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
* @copyright  STACKFORCE GmbH, Germany, http://www.stackforce.de
* @author     STACKFORCE
* @brief      Header for the RTOS uart implementation.
*/
#ifndef __SF_DRV_UART_H__
#define __SF_DRV_UART_H__

/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/
/******************************************************************************/
/**
  @brief  Close the uart handle to save energy
*/
void sf_stack_hal_serial_close(void);
/**
  @brief  Task which handles the uart communication.
*/
void sf_stack_hal_serial_taskInit(void);

#endif /* __SF_DRV_UART_H__ */
