#ifndef __SF_DRV_LFXOCALIB_H__
#define __SF_DRV_LFXOCALIB_H__

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

#include <stdint.h>
#include <stdbool.h>

/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/
/*============================================================================*/
/*!
 * @brief  The function should be called once before first calibration.
 *
 */
/*============================================================================*/
void sf_drv_lfxoCalib_init();

/*============================================================================*/
/*!
 * @brief  Starts low frequency timer.
 *
 * @param lfTicks   Number of ticks to calibrate.
 */
/*============================================================================*/
void sf_drv_lfxoCalib_startLfTimeMeasurement(uint16_t const lfTicks);

/*============================================================================*/
/*!
 * @brief  Returns the low frequency timer period length in picoseconds.
 *
 * @return LF time measurement result in ticks.
 */
/*============================================================================*/
uint32_t sf_drv_lfxoCalib_getLfTimeMeasurementResult(void);

#endif /* __SF_DRV_LFXOCALIB_H__ */
