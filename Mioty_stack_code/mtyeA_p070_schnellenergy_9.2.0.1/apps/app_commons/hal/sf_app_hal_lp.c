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

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
#include <stdbool.h>
#include "sf_app_hal_lp.h"

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>

/*==============================================================================
                             VARIABLES
==============================================================================*/
static Semaphore_Struct semUpdateTriggerStruct;
static Semaphore_Params semUpdateTriggerParams;
Semaphore_Handle semUpdateTriggerHandle;
static bool gInitialized = false;

/*==============================================================================
                          API  FUNCTIONS
==============================================================================*/
/*============================================================================*/
/* sf_app_hal_lp_init() */
/*============================================================================*/
void sf_app_hal_lp_init( void )
{
  if( !gInitialized )
  {
    /* Initialize semaphore and construct a semaphore object. */
    Semaphore_Params_init(&semUpdateTriggerParams);
    semUpdateTriggerParams.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&semUpdateTriggerStruct, 0, &semUpdateTriggerParams);
    semUpdateTriggerHandle = Semaphore_handle(&semUpdateTriggerStruct);

    gInitialized = true;
  }
}/* sf_app_hal_lp_init() */

/*============================================================================*/
/* sf_app_hal_lp_enterSleep() */
/*============================================================================*/
void sf_app_hal_lp_enterSleep( void )
{
  /* Ensure that the stack task will be blocked here */
  while(Semaphore_getCount(semUpdateTriggerHandle) > 0x00U)
  {
    Semaphore_pend(semUpdateTriggerHandle, BIOS_WAIT_FOREVER);
  }/* while */

  /* Block the task until an event occurred */
  Semaphore_pend(semUpdateTriggerHandle, BIOS_WAIT_FOREVER);
}/* sf_app_hal_lp_enterSleep() */

/*============================================================================*/
/* sf_app_hal_lp_enterDeepSleep() */
/*============================================================================*/
void sf_app_hal_lp_enterDeepSleep( void )
{
  /* The RTOS will take care about the possible depth of the sleep mode
   * so we don't need to differentiate. */
    sf_app_hal_lp_enterSleep();
}/* sf_app_hal_lp_enterDeepSleep */

/*============================================================================*/
/* sf_app_hal_lp_wakeup() */
/*============================================================================*/
void sf_app_hal_lp_wakeup( void )
{
  Semaphore_post(semUpdateTriggerHandle);
}/* sf_app_hal_lp_wakeup */

#ifdef __cplusplus
}
#endif
