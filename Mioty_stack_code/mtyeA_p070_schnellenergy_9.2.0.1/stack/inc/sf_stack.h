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
 * @brief      API definition of the STACKFORCE Stack.
 *
 */

#ifndef __SF_STACK_H__
#define __SF_STACK_H__


/*! @defgroup SF_STACK_HAL Stack HAL API
    @defgroup MS_COM_IF Stack Common API
 *
 *  @details
 *
 *  - <b>Stack Common API</b>\n
 *    | API Function                        | Description                               |
 *    |-------------------------------------|-------------------------------------------|
 *    | @ref sf_stack_init()                | @copybrief sf_stack_init()                |
 *    | @ref sf_stack_set()                 | @copybrief sf_stack_set()                 |
 *    | @ref sf_stack_get()                 | @copybrief sf_stack_get()                 |
 *    | @ref sf_stack_selectStack()         | @copybrief sf_stack_selectStack()         |
 *    | @ref sf_stack_getActiveStack()      | @copybrief sf_stack_getActiveStack()      |
 *    | @ref sf_stack_sendParams()          | @copybrief sf_stack_sendParams()          |
 *    | @ref sf_stack_send()                | @copybrief sf_stack_send()                |
 *    | @ref sf_stack_receiveParams()       | @copybrief sf_stack_receiveParams()       |
 *    | @ref sf_stack_receive()             | @copybrief sf_stack_receive()             |
 *    | @ref sf_stack_pullConfig()          | @copybrief sf_stack_pullConfig()          |
 *    | @ref sf_stack_pushConfig()          | @copybrief sf_stack_pushConfig()          |
 *    | @ref sf_stack_allocateMemory()      | @copybrief sf_stack_allocateMemory()      |
 *    | @ref sf_stack_freeMemory()          | @copybrief sf_stack_freeMemory()          |
 *    | @ref sf_callbackFunc_t()            | @copybrief sf_callbackFunc_t()            |
 *
 * \if MBUS_PRIMARY_DEVICE_DOC
 *  - <b>Stack Common API (continued)</b>\n
 *    | API Function                        | Description                               |
 *    |-------------------------------------|-------------------------------------------|
 *    | @ref sf_stack_addDevice()           | @copybrief sf_stack_addDevice()           |
 *    | @ref sf_stack_removeDevice()        | @copybrief sf_stack_removeDevice()        |
 * \endif
 *
 *  @{
 */

/*==============================================================================
                            INCLUDES
==============================================================================*/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sf_stack_types.h"

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/*!
 * @brief  Initializes the stack and sets the common parameters to their
 *         default values where needed.
 *
 * @param pCallback @copybrief sf_callbackFunc_t
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_init( sf_callbackFunc_t *pCallback );

/*============================================================================*/
/*!
 * @brief  Function to set parameters provided by the appropriate stack.
 *
 * @param  id       ID of parameter to be set. \n
 *                  @copydetails stackParamId_t
 *
 * @param  pParam   Pointer to new value for the parameter given by id.
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_set( stackParamId_t id, void *pParam );

/*============================================================================*/
/*!
 * @brief  Function to get parameters provided by the appropriate stack.
 *
 * @param  id       ID of parameter to be retrieved. \n
 *                  @copydetails stackParamId_t
 *
 * @param  pParam   Pointer to new value for the parameter given by id.
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_get( stackParamId_t id, void *pParam );

/*============================================================================*/
/*!
 * @brief   Function to select the active stack.
 *
 * @details Prepares the stack for operation. \n
 *          All stack specific peripherals are re-initalized.
 *          Re-initialization takes place even if the stack is already
 *          selected.
 *
 * @param   id ID of stack that shall be used \n
 *          @copydetails stackId_t
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_selectStack( stackId_t id );

/*============================================================================*/
/*!
 * @brief   Function to get the active stack.
 *
 * @details Returns the stack identifier of the active stack. \n
 *          The stack can be selected by the function @ref sf_stack_selectStack().
 *
 * @return Stack identifier of the active stack. \n
 *         @copydetails stackId_t
 */
/*============================================================================*/
stackId_t sf_stack_getActiveStack( void );

