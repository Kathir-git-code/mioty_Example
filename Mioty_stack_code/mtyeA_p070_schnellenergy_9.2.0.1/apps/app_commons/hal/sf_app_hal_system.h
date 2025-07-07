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
 @brief      STACKFORCE app HAL for main system.

*/

#ifndef __SF_APP_HAL_SYSTEM_H__
#define __SF_APP_HAL_SYSTEM_H__

/**
 *  @defgroup SF_APP_HAL APP HAL
 *
 *  @details
 *
 *  - Application Programming Interface (API) of the <b>Main system</b>\n
 *    | API Function                                | Description                                     |
 *    |---------------------------------------------|-------------------------------------------------|
 *    | @ref sf_app_hal_system_init()               | @copybrief sf_app_hal_system_init               |
 *    | @ref sf_app_hal_system_errorHandler()       | @copybrief sf_app_hal_system_errorHandler       |

 *  @{
 */

#include <stdint.h>

/**
  @brief  Initialization of the system.
*/
void sf_app_hal_system_init( void );

/**
  @brief  Configuration of the clock system after leaving lpm.
*/
void sf_app_hal_system_clockConfig( void );

/**
  @brief  Example error handler.
*/
void sf_app_hal_system_errorHandler( void );

/**@} end of SF_APP_HAL */
/******************************************************************************/

#endif

#ifdef __cplusplus
}
#endif
