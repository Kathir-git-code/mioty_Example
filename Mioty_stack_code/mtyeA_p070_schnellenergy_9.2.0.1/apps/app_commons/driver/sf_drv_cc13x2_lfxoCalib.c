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

#include <stddef.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_aon_pmctl.h)
#include DeviceFamily_constructPath(inc/hw_aux_sysif.h)

#include "sf_drv_lfxoCalib.h"
#include "scif_framework.h"
#include "scif_osal_tirtos.h"

/*==============================================================================
                         MACROS
==============================================================================*/
/* lfTickDurationInHfXoscTicks: Task ID */
#define SCIF_CC13X2LFXO_CALIB_LF_TICK_DURATION_IN_HF_XOSC_TICKS_TASK_ID 0

/* Sensor Controller task generic control (located in AUX RAM) */
#define scifCc13x2lfxoCalibTaskData    (*((volatile SCIF_CC13X2LFXO_CALIB_TASK_DATA_T*) 0x400E015C))

/* lfTickDurationInHfXoscTicks: Task input data structure */
typedef struct {
    uint16_t lfticks;
} SCIF_CC13X2LFXO_CALIB_LF_TICK_DURATION_IN_HF_XOSC_TICKS_INPUT_T;


/* lfTickDurationInHfXoscTicks: Task output data structure */
typedef struct {
    uint16_t hfticksHigh;
    uint16_t hfticksLow;
} SCIF_CC13X2LFXO_CALIB_LF_TICK_DURATION_IN_HF_XOSC_TICKS_OUTPUT_T;

/* Sensor Controller task data (configuration, input buffer(s),
 * output buffer(s) and internal state) */
typedef struct {
    struct {
        SCIF_CC13X2LFXO_CALIB_LF_TICK_DURATION_IN_HF_XOSC_TICKS_INPUT_T input;
        SCIF_CC13X2LFXO_CALIB_LF_TICK_DURATION_IN_HF_XOSC_TICKS_OUTPUT_T output;
    } lfTickDurationInHfXoscTicks;
} SCIF_CC13X2LFXO_CALIB_TASK_DATA_T;
/*==============================================================================
                         VARIABLES
==============================================================================*/
/* Initialized internal driver data, to be used in the call to \ref scifInit() */
extern const SCIF_DATA_T scifCc13x2lfxoCalibDriverSetup;