/*============================================================================*/
/*!
 * @brief
 * @if (MBUS_PRIMARY_DEVICE_DOC || MBUS_SECONDARY_DEVICE_DOC || MIOTY_DOC)
 * Function to set sending related parameters provided by the appropriate stack.
 * @else
 * This function is not available for the selected product.
 * @endif
 *
 * @param  id       ID of parameter to be set. \n
 *                  @copydetails stackSendParamId_t
 *
 * @param  pParam   Pointer to new value for the parameter given by id.
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_sendParams( stackSendParamId_t id, void *pParam );

/*============================================================================*/
/*!
 * @brief  Send function.
 *
 * @param  len    Number of bytes to be sent.
 * @param  pData  Pointer to the data to be sent.
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_send( uint16_t len, uint8_t *pData );

/*============================================================================*/
/*!
 *
 * @brief
 * @if (MBUS_PRIMARY_DEVICE_DOC || MBUS_SECONDARY_DEVICE_DOC)
 * Function to request details of the received frame.
 * @else
 * This function is not available for the selected product.
 * @endif
 *
 * @param  id       ID of parameter to be received. \n
 *                  @copydetails stackReceiveParamId_t
 *
 * @param  pParam   Storage where the rx-params can be stored. \n
 *          @if MBUS_PRIMARY_DEVICE_DOC
 *          | id                                                    | Pointer typ of pParam                   |
 *          |:-----------------------------------------------------:|:---------------------------------------:|
 *          | @ref  E_STACK_RECEIVE_PARAM_ID_MBUS_PRIMARY_DETAILS   |  @ref stack_mbusPrimaryRxFrame_t        |
 *          @endif
 *
 *          @if MBUS_SECONDARY_DEVICE_DOC
 *          | id                                                    | Pointer typ of pParam                   |
 *          |:-----------------------------------------------------:|:---------------------------------------:|
 *          | @ref  E_STACK_RECEIVE_PARAM_ID_MBUS_SECONDARY_DETAILS |  @ref stack_mbusSecondaryRxFrame_t      |
 *          @endif
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_receiveParams( stackReceiveParamId_t id, void *pParam );

/*============================================================================*/
/*!
 * @brief  Receive function.
 *
 * @param  len    Number of bytes of the data buffer.
 * @param  pData  Pointer to the data buffer for the received telegram data.
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_receive( uint16_t len, uint8_t *pData );

/*============================================================================*/
/*!
 * @brief  Pull runtime stack configuration from the active stack.
 *
 * @param  pLen   Pointer to a variable where the function reports the length
 *                of the byte array.
 *
 * @return Pointer to the stack configuration data.
 */
/*============================================================================*/
uint8_t* sf_stack_pullConfig( uint16_t* pLen );

/*============================================================================*/
/*!
 * @brief  Push runtime stack configuration to the active stack.
 *
 * @param  len    Length of the configuration data.
 * @param  pData  Pointer to the data buffer which contains the stack config.
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_pushConfig( uint8_t* pData, uint16_t len );

/*============================================================================*/
/*!
 * @brief  Allocates memory in the RAM.
 *
 * @param  len    Length of the requested RAM size.
 *
 * @return Returns a valid pointer if the memory cloud be allocated, otherwise
 *         the function returns NULL.
 */
/*============================================================================*/
void* sf_stack_allocateMemory( uint16_t len );

/*============================================================================*/
/*!
 * @brief  Frees an allocated memory.
 *
 * @param  memory Pointer to the memory which was allocated previously.
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_freeMemory( void* memory );

/*============================================================================*/
/*!
 * @brief   Function to add a device to a specified stack.
 *
 * @details This functionality is only available if one of the following stack's
 *          is part of the delivery: \n
 *          - @ref E_STACK_ID_MBUS_PRIMARY
 *
 * @param   deviceType Specifies which type of device shall be added. \n
 *          @copydetails stackDevice_t
 *
 * @param   pParam Pointer to the information required to add the device. \n
 *          The information which needs to be provided are depending on the
 *          param deviceType.
 *          @if MBUS_PRIMARY_DEVICE_DOC
 *          The table below shows which information needs to be provided. \n
 *          | deviceType                    | Pointer typ of pParam                   |
 *          |:-----------------------------:|:---------------------------------------:|
 *          | @ref E_STACK_DEVICE_SECONDARY |  @ref stack_mbusPrimaryAddDevice_t      |
 *          @endif
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_addDevice(stackDevice_t deviceType, void *pParam );

/*============================================================================*/
/*!
 * @brief   Function to remove a device from a specified stack.
 *
 * @details This functionality is only available if one of the following stack's
 *          is part of the delivery: \n
 *          - @ref E_STACK_ID_MBUS_PRIMARY
 *
 * @param   deviceType Specifies which type of device shall be removed. \n
 *          @copydetails stackDevice_t
 *
 * @param   pParam Pointer to the information required to remove a device.
 *          The information which needs to be provided are depending on the
 *          param deviceType.
 *          @if MBUS_PRIMARY_DEVICE_DOC
 *          The table below shows which information needs to be provided. \n
 *          | deviceType                    | Pointer typ of pParam                   |
 *          |:---------------------    ----:|:---------------------------------------:|
 *          | @ref E_STACK_DEVICE_SECONDARY |  @ref stack_mbusPrimaryRemoveDevice_t   |
 *          @endif
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_removeDevice(stackDevice_t deviceType, void *pParam );


/*!@} end of MS_COM_IF */
/******************************************************************************/

#endif /* __SF_STACK_H__ */
#ifdef __cplusplus
}
#endif
