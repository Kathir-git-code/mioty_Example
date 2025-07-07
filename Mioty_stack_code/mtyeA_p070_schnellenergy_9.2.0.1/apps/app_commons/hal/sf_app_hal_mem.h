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

#ifndef __SF_APP_HAL_MEM_H__
#define __SF_APP_HAL_MEM_H__

/**
 *  @addtogroup SF_APP_HAL APP HAL API
 *
 *  @details
 *
 *  - <b>Non-Volatile Memory API</b>\n
 *    | API Function                     | Description                          |
 *    |----------------------------------|--------------------------------------|
 *    | @ref sf_app_hal_mem_init()       | @copybrief sf_app_hal_mem_init       |
 *    | @ref sf_app_hal_mem_write()      | @copybrief sf_app_hal_mem_write      |
 *    | @ref sf_app_hal_mem_read()       | @copybrief sf_app_hal_mem_read       |
 *    | @ref sf_app_hal_mem_isValid()    | @copybrief sf_app_hal_mem_isValid    |
 *
 *  @{
 */

#include <stdint.h>
#include <stdbool.h>

/*============================================================================*/
/*!
 * @brief Initialization of the memory.
 */
/*============================================================================*/
void sf_app_hal_mem_init(void);

/*============================================================================*/
/*!
 * @brief  Writes bytes into the data memory.
 *
 * @param  pData      Bytes to write into the data memory.
 * @param  len        Number of bytes to write.
 * @param  addr       Start address of the memory to write into.
 *
 * @return Returns the number of bytes written.
 */
/*============================================================================*/
uint16_t sf_app_hal_mem_write( uint8_t *pData, uint16_t len, uint32_t addr );

/*============================================================================*/
/*!
 * @brief  Reads bytes from the data memory.
 *
 * @param  pData      Memory to read the data into.
 * @param  len        Number of bytes to read.
 * @param  addr       Address of the memory to read out.
 *
 * @return Returns the number of bytes read.
 */
/*============================================================================*/
uint16_t sf_app_hal_mem_read( uint8_t *pData, uint16_t len, uint32_t addr );

/*============================================================================*/
/*!
 * @brief  Reads bytes from the data memory.
 *
 * @param  addr       Address of the memory to read out.
 *
 * @return Pointer to the memory.
 */
/*============================================================================*/
uint8_t* sf_app_hal_mem_get( uint32_t addr );

/*============================================================================*/
/*!
 * @brief  Will determine if the data in the stack data buffer after
 *         fetching the NVM is valid or not.
 *         Valid means anything else in the buffer than 0x00 or 0xFF.
 *
 * @param  offset        Offset of the stack to verify
 * @param  stackDataSize The size of the stack that is to verify.
 *
 * @return Returns false if the data coming from the NVM is invalid.
 *         Returns true if the data coming from the NVM is valid.
 */
/*============================================================================*/
bool sf_app_hal_mem_isValid( uint16_t offset, uint16_t stackDataSize );

/**@} end of SF_APP_HAL */
/******************************************************************************/

#endif /* __SF_APP_HAL_MEM_H__ */
#ifdef __cplusplus
}
#endif
