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
 @brief      Stack hal timer implementation.

*/

/*==============================================================================
                                INCLUDES
==============================================================================*/
#include "sf_app_hal_timer.h"
#include "sf_drv_clock.h"

 /*=============================================================================
                                 MACROS
 =============================================================================*/
#define SF_SEC_TO_US           1000000

 /*=============================================================================
                                 VARIABLES
 =============================================================================*/
static sf_app_hal_timerCallback_t gfp_callback;
Clock_Handle gpAppTimerHandle = NULL;

/*==============================================================================
                        LOCAL FUNCTION DECLARATION
==============================================================================*/
static void loc_timerCallback(UArg arg);

/*==============================================================================
                       LOCAL FUNCTION IMPLEMENTATION
==============================================================================*/
/*============================================================================*/
/* loc_timerCallback() */
/*============================================================================*/
static void loc_timerCallback(UArg arg)
{
  sf_drv_clock_stop(gpAppTimerHandle);

  if(gfp_callback)
  {
    gfp_callback(NULL);
  }
}/* loc_timerCallback() */

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/* sf_app_hal_timer_init() */
/*============================================================================*/
bool sf_app_hal_timer_init(void)
{
  /* Return value of this function. */
  bool ret = true;

  if(NULL == gpAppTimerHandle)
  {
    gpAppTimerHandle = sf_drv_clock_init();

    if(NULL == gpAppTimerHandle)
    {
      ret = false;
    }/* if */
  }/* if */
  return ret;
}/* sf_app_hal_timer_init() */

/*============================================================================*/
/* sf_app_hal_timer_start() */
/*============================================================================*/
bool sf_app_hal_timer_start(uint16_t timeout,
                            sf_app_hal_timerCallback_t callback)
{
  bool ret = false;

  if(timeout <= 0xFFFFFFFF/SF_SEC_TO_US)
  {

    gfp_callback = callback;
    ret = sf_drv_clock_start(gpAppTimerHandle,
                             (uint32_t)(timeout * SF_SEC_TO_US),
                             loc_timerCallback);
  }/* if */
  return ret;
}/* sf_app_hal_timer_start() */

#ifdef __cplusplus
}
#endif
