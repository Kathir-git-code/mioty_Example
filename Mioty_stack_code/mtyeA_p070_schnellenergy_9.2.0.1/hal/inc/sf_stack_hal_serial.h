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
 * @brief      Stack HAL for the serial interface.
 *
 */

#ifndef __SF_STACK_HAL_SERIAL_H__
#define __SF_STACK_HAL_SERIAL_H__


/**
 *  @addtogroup SF_STACK_HAL
 *
 *  @details
 *
 *  - <b>Serial Interface API</b>\n
 *    | API Function                          | Description                                 |
 *    |---------------------------------------|---------------------------------------------|
 *    | @ref sf_stack_hal_serial_init()       | @copybrief sf_stack_hal_serial_init()       |
 *    | @ref sf_stack_hal_serial_write()      | @copybrief sf_stack_hal_serial_write()      |
 *    | @ref sf_stack_hal_serial_read()       | @copybrief sf_stack_hal_serial_read()       |
 *    | @ref sf_stack_hal_serial_cntRxBytes() | @copybrief sf_stack_hal_serial_cntRxBytes() |
 *    | @ref sf_stack_hal_serial_run()        | @copybrief sf_stack_hal_serial_run()        |
 *  @{
 */

#include <stdbool.h>
#include <stdint.h>


/*============================================================================*/
/*!
 * @brief  Initializes the serial interface.
 *
 * @return Returns true if initialization was successful.
 */
/*============================================================================*/
bool sf_stack_hal_serial_init( void );

/*============================================================================*/
/*!
 * @brief  Writes data to the UART.
 *
 * @param  pc_data   Pointer to the data to be sent.
 * @param  i_len     Number of bytes to be sent.
 * @return Returns the number of bytes successfully sent.
 */
/*============================================================================*/
uint16_t sf_stack_hal_serial_write( uint8_t *pc_data, uint16_t i_len );

/*============================================================================*/
/*!
 * @brief  Reads data from the UART.
 *
 * @param  pc_data   Pointer to the location where to store received data.
 * @param  i_len     Number of bytes to be read.
 * @return Number of successfully read bytes.
 */
/*============================================================================*/
uint16_t sf_stack_hal_serial_read( uint8_t *pc_data, uint16_t i_len );

/*============================================================================*/
/*!
 * @brief  Returns the number of ready-to-be-fetched bytes.
 *
 * @return Number of received bytes.
 */
/*============================================================================*/
uint16_t sf_stack_hal_serial_cntRxBytes( void );

/*============================================================================*/
/*!
 * @brief  Run the serial protocol state machine.
 */
/*============================================================================*/
void sf_stack_hal_serial_run( void );

/**@} end of SF_STACK_HAL */
/******************************************************************************/

#endif /* __SF_STACK_HAL_SERIAL_H__ */
#ifdef __cplusplus
}
#endif