/* Firmware image to be uploaded to the AUX RAM */
static const uint16_t gAuxRamImage[] = {
    /*0x0000*/ 0x140E, 0x0417, 0x140E, 0x0438, 0x140E, 0x0442, 0x140E, 0x045F, 0x140E, 0x0468, 0x140E, 0x0471, 0x140E, 0x047A, 0x8953, 0x9954,
    /*0x0020*/ 0x8D29, 0xBEFD, 0x4553, 0x2554, 0xAEFE, 0x445C, 0xADB7, 0x745B, 0x545B, 0x7000, 0x7CA2, 0x68AB, 0x009F, 0x1431, 0x68AC, 0x00A0,
    /*0x0040*/ 0x1431, 0x68AD, 0x00A1, 0x1431, 0x78A2, 0xF801, 0xFA01, 0xBEF2, 0x78A9, 0x68AB, 0xFD0E, 0x68AD, 0xED92, 0xFD06, 0x7CA9, 0x6440,
    /*0x0060*/ 0x047F, 0x78A2, 0x8F1F, 0xED8F, 0xEC01, 0xBE01, 0xADB7, 0x8DB7, 0x755B, 0x555B, 0x78A7, 0x60BF, 0xEF27, 0xE240, 0xEF27, 0x7000,
    /*0x0080*/ 0x7CA7, 0x047F, 0x6477, 0x0000, 0x18A9, 0x9D88, 0x9C01, 0xB60E, 0x109E, 0xAF19, 0xAA00, 0xB60A, 0xA8FF, 0xAF39, 0xBE07, 0x0CA2,
    /*0x00A0*/ 0x8600, 0x88A0, 0x8F08, 0xFD47, 0x9DB7, 0x08A2, 0x8801, 0x8A01, 0xBEEB, 0x254F, 0xAEFE, 0x645B, 0x445B, 0x4477, 0x047F, 0x5656,
    /*0x00C0*/ 0x655B, 0x455B, 0x0000, 0x0CA2, 0x0001, 0x0CA3, 0x1416, 0x047F, 0x5657, 0x665B, 0x465B, 0x0000, 0x0CA2, 0x0002, 0x0CA3, 0x1416,
    /*0x00E0*/ 0x047F, 0x5658, 0x675B, 0x475B, 0x0000, 0x0CA2, 0x0004, 0x0CA3, 0x1416, 0x047F, 0x765B, 0x565B, 0x86FF, 0x03FF, 0x0CA5, 0x645C,
    /*0x0100*/ 0x78A4, 0x68A5, 0xED37, 0xB605, 0x0000, 0x0CA4, 0x7CAA, 0x6540, 0x0CA5, 0x78A5, 0x68A6, 0xFD0E, 0xF801, 0xE95A, 0xFD0E, 0xBE01,
    /*0x0120*/ 0x6553, 0xBDB7, 0x700B, 0xFB96, 0x4453, 0x2454, 0xAEFE, 0xADB7, 0x6453, 0x2454, 0xA6FE, 0x7000, 0xFB96, 0xADB7, 0x0000, 0x00B1,
    /*0x0140*/ 0x00B3, 0x00FA, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01F4, 0x0000,
    /*0x0160*/ 0x0000, 0x1498, 0xADB7, 0x1492, 0x248B, 0xA6FE, 0x2486, 0xA6FE, 0x0004, 0x8B6A, 0x003F, 0x8B3C, 0xFDB1, 0x671A, 0x0015, 0x8B21,
    /*0x0180*/ 0x0002, 0x8B2D, 0x741A, 0x0025, 0x8B22, 0x08AE, 0x8802, 0x8B2E, 0x0001, 0x8B6A, 0x003F, 0x8B3C, 0xFDB1, 0x0180, 0x86A1, 0x8B00,
    /*0x01A0*/ 0x0100, 0x86A0, 0x8B80, 0x86A0, 0x8900, 0x0000, 0x8631, 0x1130, 0x9B36, 0x8B38, 0x6439, 0x14FC, 0x7002, 0x1500, 0x0000, 0x8B1D,
    /*0x01C0*/ 0x0001, 0x8B1A, 0x0031, 0x8B3C, 0xFDB1, 0x0004, 0x8B6A, 0x003F, 0x8B3C, 0xFDB1, 0x0000, 0x8B1A, 0x671A, 0x741A, 0x641F, 0x661F,
    /*0x01E0*/ 0x0000, 0x8B6A, 0x8934, 0x9933, 0x0CAF, 0x1CB0, 0x150B, 0x648B, 0x6486, 0xADB7, 0x1498, 0xADB7, 0x6468, 0x2568, 0xA6FE, 0xADB7,
    /*0x0200*/ 0x6003, 0xEB31, 0x600F, 0xEB35, 0x6000, 0xEB31, 0xFB31, 0x7643, 0xA500, 0xFD47, 0xADB7, 0x7003, 0xFB31, 0x4468, 0x2568, 0xAEFE,
    /*0x0220*/ 0xADB7
};


/* Look-up table that converts from AUX I/O index to MCU IOCFG offset */
static const uint8_t gAuxIoIndexToMcuIocfgOffsetLut[] = {
    0, 68, 64, 60, 56, 52, 48, 44, 40, 36, 32, 28, 24, 20, 16, 12, 0, 0, 0, 120, 116, 112, 108, 104, 100, 96, 92, 88, 84, 80, 76, 72
};


/** \brief Look-up table of data structure information for each task
  *
  * There is one entry per data structure (\c cfg, \c input, \c output and \c state) per task:
  * - [31:20] Data structure size (number of 16-bit words)
  * - [19:12] Buffer count (when 2+, first data structure is preceded by buffering control variables)
  * - [11:0] Address of the first data structure
  */
static const uint32_t gScifTaskDataStructInfoLut[] = {
/*  cfg         input       output      state */
    0x00000000, 0x0010115C, 0x0020115E, 0x00000000  /* lfTickDurationInHfXoscTicks */
};

/*==============================================================================
                         LOCAL FUNCTION IMPLEMENTATION
==============================================================================*/
/* SCIF driver callback: Task control interface ready (non-blocking task
 * control operation completed) */
static void loc_scCtrlReadyCallback(void) {

}

/* SCIF driver callback: Sensor Controller task code has generated an
 * alert interrupt */
static void loc_scTaskAlertCallback(void) {

}

/** \brief Performs driver setup dependent hardware initialization
  *
  * This function is called by the internal driver initialization function, \ref scifInit().
  */
static void loc_scifDriverSetupInit(void) {

    /* Select SCE clock frequency in active mode */
    HWREG(AON_PMCTL_BASE + AON_PMCTL_O_AUXSCECLK) = AON_PMCTL_AUXSCECLK_SRC_SCLK_HFDIV2;

    /* Set the default power mode */
    scifSetSceOpmode(AUX_SYSIF_OPMODEREQ_REQ_A);

    /* Initialize task resource dependencies
     * - None required */

} /* scifDriverSetupInit */

