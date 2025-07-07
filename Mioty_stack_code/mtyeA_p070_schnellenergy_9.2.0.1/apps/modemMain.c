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
 @brief      Example main application for the serial interface of Stack API.

 @example    modemMain.c
             Example for the serial API usage of the stack.
*/

#include "sf_app_hal_lp.h"
#include "sf_app_hal_system.h"
#include "sf_app_hal.h"
#include "sf_stack.h"
#include "sf_stack_serial.h"
#include "sf_stack_nb.h"
#include "sf_memory_management.h"


/*==============================================================================
                          DEFINES
==============================================================================*/
#ifndef SF_STACK_NUMBER
/*! The definitions SF_STACK_NUMBER is available in the CMakeLists.txt */
#define SF_STACK_NUMBER                 0
#endif

#ifndef SF_STACK_LIST
/*! The definitions SF_STACK_LIST is available in the CMakeLists.txt */
#define SF_STACK_LIST                   { E_STACK_ID_NONE }
#endif

/*==============================================================================
                          LOCAL FUNCTIONS
==============================================================================*/
/*============================================================================*/
/*! _handleSleep( ) */
/*============================================================================*/
static void _handleSleep(void)
{
  stackState_t stackState = sf_stack_nb_isBusy();
  if( stackState == E_STACK_STATE_BUSY_PROCESS )
  {
    sf_stack_nb_process( );
  }
  else if( ( stackState == E_STACK_STATE_BUSY_SLEEP ) &&
           ( true == sf_stack_serial_isIdle( ) ) )
  {
    /* Enable low power. */
    sf_app_hal_lp_enterSleep( );
  }
  else if( ( ( stackState == E_STACK_STATE_BUSY_DEEP_SLEEP ) ||
           ( stackState == E_STACK_STATE_IDLE ) ) &&
           ( true == sf_stack_serial_isIdle( ) ) )
  {
    /* Enable low power. */
    sf_app_hal_lp_enterDeepSleep( );
  }
}

/*============================================================================*/
/*!
 * @brief  Callback function definition of the stack. This function will be
 *         passed to the stack initialization function as parameter. The stack
 *         uses this callback to inform the application layer about event.
 *
 * @param  event    Defines the event which occurred.
 * @param  data     A pointer to data. The pointer can be NULL, as not
 *                  every event requires data.
 * @param  dataLen  The length of the data. Can be zero.
 *
 * @return The return value shall be E_STACK_RETURN_SUCCESS.
 */
/*============================================================================*/
stackReturn_t _stackCallback( stackEvent_t event, uint8_t *data, uint16_t dataLen )
{
  stackReturn_t e_return = E_STACK_RETURN_SUCCESS;

  switch( event )
  {
    case E_STACK_EVENT_PERSISTENT_DATA_UPDATE:
      break;

    case E_STACK_EVENT_TX_SUCCESS:
      break;

    case E_STACK_EVENT_CRYPTO_ERROR:
      break;

    case E_STACK_EVENT_RX_SUCCESS:
      break;

    case E_STACK_EVENT_SLEEP:
      sf_app_hal_lp_enterSleep( );
      break;

    case E_STACK_EVENT_DEEP_SLEEP:
      sf_app_hal_lp_enterDeepSleep( );
      break;

    case E_STACK_EVENT_WAKEUP:
      sf_app_hal_lp_wakeup();
      break;

    case E_STACK_EVENT_SERIAL_CONFIRM_FAIL:
      break;

    case E_STACK_EVENT_SERIAL_CONFIRM_SUCCESS:
      break;

    default:
      break;
  }

  sf_stack_serial_action(event, data, dataLen);

  return e_return;
}

/*============================================================================*/
/*!
 * @brief Callback function to inform application about incoming serial frames
 *        with the CUSTOMER STACK ID.
 *
 * @param pData Pointer to data that are received.
 *
 * @param len   Length of the data which have been received.
 *
 * @param pResp Pointer to a data buffer which shall be sent as response.
 *
 * @param pRespLen Length of the data which shall be sent as a response.
 *
 * @return The return value shall be E_STACK_RETURN_SUCCESS.
 */
/*============================================================================*/
stackReturn_t _serialManufacturerCommandCb( uint8_t* pData, uint16_t len,
                                            uint8_t **pResp, uint16_t* pRespLen )
{
  stackReturn_t ret = E_STACK_RETURN_ERROR_INVALID_PARAM;

  if( len > 0 )
  {
    if( pData[0] == 0x02 )
    {
      /* Write NVM */
      ret = sf_memory_management_writeNvm( );
    }
  }

  return ret;
}

/*=============================================================================
                                EXAMPLE MAIN
=============================================================================*/
/*============================================================================*/
/*!
 * @brief Serial main function.
 */
/*============================================================================*/
void exampleMain(void)
{
  uint8_t stacks[] = SF_STACK_LIST;

  sf_app_hal_init( );
  sf_memory_management_init( );

  /* Initialize the stack API */
  if( E_STACK_RETURN_SUCCESS != sf_stack_init( _stackCallback ) )
  {
    sf_app_hal_system_errorHandler( );
  }

  /* Initialize the serial stack API */
  if( E_STACK_RETURN_SUCCESS != sf_stack_serial_init( _serialManufacturerCommandCb ) )
  {
    sf_app_hal_system_errorHandler( );
  }

  /* Initializes the stacks with NVM data, if possible. */
  sf_memory_management_readNvm( SF_STACK_NUMBER, stacks );

  while( 1 )
  {
    sf_stack_serial_run();

    _handleSleep();
  }
}

/*=============================================================================
                                MAIN FUNCTION
=============================================================================*/
/* The macro SF_USE_RTOS_APPLICATION can be used to disable this main function
 * in order to replace it by an RTOS specific implementation. */
#ifndef SF_USE_RTOS_APPLICATION
/*============================================================================*/
/*!
 * @brief Main function.
 */
/*============================================================================*/
int main( void )
{
  exampleMain();
  return 0;
}
#endif /* SF_USE_RTOS_APPLICATION */

#ifdef __cplusplus
}
#endif
