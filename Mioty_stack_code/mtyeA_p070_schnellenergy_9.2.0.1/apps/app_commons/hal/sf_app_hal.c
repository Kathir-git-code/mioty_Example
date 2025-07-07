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
 @brief      STACKFORCE app HAL for init.

*/

/*==============================================================================
                            INCLUDES
==============================================================================*/
#include "sf_app_hal.h"
#include "sf_app_hal_lp.h"
#include "sf_app_hal_timer.h"
/*==============================================================================
                            FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*! sf_app_hal_init() */
/*============================================================================*/
bool sf_app_hal_init( void )
{
  sf_app_hal_lp_init();
  sf_app_hal_timer_init();

  return true;
}/* sf_app_hal_init() */

#ifdef __cplusplus
}
#endif