/** \brief Performs driver setup dependent hardware uninitialization
  *
  * This function is called by the internal driver uninitialization function, \ref scifUninit().
  */
static void loc_scifDriverSetupUninit(void) {

    /* Uninitialize task resource dependencies
     * - None required */

} /* scifDriverSetupUninit */

/// Driver setup data, to be used in the call to \ref scifInit()
const SCIF_DATA_T scifCc13x2lfxoCalibDriverSetup = {
    (volatile SCIF_INT_DATA_T*) 0x400E0144,
    (volatile SCIF_TASK_CTRL_T*) 0x400E0152,
    (volatile uint16_t*) 0x400E013C,
    0x0000,
    sizeof(gAuxRamImage),
    gAuxRamImage,
    gScifTaskDataStructInfoLut,
    gAuxIoIndexToMcuIocfgOffsetLut,
    0x0000,
    24,
    loc_scifDriverSetupInit,
    loc_scifDriverSetupUninit,
    (volatile uint16_t*) NULL,
    (volatile uint16_t*) NULL,
    NULL
};

/*==============================================================================
                         API FUNCTION IMPLEMENTATION
==============================================================================*/
/*----------------------------------------------------------------------------*/
/*! sf_drv_lfxoCalib_init */
/*----------------------------------------------------------------------------*/
void sf_drv_lfxoCalib_init()
{
  /* Initialize the SCIF operating system abstraction layer */
  scifOsalInit();
  scifOsalRegisterCtrlReadyCallback(loc_scCtrlReadyCallback);
  scifOsalRegisterTaskAlertCallback(loc_scTaskAlertCallback);

  /* Initialize the SCIF driver */
  scifInit(&scifCc13x2lfxoCalibDriverSetup);
} /* sf_drv_lfxoCalib_init */

/*----------------------------------------------------------------------------*/
/*! sf_drv_lfxoCalib_startLfTimeMeasurement */
/*----------------------------------------------------------------------------*/
void sf_drv_lfxoCalib_startLfTimeMeasurement(uint16_t const lfTicks)
{
  /* set number of ticks to calibrate */
  scifCc13x2lfxoCalibTaskData.lfTickDurationInHfXoscTicks.input.lfticks = lfTicks;

  /* Reset all data structures except configuration */
  scifResetTaskStructs(1 << SCIF_CC13X2LFXO_CALIB_LF_TICK_DURATION_IN_HF_XOSC_TICKS_TASK_ID, (1 << SCIF_STRUCT_INPUT) | (1 << SCIF_STRUCT_OUTPUT));

  /* Run the "lfTickDurationInHfXoscTicks" Sensor Controller task */
  if (scifWaitOnNbl(20000) != SCIF_SUCCESS) {
      /* error */
  } else if (scifExecuteTasksOnceNbl(1 << SCIF_CC13X2LFXO_CALIB_LF_TICK_DURATION_IN_HF_XOSC_TICKS_TASK_ID) != SCIF_SUCCESS) {
      /* error */
  }
} /* sf_drv_lfxoCalib_startLfTimeMeasurement */

/*----------------------------------------------------------------------------*/
/*! sf_drv_lfxoCalib_getLfTimeMeasurementResult */
/*----------------------------------------------------------------------------*/
uint32_t sf_drv_lfxoCalib_getLfTimeMeasurementResult(void)
{
  /* Wait with 100 millisecond timeout for results */
  if (scifWaitOnNbl(100000) != SCIF_SUCCESS) {
      return 0;
  }

  uint32_t lfPeriod_lfTicks      = scifCc13x2lfxoCalibTaskData.lfTickDurationInHfXoscTicks.input.lfticks;
  uint32_t lfPeriod_hfTicks_high = scifCc13x2lfxoCalibTaskData.lfTickDurationInHfXoscTicks.output.hfticksHigh;
  uint32_t lfPeriod_hfTicks_low  = scifCc13x2lfxoCalibTaskData.lfTickDurationInHfXoscTicks.output.hfticksLow;
  uint32_t lfPeriod_hfTicks      = (lfPeriod_hfTicks_high << 16) | lfPeriod_hfTicks_low;
  uint64_t const hfTick_ps       = 20833;

  uint64_t lfTick_ps = (hfTick_ps * lfPeriod_hfTicks) / lfPeriod_lfTicks;
  return lfTick_ps;
} /* sf_drv_lfxoCalib_getLfTimeMeasurementResult */

#ifdef __cplusplus
}
#endif
