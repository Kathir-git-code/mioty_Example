#ifdef __cplusplus
extern "C" {
#endif

/**
 @code
  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 embedded.connectivity.solutions.==============
 @endcode

 @file
 @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 @author     STACKFORCE
 @brief      Mioty timer specific implementation.
*/

/*==============================================================================
                            INCLUDES
==============================================================================*/
/* Standard libraries */
#include <stdint.h>
#include <stdbool.h>
/* SDK includes */
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Clock.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/timer.h)
#include DeviceFamily_constructPath(driverlib/aon_rtc.h)
#include DeviceFamily_constructPath(driverlib/aon_event.h)

/* Module specific includes. */
#include "sf_stack_hal_mioty_timer.h"
#include "sf_drv_lfxoCalib.h"

/*==============================================================================
                            MACROS
==============================================================================*/
/* The calibration duration in RTC ticks. */
#ifndef SF_MIOTY_TMR_CALIBDURATION_RTCTC
#define SF_MIOTY_TMR_CALIBDURATION_RTCTC         (1000)
#endif
/* Minimum time a tick period should ever take.
   Default is derived from 32,768 kHz * 120e-6.
   100ppm for the RTC crystal and 20ppm for the HF crystal. */
#ifndef SF_MIOTY_TMR_RTCTICKPERIOD_MIN_PS
#define SF_MIOTY_TMR_RTCTICKPERIOD_MIN_PS        (30513916)
#endif
/* Maximum time a tick period should ever take.
   Default is derived from 32,768 kHz * 120e-6.
   100ppm for the RTC crystal and 20ppm for the HF crystal. */
#ifndef SF_MIOTY_TMR_RTCTICKPERIOD_MAX_PS
#define SF_MIOTY_TMR_RTCTICKPERIOD_MAX_PS        (30521241)
#endif
/* Conversion factor from nano seconds to pico seconds. */
#define SF_MIOTY_TMR_NS_TO_PS                    (1000U)
/* Number of radio-bursts after which a new calibration of the LFXO is done.
   First calibration is always done before any transmission takes place.
   Default is set higher than the potential number of radio-bursts to disable
   re-calibration during transmission.
   Actual value needs to be adjusted to the thermal situation on the end-point. */
#ifndef SF_MIOTY_TMR_LFCALIBINTERVAL
#define SF_MIOTY_TMR_LFCALIBINTERVAL             (300)
#endif
/* Default RTC Tick Period for a 32,768 kHz crystal. */
#ifndef SF_MIOTY_TMR_RTCTICKPERIOD_PS
#define SF_MIOTY_TMR_RTCTICKPERIOD_PS            (30517578)
#endif
/*! 250 us in RTCTC notation */
#define SF_MIOTY_TMR_GUARD_RTCTC                 (20UL)
#define SF_MIOTY_TMR_GUARD_RTC64                 ((uint64_t) SF_MIOTY_TMR_GUARD_RTCTC << 16)

/*==============================================================================
                                VARIABLES
==============================================================================*/
/* HF timer interrupt object. */
static Hwi_Struct gHwiHfTimer;
/* The number of sub-packets have been processed of a single frame. */
static uint32_t gSubpacketCount = 0;
/* Reference timer. */
static uint64_t gReferenceTimeInRtc64 = 0;
/** Stores pointer to the callback which will be called in case a delay is
 *  expired.   */
sf_stack_hal_mioty_timer_callbackFunc_t* gfp_callback;
/* Current measured period time of the LF oscillator (in picoseconds). */
static uint32_t gLfPeriodTimeInPs = SF_MIOTY_TMR_RTCTICKPERIOD_PS;


/*==============================================================================
                         LOCAL FUNCTION IMPLEMENTATION
==============================================================================*/
/*============================================================================*/
/*!
 * @brief  Transform a full 64 bit RTC timer to a 32 bit compare register value.
 *
 */
