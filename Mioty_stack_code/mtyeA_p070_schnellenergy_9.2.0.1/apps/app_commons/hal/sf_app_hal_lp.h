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
 @brief      STACKFORCE app HAL for low power.

*/

#ifndef __SF_APP_HAL_LP_H__
#define __SF_APP_HAL_LP_H__

/**
 *  @defgroup SF_APP_HAL APP HAL
 *
 *  @details
 *
 *  - Application Programming Interface (API) of the <b>Low power</b>\n
 *    | API Function                                | Description                                     |
 *    |---------------------------------------------|-------------------------------------------------|
 *    | @ref sf_app_hal_lp_init()                   | @copybrief sf_app_hal_lp_init                   |
 *    | @ref sf_app_hal_lp_enterSleep()             | @copybrief sf_app_hal_lp_enterSleep             |
 *    | @ref sf_app_hal_lp_enterDeepSleep()         | @copybrief sf_app_hal_lp_enterDeepSleep         |
 *    | @ref sf_app_hal_lp_wakeup()                 | @copybrief sf_app_hal_lp_wakeup                 |
 *  @{
 */

/**
  @brief  Initializes app low power HAL.
*/
void sf_app_hal_lp_init( void );

/**
  @brief  Enters sleep mode without RAM loss.
*/
void sf_app_hal_lp_enterSleep( void );

/**
  @brief  Enters deep sleep mode with RAM loss.
*/
void sf_app_hal_lp_enterDeepSleep( void );

/**
  @brief  Wakes up from sleep mode.
*/
void sf_app_hal_lp_wakeup( void );

/**@} end of SF_APP_HAL */
/******************************************************************************/

#endif

#ifdef __cplusplus
}
#endif
