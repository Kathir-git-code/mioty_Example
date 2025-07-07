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
 * @file
 * @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 * @author     STACKFORCE
 * @brief      API definition of the STACKFORCE HW tests.
 *
 */

#ifndef __SF_HW_TEST_H__
#define __SF_HW_TEST_H__

/******************************************************************************/
 /*! @defgroup SF_HW_TEST_COMMON_TEXT HW test common information
 *   @ingroup SF_HW_TEST_IF
 *
 *   @details
 *
 * Before this function can be used the user needs to ensure that no stack is
 * active. This can be done by calling the function @ref sf_stack_selectStack()
 * with the parameter @ref E_STACK_ID_NONE.  \n
 * After calling this function the device will stay in the selected test mode
 * until the function @ref sf_hw_test_stop() is called. \n
 * <b>NOTE:</b> \n
 * It must be ensured that the function @ref sf_hw_test_stop() is called
 * before any stack is selected by calling @ref sf_stack_selectStack().
 *
 *@{
 *@}
 */

/*! @defgroup SF_HW_TEST_IF Radio Test API
 *
 *  @details
 *
 *    | API Function                           | Description                                  |
 *    |----------------------------------------|----------------------------------------------|
 *    | @ref sf_hw_test_startTx()              | @copybrief sf_hw_test_startTx()              |
 *    | @ref sf_hw_test_startTxCw()            | @copybrief sf_hw_test_startTxCw()            |
 *    | @ref sf_hw_test_startTxModCw()         | @copybrief sf_hw_test_startTxModCw()         |
 *    | @ref sf_hw_test_startRx()              | @copybrief sf_hw_test_startRx()              |
 *    | @ref sf_hw_test_stop()                 | @copybrief sf_hw_test_stop()                 |
 *  @{
 */

/*==============================================================================
                            INCLUDES
==============================================================================*/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sf_stack_types.h"

/*=============================================================================
                                ENUMS
==============================================================================*/

/*! @brief Definition of hardware test return codes.
 *  @details
 *    <b>Hardware test return codes.</b> [1 Byte] \n
 *    > @copydetails E_HW_TEST_RETURN_SUCCESS \n
 *    > @copydetails E_HW_TEST_RETURN_ERROR \n
 *    > @copydetails E_HW_TEST_RETURN_ERROR_INVALID_PARAM \n
 *    > @copydetails E_HW_TEST_RETURN_ERROR_MODE_NOT_SUPPORTED \n
*/
typedef enum
{
  /*!
   * <b>0x00 : @ref E_HW_TEST_RETURN_SUCCESS - Return code success</b>
   */
  E_HW_TEST_RETURN_SUCCESS = 0,
  /*!
   * <b>0x01 : @ref E_HW_TEST_RETURN_ERROR - Return code general error</b>
   */
  E_HW_TEST_RETURN_ERROR,
  /*!
   * <b>0x02 : @ref E_HW_TEST_RETURN_ERROR_INVALID_PARAM - Return code invalid parameter</b>
   */
  E_HW_TEST_RETURN_ERROR_INVALID_PARAM,
  /*!
   * <b>0x03 : @ref E_HW_TEST_RETURN_ERROR_MODE_NOT_SUPPORTED - Return code not supported test mode</b>
   */
  E_HW_TEST_RETURN_ERROR_MODE_NOT_SUPPORTED
}hwTestReturn_t;

/*! @brief Definition of the different test modes.
 *  @details
 *    <b>Hardware test mode codes.</b> [2 Byte] \n
 *    > @copydetails E_HW_TEST_MODE_WMBUS_S \n
 *    > @copydetails E_HW_TEST_MODE_WMBUS_M2O_T \n
 *    > @copydetails E_HW_TEST_MODE_WMBUS_M2O_C \n
 *    > @copydetails E_HW_TEST_MODE_LORAWAN_FSK \n
 *    > @copydetails E_HW_TEST_MODE_MIOTY \n
*/
typedef enum
{
  /*!
   * <b>0x0000 : @ref E_HW_TEST_MODE_WMBUS_S - wMBus mode S</b>
   */
  E_HW_TEST_MODE_WMBUS_S = 0x0000,
  /*!
   * <b>0x0001 : @ref E_HW_TEST_MODE_WMBUS_M2O_T - wMBus meter mode T</b>
   */
  E_HW_TEST_MODE_WMBUS_M2O_T = 0x0001,
  /*!
   * <b>0x0002 : @ref E_HW_TEST_MODE_WMBUS_M2O_C - wMBus meter mode C</b>
   */
  E_HW_TEST_MODE_WMBUS_M2O_C = 0x0002,
  /*!
   * <b>0x0100 : @ref E_HW_TEST_MODE_LORAWAN_FSK - LoRaWAN FSK</b>
   */
  E_HW_TEST_MODE_LORAWAN_FSK = 0x0100,
/*!
   * <b>0x0200 : @ref E_HW_TEST_MODE_MIOTY - mioty mode</b>
   */
  E_HW_TEST_MODE_MIOTY = 0x0200
}hwTestMode_t;

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/*!
 * @brief Sets the radio into the test mode with selected frequency, power and
          modulation.
 *
 * @copydetails SF_HW_TEST_COMMON_TEXT
 *
 * @param mode      Used test mode.
 *
 * @param freq      The radio frequency in Hz.
 *
 * @param power     The transmission power in dBm.
 *
 * @param modulated Select if test wave should be modulated.
 *
 *
 * @return Status of the operation. \n
 *         @copydetails hwTestReturn_t
 */
/*============================================================================*/
hwTestReturn_t sf_hw_test_startTx(hwTestMode_t mode, uint32_t freq,
                                  int8_t power, bool modulated);

/*============================================================================*/
/*!
 * @brief Sets the radio into the unmodulated continuous wave test mode
          "TX unmodulated".
 *
 * @copydetails SF_HW_TEST_COMMON_TEXT
 *
 * @param freq      The radio frequency in Hz.
 *
 * @param power     The transmission power in dBm.
 *
 *
 * @return Status of the operation. \n
 *         @copydetails hwTestReturn_t
 */
/*============================================================================*/
hwTestReturn_t sf_hw_test_startTxCw(uint32_t freq, int8_t power);

/*============================================================================*/
/*!
 * @brief Sets the radio into the modulated continuous wave test mode
          "TX modulated".
 *
 * @copydetails SF_HW_TEST_COMMON_TEXT
 *
 * @param mode        Used test mode.
 *
 * @param power       The transmission power in dBm.
 *
 * @return Status of the operation. \n
 *         @copydetails hwTestReturn_t
 */
/*============================================================================*/
hwTestReturn_t sf_hw_test_startTxModCw(hwTestMode_t mode, int8_t power);

/*============================================================================*/
/*!
 * @brief Sets the radio into the receiving mode "RX".
 *
 * @copydetails SF_HW_TEST_COMMON_TEXT
 *
 * @param mode        Used test mode.
 *
 * @return Status of the operation. \n
 *         @copydetails hwTestReturn_t
 */
/*============================================================================*/
hwTestReturn_t sf_hw_test_startRx(hwTestMode_t mode);

/*============================================================================*/
/*!
 * @brief Cancel any on going hw test operation.
 *
 * @return Status of the operation. \n
 *         @copydetails hwTestReturn_t
 */
/*============================================================================*/
hwTestReturn_t sf_hw_test_stop(void);

/**@} end of SF_HW_TEST_IF */

#endif /* __SF_HW_TEST_H__ */
#ifdef __cplusplus
}
#endif