/*============================================================================*/
static inline uint32_t loc_rtc64ToRtctc(uint64_t const rtc64)
{
  return (rtc64 >> 16);
}

/*============================================================================*/
/*!
 * @brief  Measures the LF timer period length in picoseconds.
 *
 * @return true in case of valid value, false otherwise.
 */
/*============================================================================*/
static bool loc_calibrateLf()
{
  uint64_t lfPeriodInPs = 0;

  /* run sensor controller to calibrate. */
  sf_drv_lfxoCalib_startLfTimeMeasurement(SF_MIOTY_TMR_CALIBDURATION_RTCTC);

  lfPeriodInPs = sf_drv_lfxoCalib_getLfTimeMeasurementResult();

  /* Check if we are in the expected range. */
  if(lfPeriodInPs >= SF_MIOTY_TMR_RTCTICKPERIOD_MIN_PS &&
     lfPeriodInPs <= SF_MIOTY_TMR_RTCTICKPERIOD_MAX_PS)
  {
    gLfPeriodTimeInPs = lfPeriodInPs;

    return true;
  }
  else
  {
    return false;
  }
}

/*============================================================================*/
/*!
 * @brief   Configure the RTC timer for this module purposes.
 *
 * @details For the call scheduling we use the RTC compare channel 1.
 *          Note that channel 0 is used by the TI-RTOS. The RTC is
 *          configured and started by TI-RTOS. We need to hook
 *          for the RTC interrupt in the TI-RTOS config file.
 */
/*============================================================================*/
static void loc_setupRtcCompareChannel(void)
{
  /* Enable MCU wake-up by the RTC CH1 event. WU0 and WU1 signals are
     preconfigured by the TI-RTOS, therefore we use WU2. */
  AONEventMcuWakeUpSet(AON_EVENT_MCU_WU2, AON_EVENT_RTC_CH1);

  /* TI_RTOS already routes RTC CH0 to RTC combined event,
     here we add also CH1. */
  AONRTCCombinedEventConfig(AON_RTC_CH0 | AON_RTC_CH1);

  /* Set the priority of the RTC combined interrupt to the highest
     dispatched value. */
  Hwi_setPriority(INT_AON_RTC_COMB, 0x20);

  /* Clear and enable RTC compare channel 1. */
  AONRTCEventClear(AON_RTC_CH1);
  AONRTCChannelEnable(AON_RTC_CH1);
}

/*============================================================================*/
/*!
 * @brief  Returns a value in the RTC compare format.
 *
 * @param timeoutInPs  Value to be converted in picoseconds
 */
/*============================================================================*/
static inline uint32_t loc_getLfTimerCompareValue(int64_t timeoutInPs)
{
  uint32_t  nLfPeriods = timeoutInPs / gLfPeriodTimeInPs;
  /* -1 because HF timer counts one LF period more
     <<1 to scale to RtcCompareValue format. */
  return ((nLfPeriods - 1) << 1);
}

/*============================================================================*/
/*!
 * @brief  Returns a value in the HF timer compare format.
 *
 * @param remainingTimeInPs  Value to be converted in picoseconds. It should be
 *                           the time left to start the action.
 */
/*============================================================================*/
static inline uint32_t loc_getHfTimerCompareValue(int64_t remainingTimeInPs)
{
  //                    remainingTimeInPs     remainingTimeInPs     remainingTimeInPs * 3
  // ticksForHfTimer = ------------------ = ------------------ = ----------------------
  //                      psPerHfTick         10^12/48000000             62500
  return (remainingTimeInPs * 3) / 62500;
}

/*============================================================================*/
/*!
 * @brief  Interrupt subroutine of the high precision timer.
 */
