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
 @brief      STACKFORCE example HAL for RF.

*/

#ifndef __SF_STACK_HAL_MIOTY_RF_H__
#define __SF_STACK_HAL_MIOTY_RF_H__

/**
 *  @addtogroup SF_STACK_HAL
 *
 *  @details
 *
 *  - <b>RF API</b>\n
 *    | API Function                              | Description                                     |
 *    |-------------------------------------------|-------------------------------------------------|
 *    | @ref sf_stack_hal_mioty_rf_configTxData() | @copybrief sf_stack_hal_mioty_rf_configTxData() |
 *    | @ref sf_stack_hal_mioty_rf_configTx()     | @copybrief sf_stack_hal_mioty_rf_configTx()     |
 *    | @ref sf_stack_hal_mioty_rf_tx()           | @copybrief sf_stack_hal_mioty_rf_tx()           |
 *    | @ref sf_stack_hal_mioty_rf_configRx()     | @copybrief sf_stack_hal_mioty_rf_configRx()     |
 *    | @ref sf_stack_hal_mioty_rf_rx()           | @copybrief sf_stack_hal_mioty_rf_rx()           |
 *    | @ref sf_stack_hal_mioty_rf_initRx()       | @copybrief sf_stack_hal_mioty_rf_initRx()       |
 *    | @ref sf_stack_hal_mioty_rf_txTest()       | @copybrief sf_stack_hal_mioty_rf_txTest()       |
 *    | @ref sf_stack_hal_mioty_rf_deInit()       | @copybrief sf_stack_hal_mioty_rf_deInit()       |
 *  @{
 */
#include <stdint.h>
#include <stdbool.h>

/*============================================================================*/
/**
 * @brief Set the tx related register of the transceiver.
 *
 * @param centerFreq  Base frequency in MHz.
 * @param fractFreq   Fractional part of the frequency to tune to.
 * @param pOverrides  register overrides.
 * @param txPower     Tx power register.
 *
 * @return true is everything is fine, otherwise false.
 */
/*============================================================================*/
bool sf_stack_hal_mioty_rf_configTx( uint16_t centerFreq, uint16_t fractFreq,
                              uint32_t* pOverrides, uint16_t txPower );

/*============================================================================*/
/**
 * @brief Hand the payload over to the transceiver.
 *
 * @param pPayload          Pointer to the payload.
 * @param length            Payload length.
 *
 * @return true is everything is fine, otherwise false.
 */
/*============================================================================*/
bool sf_stack_hal_mioty_rf_configTxData( uint8_t* pPayload, uint8_t length );

/*============================================================================*/
/*!
 * @brief  Start the transmission.
 *
 * @return true is everything is fine, otherwise false.
 */
/*============================================================================*/
bool sf_stack_hal_mioty_rf_tx(void);

/*============================================================================*/
/**
 * @brief Set up the transceiver for Rx.
 *
 * @param freq              Center frequency.
 * @param freqFrac          Frequency fraction.
 * @param shift             Shift value used to recenter frequency after
 *                          reception
 * @param samplesToCapture  Samples to be captured.
 * @param pOutBuf           Application IQ buffer.
 */
/*============================================================================*/
void sf_stack_hal_mioty_rf_configRx(uint16_t freq, uint16_t freqFrac,
                                    int32_t shift, uint16_t samplesToCapture,
                                    int16_t* pOutBuf);

/*============================================================================*/
/*!
 * @brief  Start the reception.
 */
/*============================================================================*/
void sf_stack_hal_mioty_rf_rx(void);

/*============================================================================*/
/*!
 * @brief  Initialize Rx.
 *
 * @param pBuffer           Rx buffer.
 * @param bufferSize        Buffer size
 *
 * @return true is everything is fine, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_mioty_rf_initRx( uint8_t *pBuffer, uint32_t bufferSize );

/*============================================================================*/
/*!
 * @brief  Start the transmission of a carrier.
 *
 * @param useCw             1 if an unmodulated carrier should transmitted.
 *                          0 if a modulated carrier should be transmitted.
 *
 * @return true is everything is fine, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_mioty_rf_txTest(bool useCw);

/*============================================================================*/
/*!
 * @brief  Sets the transceiver in to rx-mode till another test mode is
 *         requested.
 *
 *
 * @return true is everything is fine, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_mioty_rf_rxTest(void);

/*============================================================================*/
/*!
 * @brief  De-Initialize mioty rf.
 *
 *
 * @return true is everything is fine, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_mioty_rf_deInit(void);

/*! @} */

#endif  /* __SF_STACK_HAL_MIOTY_RF_H__ */

#ifdef __cplusplus
}
#endif
