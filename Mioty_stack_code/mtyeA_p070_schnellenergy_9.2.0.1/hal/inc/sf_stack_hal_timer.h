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
 * @brief      Stack HAL for the timer.
 *
 */

#ifndef __SF_STACK_HAL_TIMER_H__
#define __SF_STACK_HAL_TIMER_H__

/**
 *  @addtogroup SF_STACK_HAL
 *
 *  @details
 *
 *  - <b>Timer API</b>\n
 *    | API Function                          | Description                               |
 *    |---------------------------------------|-------------------------------------------|
 *    | @ref sf_stack_hal_timer_init()        | @copybrief sf_stack_hal_timer_init        |
 *    | @ref sf_stack_hal_timer_setCallback() | @copybrief sf_stack_hal_timer_setCallback |
 *    | @ref sf_stack_hal_timer_enable()      | @copybrief sf_stack_hal_timer_enable      |
 *    | @ref sf_stack_hal_timer_disable()     | @copybrief sf_stack_hal_timer_disable     |
 *  @{
 */

#include <stdint.h>
#include <stdbool.h>

/*============================================================================*/
/*!
 * @brief  Callback which indicates a timer event.
 *
 * @param  count Elapsed time in micro-seconds.
 *
 * @return Returns true, if the sleep device shall wake up.
 */
/*============================================================================*/
typedef bool ( *sf_stack_hal_timerCallback_t )( uint32_t count );

/*============================================================================*/
/*!
 * @brief  Initializes example timer.
 *
 * @param  ticksPerSecond Timer interrupt period.
 */
/*============================================================================*/
bool sf_stack_hal_timer_init( uint16_t ticksPerSecond );

/*============================================================================*/
/*!
 * @brief  Sets the callback for the timer event.
 *
 * @param  tmr_cb Function to call in case of an interrupt.
 *
 * @return Returns true, if successfully, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_timer_setCallback( sf_stack_hal_timerCallback_t tmr_cb );

/*============================================================================*/
/*!
 * @brief  Enables the timer.
 */
/*============================================================================*/
void sf_stack_hal_timer_enable( void );

/*============================================================================*/
/*!
 * @brief  Disables the timer.
 */
/*============================================================================*/
void sf_stack_hal_timer_disable( void );

/**@} end of SF_STACK_HAL */
/******************************************************************************/

#endif /* __SF_STACK_HAL_TIMER_H__ */
#ifdef __cplusplus
}
#endif
