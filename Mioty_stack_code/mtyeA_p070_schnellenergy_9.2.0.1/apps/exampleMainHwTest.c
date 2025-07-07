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
 @brief      Example main which demonstrated how to use the hw test extension.

 @example    exampleMainHwTest.c
             This example implements a simple hw test sequence.
*/

/*=============================================================================
                                INCLUDES
=============================================================================*/
/* Standard libraries */
#include <stdint.h>
#include <stdbool.h>

#include "sf_app_hal.h"
#include "sf_app_hal_system.h"
#include "sf_app_hal_timer.h"
#include "sf_hw_test.h"
#include "exampleMain.h"


/*=============================================================================
                                MACROS
==============================================================================*/
#ifndef SF_HW_TEST_FREQ_IN_HZ
/*! Defines the frequency used inside this demo. Default we select 868,1 MHz. */
#define SF_HW_TEST_FREQ_IN_HZ          868100000
#endif /* SF_HW_TEST_FREQ_IN_HZ */

/*! Defines the tx power used inside this demo. Default we select 14dBm. */
#define SF_HW_TEST_TX_POWER            14
/*! Defines the test time used inside this demo. Default we select 10 seconds. */
#define SF_HW_TEST_TIME_IN_SECONDS     10

/*=============================================================================
                          GLOBAL VARIABLES
=============================================================================*/
/*! Boolean used to indicate that the HW-test can be stoped. */
volatile bool gHwTestTimerExpired;

/*============================================================================*/
/*!
 * @brief  Callback function definition of the timer. This callback function
 *         sets a status to initiate another transmission.
 *
 * @param  pCtx    A pointer to a potential data context.
 */
/*============================================================================*/
static void loc_timerCallback( void* pCtx )
{
  gHwTestTimerExpired = true;
}

/*============================================================================*/
/*!
 * @brief  Execute a hw test for a defined time.
 *
 * @param  timeInSeconds  Time the device should stay in the selected test mode.
 */
/*============================================================================*/
void loc_executeHwTestMode( uint8_t timeInSeconds )
{
  /* Reset global isr flag. */
  gHwTestTimerExpired = false;

  /* Start a timer */
  if( true != sf_app_hal_timer_start(timeInSeconds, loc_timerCallback))
  {
    sf_app_hal_system_errorHandler();
  }

  while(false == gHwTestTimerExpired)
  {
    /* Wait till the hw test timer expires. */
  }

  /* Stop the hw test. */
  sf_hw_test_stop();
}

/*============================================================================*/
/*!
 * @brief  Main loop function.
 *         Executes an example of the hardware tests.
 */
/*============================================================================*/
void exampleMain(void)
{
  /* Initialize the MCU */
  sf_app_hal_init();

  /* Starts an unmodulated continuous wave test */
  if(E_HW_TEST_RETURN_SUCCESS != sf_hw_test_startTxCw(SF_HW_TEST_FREQ_IN_HZ, SF_HW_TEST_TX_POWER))
  {
    sf_app_hal_system_errorHandler();
  }
  loc_executeHwTestMode( SF_HW_TEST_TIME_IN_SECONDS );

  while(1)
  {
    /* Loops here after demo is finished */
  }
}

/*============================================================================*/
/*!
 * @brief  Main function.
 */
/*============================================================================*/
#ifndef SF_USE_RTOS_APPLICATION
int main(void)
{
  exampleMain();
  return 0;
}
#endif /* SF_USE_RTOS_APPLICATION */

#ifdef __cplusplus
}/* exampleMain() */
#endif
