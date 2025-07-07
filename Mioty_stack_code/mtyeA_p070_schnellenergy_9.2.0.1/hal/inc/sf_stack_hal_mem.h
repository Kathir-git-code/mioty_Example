#ifdef __cplusplus
extern "C" {
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
 * @brief      Stack HAL for non-volatile memory.
 *
 */

#ifndef __SF_STACK_HAL_MEM_H__
#define __SF_STACK_HAL_MEM_H__

/**
 *  @addtogroup SF_STACK_HAL
 *
 *  @details
 *
 *  - <b>Non-Volatile Memory API</b>\n
 *    | API Function                     | Description                          |
 *    |----------------------------------|--------------------------------------|
 *    | @ref sf_stack_hal_mem_getRAM()   | @copybrief sf_stack_hal_mem_getRAM   |
 *
 *  @{
 */

#include <stdint.h>
#include <stdbool.h>

/*============================================================================*/
/*!
 * @brief  The purpose of this function is to query RAM. The stack will use it
 *         to dynamically allocate memory for internal usage. This memory
 *         can be reused in case the stack is idle.
 *
 * @param  size       Size of the RAM area in bytes.
 *
 * @return Returns a pointer to the memory.
 */
/*============================================================================*/
void* sf_stack_hal_mem_getRAM( uint32_t* size );

/**@} end of SF_STACK_HAL */
/******************************************************************************/

#endif /* __SF_STACK_HAL_MEM_H__ */
#ifdef __cplusplus
}
#endif
