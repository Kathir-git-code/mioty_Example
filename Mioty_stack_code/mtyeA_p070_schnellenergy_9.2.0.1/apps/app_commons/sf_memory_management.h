#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file
 * @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 * @author     STACKFORCE
 * @brief      Stack application memory extensions
 *
 */

#ifndef __SF_MEMORY_MANAGEMENT_H__
#define __SF_MEMORY_MANAGEMENT_H__

/**
 *  @defgroup SF_MEMORY_MANAGEMENT Stackforce Stack application extension interface
 *
 *  @details
 *
 *  - Application Programming Interface (API) of the <b>Stack application extensions</b>\n
 *    | API Function                                    | Description                                         |
 *    |-------------------------------------------------|-----------------------------------------------------|
 *    | @ref sf_memory_management_init()                | @copybrief sf_memory_management_init                |
 *    | @ref sf_memory_management_readNvm()             | @copybrief sf_memory_management_readNvm             |
 *    | @ref sf_memory_management_writeNvm()            | @copybrief sf_memory_management_writeNvm            |
 *  @{
 */

#include <stdbool.h>
#include "sf_stack_types.h"

/**
  @brief  Initializes the stacks with NVM driver.
*/
void sf_memory_management_init( void );

/**
  @brief  Initializes the stacks with NVM data, if possible.

  @param  nbStacks Number of stacks
  @param  stacks   List of stacks

  @return Status of the operation. \n
          @copydetails stackReturn_t
*/
stackReturn_t sf_memory_management_readNvm( uint8_t nbStacks, uint8_t* stacks );

/**
  @brief  Writes stack data of the current active stack into the NVM.

  @return Status of the operation. \n
          @copydetails stackReturn_t
 */
stackReturn_t sf_memory_management_writeNvm( void );

/**@} end of SF_MEMORY_MANAGEMENT */
/******************************************************************************/

#endif // __SF_MEMORY_MANAGEMENT_H__

#ifdef __cplusplus
}
#endif
