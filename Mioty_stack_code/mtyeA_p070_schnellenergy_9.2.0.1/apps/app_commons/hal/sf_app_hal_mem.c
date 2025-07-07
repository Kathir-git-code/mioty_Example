/**
* @code
*  ___ _____ _   ___ _  _____ ___  ___  ___ ___
* / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
* \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
* |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
* embedded.connectivity.solutions.==============
* @endcode
*
* @file       sf_app_hal_mem.c
* @copyright  STACKFORCE GmbH, Germany, http://www.stackforce.de
* @author     STACKFORCE
* @brief      NVM implementation.
*/
#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
/* Standart libraries */
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "driverlib/flash.h"
#include "driverlib/vims.h"

#include "sf_app_hal_mem.h"

/*==============================================================================
                            MACROS
==============================================================================*/
#ifndef SECTOR_SIZE
#error Please define the size of one sector
#endif /* SECTOR_SIZE */

#ifndef TARGET_NVM_START_ADDR
#error Please define TARGET_NVM_START_ADDR in target_config.h or check include order
#endif /* TARGET_NVM_START_ADDR */

#ifndef TARGET_NVM_END_ADDR
#error Please define TARGET_NVM_END_ADDR in target_config.h or check include order
#endif /* TARGET_NVM_END_ADDR */

/*! Calculate the size of the nvm space available for the device. Note that the
   available space and the SECTOR_SIZE is not the same. To save RAM the
   available space is normally smaler than a flash page! */
#define MCU_INFOFLASH_SIZE         (TARGET_NVM_END_ADDR - TARGET_NVM_START_ADDR)

/* Currently it is only supported to write on more than one page so this check
   is necessary */
#if (MCU_INFOFLASH_SIZE > SECTOR_SIZE)
#error Currently we do not support more than one flash page
#endif /* (MCU_INFOFLASH_SIZE > SECTOR_SIZE) */

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
void sf_app_hal_mem_init(void)
{
  /* Nothing to do here. */
}/* sf_app_hal_mem_init() */

/*----------------------------------------------------------------------------*/
/* sf_app_hal_mem_write() */
/*----------------------------------------------------------------------------*/
uint16_t sf_app_hal_mem_write(uint8_t *pc_data, uint16_t i_len, uint32_t l_addr)
{
  /* Counter variable. */
  uint16_t i;
  /* Start of the segment to write into. */
  uint8_t *pc_memory;
  /* Number of written bytes */
  uint16_t i_return = 0x00U;
  /* Array to save the flash content before erasing the flash */
  static uint8_t ac_flashPage[MCU_INFOFLASH_SIZE];
  /* Address of the first segment. */
  uint32_t l_addrSegmStart;

  /* Check the input parameters */
  if((i_len > 0x00U) && (NULL != pc_data) &&
     ((l_addr + i_len) <= MCU_INFOFLASH_SIZE))
  {
    /* Find the start of the flash page. */
    l_addrSegmStart = l_addr + TARGET_NVM_START_ADDR;
    while((l_addrSegmStart % SECTOR_SIZE) != 0)
    {
      l_addrSegmStart--;
    } /* while */

    /* Calculates the start address to write in.*/
    l_addr %= SECTOR_SIZE;

    /* Disable the cache */
    VIMSModeSet(VIMS_BASE, VIMS_MODE_DISABLED);
    while(VIMSModeGet(VIMS_BASE) != VIMS_MODE_DISABLED);

    /* Check if the flash is protected*/
    if(FlashProtectionGet(l_addr) != FLASH_WRITE_PROTECT)
    {
      /* Set the local pointer to the start of the flash page */
      pc_memory = (uint8_t*) l_addrSegmStart;

      /* Store the flash data in local array */
      for(i = 0x00U; i < MCU_INFOFLASH_SIZE; i++)
      {
        ac_flashPage[i] = pc_memory[i];
      } /* for */

      /* Updates the current flash page. */
      for(i = 0x00U; i < i_len; i++)
      {
        ac_flashPage[(l_addr + i)] = pc_data[i];
      } /* for */

      /* Erase and rewrite the flash */
      if (FlashSectorErase(l_addrSegmStart) == FAPI_STATUS_SUCCESS)
      {
        if(FlashProgram(ac_flashPage, l_addrSegmStart, MCU_INFOFLASH_SIZE) == FAPI_STATUS_SUCCESS)
        {
          i_return = i_len;
        }/* if */
      }
    }/* if  */
    /* Re-enable the cache */
    VIMSModeSet(VIMS_BASE, VIMS_MODE_ENABLED);
  }/* if */

  return i_return;
} /* sf_app_hal_mem_write() */

/*============================================================================*/
/*! sf_app_hal_mem_read() */
/*============================================================================*/
uint16_t sf_app_hal_mem_read(uint8_t *pc_data, uint16_t i_len, uint32_t l_addr)
{
  /* Counter variable. */
  uint16_t i;
  /* Pointer to the segment to read from. */
  uint8_t *pc_memory;

  pc_memory = ((uint8_t*) (TARGET_NVM_START_ADDR)) + l_addr;

   for(i = 0x00U; i < i_len ;i++)
   {
     pc_data[i] = pc_memory[i];
   } /* for */

  return i_len;
} /* sf_app_hal_mem_read() */

/*============================================================================*/
/*! sf_app_hal_mem_get() */
/*============================================================================*/
uint8_t* sf_app_hal_mem_get(uint32_t addr)
{
  return (uint8_t*) (TARGET_NVM_START_ADDR);
}/* sf_app_hal_mem_get() */

/*============================================================================*/
/*! sf_app_hal_mem_isValid() */
/*============================================================================*/
bool sf_app_hal_mem_isValid(uint16_t offset, uint16_t stackDataSize)
{
  bool ret = false;
  uint8_t readData = 0;
  uint8_t cmp1 = 0x00;
  uint8_t cmp2 = 0xFF;

  for (uint16_t counter = 0; counter < stackDataSize; counter++)
  {
    if(sizeof(readData) == sf_app_hal_mem_read(&readData, 0x01U,
                                               (offset + counter)))
    {
      if((readData != cmp1) && (readData !=cmp2))
      {
        ret = true;
        break;
      }
    }
  }

  return ret;
}/* sf_app_hal_mem_isValid */

#ifdef __cplusplus
}
#endif