/*============================================================================*/
static void HfTimerIsr(UArg arg)
{
  TimerIntClear(GPT0_BASE, TIMER_TIMA_TIMEOUT);

  /* Inform the higher layer that the expected delay is expired. */
  if(NULL != gfp_callback)
  {
    gfp_callback();
  }/* if */

  /* Release GPT resources, stop enforcing the HF crystal enable
     and allow sleep modes again. */
  Power_releaseDependency(PowerCC26XX_XOSC_HF);
  Power_releaseDependency(PowerCC26XX_PERIPH_GPT0);
  Power_releaseConstraint(PowerCC26XX_SB_DISALLOW);
}

/*============================================================================*/
/*!
 * @brief  Specific low frequency timer delay function.
 *
 * @param  timeoutInNs      Delay time in nanoseconds.
 */
/*============================================================================*/
static bool loc_lfTimer_delayTill(uint64_t timeoutInNs)
{
  uint32_t timeoutInRtctc = loc_getLfTimerCompareValue(timeoutInNs * SF_MIOTY_TMR_NS_TO_PS);
  uint32_t referenceInRtctc = loc_rtc64ToRtctc(gReferenceTimeInRtc64);
  uint32_t wakeupTimeRtctc = timeoutInRtctc + referenceInRtctc;
  uint32_t currentTimeInRtctc = loc_rtc64ToRtctc(AONRTCCurrent64BitValueGet());

  if(wakeupTimeRtctc <= currentTimeInRtctc + SF_MIOTY_TMR_GUARD_RTCTC)
  {
    return false;
  }
  else
  {
    /* Schedule the timeout. */
    HWREG(AON_RTC_BASE + AON_RTC_O_CH1CMP) = wakeupTimeRtctc;
  }

  return true;
}

/*============================================================================*/
/*!
 * @brief  Specific high frequency timer delay function. It calculates
 *         the remaining time until the transmission point with more precision.
 *
 * @param  timeoutInNs      Delay time in nanoseconds.
 */
/*============================================================================*/
static bool loc_hfTimer_delayTill(uint64_t timeoutInNs)
{
  uint32_t timeoutInRtctc = loc_getLfTimerCompareValue(timeoutInNs * SF_MIOTY_TMR_NS_TO_PS);
  uint32_t referenceInRtctc = loc_rtc64ToRtctc(gReferenceTimeInRtc64);
  uint32_t wakeupTimeRtctc = timeoutInRtctc + referenceInRtctc;
  uint32_t currentTimeInRtctc = loc_rtc64ToRtctc(AONRTCCurrent64BitValueGet());
  uint64_t remainingTimeInPs = ((wakeupTimeRtctc - currentTimeInRtctc) >> 1) * gLfPeriodTimeInPs;

  if(wakeupTimeRtctc <= currentTimeInRtctc + SF_MIOTY_TMR_GUARD_RTCTC)
  {
    return false;
  }

  /* Force HF crystal enabled, disable standby mode and
      configure the high precision timer to be ready to
      measure the remaining time after RTC interrupt. */
  Power_setDependency(PowerCC26XX_XOSC_HF);
  Power_setDependency(PowerCC26XX_PERIPH_GPT0);
  Power_setConstraint(PowerCC26XX_SB_DISALLOW);
  TimerConfigure(GPT0_BASE, TIMER_CFG_ONE_SHOT);
  TimerIntEnable(GPT0_BASE, TIMER_TIMA_TIMEOUT);
  TimerLoadSet(GPT0_BASE, TIMER_A, loc_getHfTimerCompareValue(remainingTimeInPs));
  TimerEnable(GPT0_BASE, TIMER_A);

  return true;
}

