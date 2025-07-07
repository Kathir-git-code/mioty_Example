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
 @brief      Stack memory extensions.

*/

#include "sf_memory_management.h"
#include "sf_stack.h"
#include "sf_app_hal_mem.h"

/*=============================================================================
                                DEFINES
=============================================================================*/
/** Address offset where the lora stack data starts. */
#ifndef SF_STACK_WMBUS_NVM_OFFSET
#define SF_STACK_WMBUS_NVM_OFFSET              0x00U
#endif

#ifndef SF_STACK_MBUS_OVER_LORA_NVM_OFFSET
#define SF_STACK_MBUS_OVER_LORA_NVM_OFFSET     0x80U
#endif

#ifndef SF_STACK_LORA_NVM_OFFSET
#define SF_STACK_LORA_NVM_OFFSET               0x100U
#endif

/*=============================================================================
                        LOCAL FUNCTION IMPLEMENTATIONS
=============================================================================*/

/*============================================================================*/
/*!
 * @brief  Gets the NVM data offset for the current stack.
 *
 * @param activeStack Active stack, offset will be selected with this param
 *
 * @return The offset for the current stack.
 */
/*============================================================================*/
static uint16_t loc_getNvmOffset( stackId_t activeStack )
{
  uint16_t offset = 0;

  switch (activeStack)
  {
    case E_STACK_ID_LORAWAN:
      offset = SF_STACK_LORA_NVM_OFFSET;
      break;
    case E_STACK_ID_MIOTY:
      /* Not yet supported */
      break;
    case E_STACK_ID_WMBUS:
      offset = SF_STACK_WMBUS_NVM_OFFSET;
      break;
    case E_STACK_ID_SIGFOX:
      /* Not yet supported */
      break;
    case E_STACK_ID_MBUS_OVER_LORAWAN:
      /* The MBus over LoRaWAN stack is only the M-Bus data. */
      offset = SF_STACK_MBUS_OVER_LORA_NVM_OFFSET;
      break;
    default:
      /* Not yet supported */
      break;
  }

  return offset;
}

/*=============================================================================
                                API FUNCTION IMPLEMENTATIONS
=============================================================================*/
void sf_memory_management_init( void )
{
  sf_app_hal_mem_init( );
}

stackReturn_t sf_memory_management_readNvm( uint8_t nbStacks, uint8_t* stacks )
{
  stackReturn_t ret = E_STACK_RETURN_SUCCESS;
  uint16_t offset = 0;
  stackId_t activeStack;
  uint16_t stackDataSize = 0;
  uint8_t* nvm = NULL;

  if( ( stacks == NULL ) || ( nbStacks == 0 ) )
  {
    return E_STACK_RETURN_ERROR_INVALID_PARAM;
  }

  /* Loop to initialise all stacks */
  for( uint8_t i = 0; i < nbStacks; i++ )
  {
    /* Gets the active stack */
    activeStack = (stackId_t) stacks[i];
    /* Select the stack */
    if( E_STACK_RETURN_SUCCESS == sf_stack_selectStack( activeStack ) )
    {
      /* Gets the offset in the NVM that matches to the current stack */
      offset = loc_getNvmOffset( activeStack );
      /* Gets the size of the stack data context */
      sf_stack_pullConfig( &stackDataSize );

      /* Verify that the NVM is not flashed (check on 0x00 & 0xFF) */
      if( true == sf_app_hal_mem_isValid( offset, stackDataSize ) )
      {
        nvm = sf_app_hal_mem_get( offset );
        if( nvm != NULL )
        {
          ret = sf_stack_pushConfig( nvm, stackDataSize );
        }
      }
    }
  }
  return ret;
}

stackReturn_t sf_memory_management_writeNvm( void )
{
  stackReturn_t status = E_STACK_RETURN_ERROR;
  uint8_t* stackDataPtr = NULL;
  uint16_t stackDataSize = 0;
  stackId_t activeStack = sf_stack_getActiveStack( );

  /* Gets the pointer and the length of the stack data context */
  stackDataPtr = sf_stack_pullConfig( &stackDataSize );

  if( ( stackDataPtr != NULL ) && ( 0 != stackDataSize) )
  {
    /* Write the current stack data of the active stack into
       it's respective space in the NVM*/
    if( sf_app_hal_mem_write( stackDataPtr, stackDataSize,
                                loc_getNvmOffset( activeStack ) ) == stackDataSize )
    {
      status = E_STACK_RETURN_SUCCESS;
    }
    else
    {
      status = E_STACK_RETURN_ERROR_INVALID_PARAM;
    }
  }
  return status;
}

#ifdef __cplusplus
}
#endif
