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
 @brief      STACKFORCE stack HAL for timer implementation.

*/

/*==============================================================================
                                INCLUDES
==============================================================================*/
#include "sf_stack_hal_timer.h"
#include "sf_drv_clock.h"
#include "sf_app_hal_lp.h"

 /*=============================================================================
                                 MACROS
 =============================================================================*/

 /*=============================================================================
                                 VARIABLES
 =============================================================================*/
static sf_stack_hal_timerCallback_t gfp_callback;
Clock_Handle gpTimerHandle = NULL;

/*==============================================================================
                        LOCAL FUNCTION DECLARATION
==============================================================================*/
static void loc_stackTimerCallback(UArg arg);

/*==============================================================================
                       LOCAL FUNCTION IMPLEMENTATION
==============================================================================*/
/*============================================================================*/
/* loc_stackTimerCallback() */
/*============================================================================*/
static void loc_stackTimerCallback(UArg arg)
{
  if(gfp_callback)
  {
    gfp_callback(arg);
  }/* if */
}/* loc_stackTimerCallback() */

/*==============================================================================
                        API FUNCTION IMPLEMENTATION
==============================================================================*/
/*-----------------------------------------------------------------------------
  sf_stack_hal_timer_init()
-----------------------------------------------------------------------------*/
bool sf_stack_hal_timer_init(uint16_t ticksPerSecond)
{
  /* Return value of this function. */
  bool ret = false;
  /* Param for crating clock instance */
  Clock_Params clkParams;

  /** Variable to store the microseconds. */
  uint32_t microSec = 0U;

  /* Only create the clock handle if not already present. */
  if(NULL == gpTimerHandle)
  {
    /* Converts i_ticksPerSecond to system time units. */
    microSec = 100000 / (uint32_t)ticksPerSecond;

    /* Create a periodic Clock Instance with period = 50 system time units */
    Clock_Params_init(&clkParams);
    clkParams.arg = (microSec*10U);
    clkParams.period = microSec;
    clkParams.startFlag = false;

    gpTimerHandle = Clock_create(loc_stackTimerCallback, microSec, &clkParams, NULL);
    if(NULL != gpTimerHandle)
    {
        ret = true;
    }/* if */
  }/* if */
  else
  {
    /* Clock handle is already available. */
    ret = true;
  }/* else */

  return ret;
} /* sf_stack_hal_timer_init() */

/*-----------------------------------------------------------------------------
  sf_stack_hal_timer_setCallback()
-----------------------------------------------------------------------------*/
bool sf_stack_hal_timer_setCallback(sf_stack_hal_timerCallback_t tmr_cb)
{
  bool ret = false;

  if(NULL != tmr_cb)
  {
    gfp_callback = tmr_cb;
    ret = true;
  }/* if */

  return ret;
} /* sf_stack_hal_timer_setCallback() */

/*-----------------------------------------------------------------------------
  sf_stack_hal_timer_enable()
-----------------------------------------------------------------------------*/
void sf_stack_hal_timer_enable(void)
{
  Clock_start(gpTimerHandle);
} /* sf_stack_hal_timer_enable() */

/*-----------------------------------------------------------------------------
  sf_stack_hal_timer_disable()
-----------------------------------------------------------------------------*/
void sf_stack_hal_timer_disable(void)
{
  Clock_stop(gpTimerHandle);
} /* sf_stack_hal_timer_disable() */