/*==============================================================================
                      API FUNCTION IMPLEMENTATION
==============================================================================*/
/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_timer_init */
/*----------------------------------------------------------------------------*/
void sf_stack_hal_mioty_timer_init(void)
{
  /* Setup sensor controller studio task for calibration of LF. */
  sf_drv_lfxoCalib_init();

  /* Destruct HF timer interrupt. It is necessary if there was a previously
     initialisation. */
  Hwi_destruct(&gHwiHfTimer);

  /* HF Timer interrupt config. */
  Error_Block eb;
  Error_init(&eb);
  Hwi_Params hwiParams;
  Hwi_Params_init(&hwiParams);
  Hwi_construct(&gHwiHfTimer, INT_GPT0A, HfTimerIsr, &hwiParams, &eb);
  /* highest dispatched interrupt priority. */
  Hwi_setPriority(INT_GPT0A, 0x20);
}/* sf_stack_hal_mioty_timer_init() */

/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_timer_deInit */
/*----------------------------------------------------------------------------*/
void sf_stack_hal_mioty_timer_deInit(void)
{

} /* sf_stack_hal_mioty_timer_deInit() */

/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_timer_delayTill */
/*----------------------------------------------------------------------------*/
bool sf_stack_hal_mioty_timer_delayTill(uint64_t* pTotalPointOfTime, stackHalMiotyState_t state,
                            sf_stack_hal_mioty_timer_callbackFunc_t fp_callback)
{
  bool ret = true;

  if(NULL == pTotalPointOfTime || NULL == fp_callback)
  {
    return false;
  }

  /* Increase the number Number of sub-packets have been processed. */
  if(0 == *pTotalPointOfTime)
  {
    gSubpacketCount = 0;
  }
  else if(E_STACK_HAL_MIOTY_TIMER_STATE_TX_PREPARE == state)
  {
    gSubpacketCount++;
  }

  /* Clibrate LFXO. */
  if(gSubpacketCount % SF_MIOTY_TMR_LFCALIBINTERVAL == 0)
  {
    /* (re-) calibrate. */
    loc_calibrateLf();
  }

  gfp_callback = fp_callback;

  if(0 == *pTotalPointOfTime)
  {
    /* Configure RTC timer for our purposes. */
    loc_setupRtcCompareChannel();

    /* Get time 0. */
    gReferenceTimeInRtc64 = AONRTCCurrent64BitValueGet() + SF_MIOTY_TMR_GUARD_RTC64;

    HWREG(AON_RTC_BASE + AON_RTC_O_CH1CMP) = loc_rtc64ToRtctc(gReferenceTimeInRtc64);
  }
  else if(E_STACK_HAL_MIOTY_TIMER_STATE_TX_PREPARE == state ||
          E_STACK_HAL_MIOTY_TIMER_STATE_RX_PREPARE == state)
  {
    /* Configure RTC timer for our purposes. */
    loc_setupRtcCompareChannel();

    ret = loc_lfTimer_delayTill(*pTotalPointOfTime);
  }
  else if(E_STACK_HAL_MIOTY_TIMER_STATE_TX_SUB == state ||
          E_STACK_HAL_MIOTY_TIMER_STATE_TX_LAST_SUB == state ||
          E_STACK_HAL_MIOTY_TIMER_STATE_RX_SUB == state)
  {
    ret = loc_hfTimer_delayTill(*pTotalPointOfTime);
  }

  return ret;
}/* sf_stack_hal_mioty_timer_delayTill() */

/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_timer_isDeepSleepPossible */
/*----------------------------------------------------------------------------*/
bool sf_stack_hal_mioty_timer_isDeepSleepPossible(void)
{
  /* This function is doing nothing */
  return false;
}/* sf_stack_hal_mioty_timer_isDeepSleepPossible() */

/*==============================================================================
                            INTERRUPTS
==============================================================================*/
/*! \brief Interrupt subroutine of the LF RTC timer.
 *
 *  This is actually a hook function called from the real
 *  RTC ISR that is embedded inside of the TI-RTOS. This
 *  function needs to be set up in the TI-RTOS config file.
 */
void RtcCh1CompareIsr(UArg arg)
{
  /* Inform the higher layer that the expected delay is expired. */
  if(NULL != gfp_callback)
  {
    gfp_callback();
  }/* if */
}

#ifdef __cplusplus
}
#endif
