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
 @brief      STACKFORCE app HAL for initialization.

*/

#ifndef __SF_APP_HAL_H__
#define __SF_APP_HAL_H__

/**
 *  @defgroup SF_APP_HAL Stackforce example HAL interface
 *
 *  @details
 *
 *  - Application Programming Interface (API) for the <b>Initialization</b>\n
 *    | API Function             | Description                 |
 *    |--------------------------|-----------------------------|
 *    | @ref sf_app_hal_init()   | @copybrief sf_app_hal_init  |
 *  @{
 */

#include <stdint.h>
#include <stdbool.h>

/**
  @brief  Initializes all app HAL.

  @return Returns true, if successfully, false otherwise.
*/
bool sf_app_hal_init( void );

/**@} end of SF_APP_HAL */
/******************************************************************************/

#endif

#ifdef __cplusplus
}
#endif
