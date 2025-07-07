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
 @brief      STACKFORCE app HAL for the application timer.

*/

#ifndef __SF_APP_HAL_TIMER_H__
#define __SF_APP_HAL_TIMER_H__

/**
 *  @defgroup SF_APP_HAL APP HAL
 *
 *  @details
 *
 *  - Application Programming Interface (API) of the <b>Application timer</b>\n
 *    | API Function                            | Description                                 |
 *    |-----------------------------------------|---------------------------------------------|
 *    | @ref sf_app_hal_timer_init()            | @copybrief sf_app_hal_timer_init            |
 *    | @ref sf_app_hal_timer_start()           | @copybrief sf_app_hal_timer_start           |
 *    | @ref sf_app_hal_timer_stop()            | @copybrief sf_app_hal_timer_stop            |
 *  @{
 */

#include <stdint.h>
#include <stdbool.h>

/**
  @brief Function pointer to a callback function for a timer event.
 */
typedef void (*sf_app_hal_timerCallback_t)(void* pCtx);

/**
  @brief  Initializes the example app timer.
*/
bool sf_app_hal_timer_init( void );

/**
  @brief   Start the timer.

  @param   timeout   Timeout for the timer in seconds
  @param   callback  Pointer to callback function that should be called when
                     timer expires.

  @return Returns true, if successful, false otherwise.
*/
bool sf_app_hal_timer_start( uint16_t timeout,
                             sf_app_hal_timerCallback_t callback );

/**
  @brief  Stop the timer.

  @return Returns true, if successful, false otherwise.
*/
bool sf_app_hal_timer_stop( void );

/**@} end of SF_APP_HAL */
/******************************************************************************/

#endif

#ifdef __cplusplus
}
#endif
