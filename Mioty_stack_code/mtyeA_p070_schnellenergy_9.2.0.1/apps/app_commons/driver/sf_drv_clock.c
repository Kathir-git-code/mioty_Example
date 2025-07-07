#ifdef __cplusplus
extern "C" {
#endif
/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       sf_drv_clock.h
 * @copyright  STACKFORCE GmbH, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @brief      HAL for generic timer implementations.
 */

/*=============================================================================
                                INCLUDES
=============================================================================*/
#include <stdint.h>
#include <stdbool.h>

#include "sf_drv_clock.h"

/*=============================================================================
                                MACRO
=============================================================================*/
/* Multiplier to convert miliseconds to micro seconds. */
#define SF_DRV_CLOCK_MS_TO_US           1000
#define SF_DRV_CLOCK_TIMEOUT_MAX        0xFFFFFFFF/SF_DRV_CLOCK_MS_TO_US

/*=============================================================================
                    API FUNCTION IMPLEMENTATION
=============================================================================*/
/*----------------------------------------------------------------------------*/
/*! sf_drv_clock_init() */
/*----------------------------------------------------------------------------*/
Clock_Handle sf_drv_clock_init(void)
{
  Clock_Handle pClockHandle;
  Clock_Params clockParams;

  /* Configure default clock params */
  Clock_Params_init(&clockParams);
  clockParams.period = 0;
  clockParams.startFlag = false;

  /* Create clock instance. */
  pClockHandle = Clock_create(NULL, 0, &clockParams, NULL);

  return pClockHandle;
}/* sf_drv_clock_init() */

/*----------------------------------------------------------------------------*/
/*! sf_drv_clock_start() */
/*----------------------------------------------------------------------------*/
bool sf_drv_clock_start(Clock_Handle pClockHandle, uint32_t timeout,
                        Clock_FuncPtr fp_clockCb )
{
  bool ret = false;

  if((NULL != fp_clockCb) && (NULL != pClockHandle))
  {
    if(Clock_isActive(pClockHandle))
    {
      Clock_stop(pClockHandle);
    }/* if */

    Clock_setFunc(pClockHandle, fp_clockCb, NULL);
    Clock_setTimeout(pClockHandle, (timeout / Clock_tickPeriod));

    Clock_start(pClockHandle);

    ret = true;
  }/* if */

  return ret;
}/* sf_drv_clock_start() */

/*----------------------------------------------------------------------------*/
/*! sf_drv_clock_stop() */
/*----------------------------------------------------------------------------*/
bool sf_drv_clock_stop(Clock_Handle pClockHandle)
{
  bool ret = false;

  if(NULL != pClockHandle)
  {
    Clock_stop(pClockHandle);
    ret = true;
  }/* if */

  return ret;
}/* sf_drv_clock_stop() */


#ifdef __cplusplus
}
#endif
