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
 * @brief      API non blocking extension definition of the STACKFORCE Stack.
 *
 */

#ifndef __SF_STACK_NB_H__
#define __SF_STACK_NB_H__


/*! @defgroup MS_COM_IF_EX Stack Common Non-Blocking API
 *
 *  @details
 *
 *  - <b>Stack Common Non-Blocking API</b>\n
 *    | API Function                     | Description                         |
 *    |----------------------------------|-------------------------------------|
 *    | @ref sf_stack_nb_send()          | @copybrief sf_stack_nb_send()       |
 *    | @ref sf_stack_nb_process()       | @copybrief sf_stack_nb_process()    |
 *    | @ref sf_stack_nb_isBusy()        | @copybrief sf_stack_nb_isBusy()     |
 *  @{
 */

/*==============================================================================
                            DEFINES
==============================================================================*/
#include <stdint.h>
#include <stddef.h>

#include "sf_stack_types.h"

/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/
/*! @brief Definition of stack states return codes.
 *  @details
 *    <b>Stack state codes.</b> [1 Byte] \n
 *    > @copydetails E_STACK_STATE_IDLE \n
 *    > @copydetails E_STACK_STATE_BUSY_PROCESS \n
 *    > @copydetails E_STACK_STATE_BUSY_SLEEP \n
 *    > @copydetails E_STACK_STATE_BUSY_DEEP_SLEEP \n
*/
typedef enum
{
  /*!
  * <b>0x00 : @ref E_STACK_STATE_IDLE - Stack is idle, all operations are finished </b>
  */
  E_STACK_STATE_IDLE = 0x00,
  /*!
  * <b>0x01 : @ref E_STACK_STATE_BUSY_PROCESS - Stack is busy, and the application shall
  * call the function \ref sf_stack_nb_process. </b>
  */
  E_STACK_STATE_BUSY_PROCESS = 0x01,
  /*!
   * <b>0x02 : @ref E_STACK_STATE_BUSY_SLEEP - Stack is busy, only sleep state is allowed</b>
   */
  E_STACK_STATE_BUSY_SLEEP = 0x02,
  /*!
   * <b>0x03 : @ref E_STACK_STATE_BUSY_DEEP_SLEEP - Stack is busy, deep sleep state is allowed</b>
   */
  E_STACK_STATE_BUSY_DEEP_SLEEP = 0x03
} stackState_t;

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/*!
 * @brief  Send function for non-blocking operation.
 *
 * @param  len    Number of bytes to be sent.
 * @param  pData  Pointer to the data to be sent.
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_nb_send( uint16_t len, uint8_t *pData );

/*============================================================================*/
/*!
 * @brief  Process function.
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
/*============================================================================*/
stackReturn_t sf_stack_nb_process( void );

/*============================================================================*/
/*!
 * @brief  Function to verify if the stack is busy.
 *
 * @return Status of the stack. \n
 *         @copydetails stackState_t
 */
/*============================================================================*/
stackState_t sf_stack_nb_isBusy( void );

/*!@} end of MS_COM_IF_EX */
/******************************************************************************/

#endif /* __SF_STACK_NB_H__ */
#ifdef __cplusplus
}
#endif
