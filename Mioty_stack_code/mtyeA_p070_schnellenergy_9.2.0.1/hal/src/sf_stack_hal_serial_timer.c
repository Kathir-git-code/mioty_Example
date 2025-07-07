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
 @brief      Serial timer implementation.

*/

/*==============================================================================
                                INCLUDES
==============================================================================*/
#include "sf_stack_hal_serial_timer.h"
#include "sf_drv_clock.h"

 /*=============================================================================
                                 MACROS
 =============================================================================*/
#define SF_MS_TO_US              1000
 /*=============================================================================
                                 VARIABLES
 =============================================================================*/
static sf_stack_hal_serial_timer_callback_t gfp_callback;
Clock_Handle gpSerialTimerHandle = NULL;

/*==============================================================================
                        LOCAL FUNCTION DECLARATION
==============================================================================*/
static void loc_serialTimerCallback(UArg arg);

/*==============================================================================
                       LOCAL FUNCTION IMPLEMENTATION
==============================================================================*/
/*============================================================================*/
/* loc_serialTimerCallback() */
/*============================================================================*/
static void loc_serialTimerCallback(UArg arg)
{
  sf_drv_clock_stop(gpSerialTimerHandle);

  if(gfp_callback)
  {
    gfp_callback(NULL);
  }
}/* loc_serialTimerCallback() */

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/* sf_app_hal_timer_init() */
/*============================================================================*/
bool sf_stack_hal_serial_timer_init(void)
{
  /* Return value of this function. */
  bool ret = true;

  if(NULL == gpSerialTimerHandle)
  {
    gpSerialTimerHandle = sf_drv_clock_init();

    if(NULL == gpSerialTimerHandle)
    {
      ret = false;
    }/* if */
  }/* if */
  return ret;
}/* sf_app_hal_timer_init() */

/*============================================================================*/
/* sf_app_hal_timer_start() */
/*============================================================================*/
void sf_stack_hal_serial_timer_start(uint32_t timeout,
                                     sf_stack_hal_serial_timer_callback_t callback)
{
  gfp_callback = callback;
  sf_drv_clock_start(gpSerialTimerHandle, timeout * SF_MS_TO_US,
                     loc_serialTimerCallback);
}/* sf_app_hal_timer_start() */

/*============================================================================*/
/* sf_stack_hal_serial_timer_stop() */
/*============================================================================*/
void sf_stack_hal_serial_timer_stop( void )
{
  sf_drv_clock_stop(gpSerialTimerHandle);
}/* sf_stack_hal_serial_timer_stop() */

#ifdef __cplusplus
}
#endif
