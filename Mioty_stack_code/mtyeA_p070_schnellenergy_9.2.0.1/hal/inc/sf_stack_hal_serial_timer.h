#ifdef __cplusplus
extern "C" {
#endif

/*!
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
 * @author     STACKFORCE GmbH
 * @brief      Stack HAL for serial timer.
 */


#ifndef __SF_STACK_HAL_SERIAL_TIMER_H__
#define __SF_STACK_HAL_SERIAL_TIMER_H__

/**
 *  @addtogroup SF_STACK_HAL
 *
 *  @details
 *
 *  - <b>Serial Timer API</b>\n
 *    | API Function                                        | Description                                             |
 *    |-----------------------------------------------------|---------------------------------------------------------|
 *    | @ref sf_stack_hal_serial_timer_init()                  | @copybrief sf_stack_hal_serial_timer_init                  |
 *    | @ref sf_stack_hal_serial_timer_start()                 | @copybrief sf_stack_hal_serial_timer_start                 |
 *    | @ref sf_stack_hal_serial_timer_stop()                  | @copybrief sf_stack_hal_serial_timer_stop                  |
 *
 *  @{
 */

#include "stdint.h"
#include "stdbool.h"

/*============================================================================*/
/*!
 * @brief  Function pointer to a callback function for a timer event.
 *
 * @param  pCtx Data which can be passed to the callback function.
 */
/*============================================================================*/
typedef void ( *sf_stack_hal_serial_timer_callback_t )( void* pCtx );

/*============================================================================*/
/*!
 * @brief  Initializes the serial timer.
 *
 * @return true if success, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_serial_timer_init( void );

/*============================================================================*/
/*!
 * @brief Starts the serial timer.
 *
 * @param i_timeout      Timeout value in milliseconds.
 * @param fp_callback    Pointer to callback function that should be called
 *                       when the timer expires.
 */
/*============================================================================*/
void sf_stack_hal_serial_timer_start( uint32_t i_timeout,
                                      sf_stack_hal_serial_timer_callback_t fp_callback );

/*============================================================================*/
/*!
 * @brief Stops the serial timer.
 */
/*============================================================================*/
void sf_stack_hal_serial_timer_stop( void );

/**@} end of SF_STACK_HAL */
/******************************************************************************/

#endif /* __SF_STACK_HAL_SERIAL_TIMER_H__ */
#ifdef __cplusplus
}
#endif
