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
 * @brief      Serial communication interface for accessing Stack common API.
 */

#ifndef __SF_STACK_SERIAL_H__
#define __SF_STACK_SERIAL_H__

/*! @defgroup MS_COM_SERIAL_IF Stack Common Serial API
 *
 *  @details
 *
 *  - <b>Stack Common Serial API</b>\n
 *    | API Function                          | Description                                 |
 *    |---------------------------------------|---------------------------------------------|
 *    | @ref sf_stack_serial_init()           | @copybrief sf_stack_serial_init()           |
 *    | @ref sf_stack_serial_run()            | @copybrief sf_stack_serial_run()            |
 *    | @ref sf_stack_serial_isIdle()         | @copybrief sf_stack_serial_isIdle()         |
 *    | @ref sf_stack_serial_action()         | @copybrief sf_stack_serial_action()         |
 *    | @ref sf_stack_serial_indication()     | @copybrief sf_stack_serial_indication()     |
 *    | @ref sf_stack_serial_setKey()         | @copybrief sf_stack_serial_setKey()         |
 *    | @ref sf_stack_serial_getKey()         | @copybrief sf_stack_serial_getKey()         |
 *    | @ref sf_stack_serial_changeSecurity() | @copybrief sf_stack_serial_changeSecurity() |
 *    | @ref sf_callbackFuncSerial_t()        | @copybrief sf_callbackFuncSerial_t()        |
 *    | @ref sf_stack_hal_serial_isBusy()     | @copybrief sf_stack_hal_serial_isBusy()     |
 *  @{
 */

/*==============================================================================
                               INCLUDES
==============================================================================*/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sf_stack_types.h"

/*! Size of the rx event payload in bytes. */
#define SF_STACK_RX_EVENT_LEN                           2U

/*==============================================================================
                               FUNCTIONS
==============================================================================*/
/*============================================================================*/
/*!
 * @brief  Initializes the serial communication interface for accessing the
 *         Stack common API.
 *
 * @param serialCallback @copybrief sf_callbackFunc_t
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_serial_init( sf_callbackFuncSerial_t *serialCallback );

/*============================================================================*/
/*!
 * @brief  Run the serial communication interface and the Stack.
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_serial_run( void );

/*============================================================================*/
/*!
 * @brief  Returns if the serial communication is busy.
 *
 * @return Returns true is the serial communication is busy.
 */
/*============================================================================*/
bool sf_stack_hal_serial_isBusy( void );

/*============================================================================*/
/*!
 * @brief  Checks if the serial module is IDLE.
 *
 *         This function must be called to decide if going to sleep is possible.
 *
 * @return True if the module is IDLE. False otherwise.
 */
/*============================================================================*/
bool sf_stack_serial_isIdle(void);

/*============================================================================*/
/*!
 * @brief  Push back function to inform the serial layer about actions.
 *
 * @param  event    Defines the event which occurred.
 * @param  data     A pointer to data. The pointer can be NULL, as not
 *                  every event requires data.
 * @param  dataLen  The length of the data. Can be zero.
 *
 * @return The return value shall be E_STACK_RETURN_SUCCESS.
 */
/*============================================================================*/
stackReturn_t sf_stack_serial_action( stackEvent_t event, uint8_t *data,
                                      uint16_t dataLen );

/*============================================================================*/
/*!
 * @brief  Trigger a generic indication via serial.
 *
 * @param  stackId   SATP stack Identifier
 * @param  apiId     SATP API identifier
 * @param  indId     SATP indication identifier
 * @param  pParam    Pointer to indication parameters
 * @param  paramLen  Length of indication parameters in bytes.
 * @param  pData     Pointer to indication payload.
 * @param  dataLen   Length of indication payload in bytes.
 *
 * @return The return value shall be E_STACK_RETURN_SUCCESS.
 */
/*============================================================================*/
stackReturn_t sf_stack_serial_indication(uint8_t stackId, uint8_t apiId, uint8_t indId,
                                         uint8_t *pParam, uint8_t paramLen,
                                         uint8_t *pData, uint16_t dataLen);

/*============================================================================*/
/*!
 *  Set the key for secure serial communication.
 *
 * @param pKey       Pointer to key.
 * @param size       Size of key (16 Bytes)
 *
 * @return true, if operation is successful. Otherwise, false.
 */
/*============================================================================*/
bool sf_stack_serial_setKey(uint8_t *pKey, uint8_t size);

/*============================================================================*/
/*!
 *  Get the key for secure serial communication.
 *
 * @return Pointer to serial key location.
 */
/*============================================================================*/
uint8_t* sf_stack_serial_getKey(void);

/*============================================================================*/
/*!
 *  Enable/disable secure serial communication.
 *
 * @param enable      Enable flag.
 *
 * @return true, if operation is successful. Otherwise, false.
 */
/*============================================================================*/
bool sf_stack_serial_changeSecurity(bool enable);

/*!@} end of MS_COM_SERIAL_IF */
/******************************************************************************/

#endif /* __SF_STACK_SERIAL_H__ */
#ifdef __cplusplus
}
#endif
