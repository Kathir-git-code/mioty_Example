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
 @brief      Stack HAL for AES.

*/

/* Standard libraries */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "sf_stack_hal_aes.h"

#include "Board.h"
#include <ti/drivers/AESECB.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKeyPlaintext.h>

/*==============================================================================
                            DEFINES
==============================================================================*/
#define AES_BLOCK_LENGTH              16U

/*==============================================================================
                            VARIABLES
==============================================================================*/
/** Module global variable for storing the encryption key. */
static uint8_t gKey[AES_BLOCK_LENGTH];

/* CryptoKey */
CryptoKey gCryptoKey;

/*==============================================================================
                            LOCAL FUNCTIONS
==============================================================================*/
/*----------------------------------------------------------------------------*/
/* loc_aes() */
/*----------------------------------------------------------------------------*/
bool loc_aes(const uint8_t* pc_in, uint8_t* pc_out, bool b_encrypt)
{
  /* Return value of this function. */
  bool b_return = false;
  /* AESECB operation struct. */
  AESECB_Operation s_aesEcbOperation;
  /* Result of the AESECB en-/decryption. */
  int_fast16_t i_result;
  /* Temporary data for the output */
  uint8_t pc_tmpData[AES_BLOCK_LENGTH];
  /* AESECB handle */
  AESECB_Handle s_aesEcbHandle;

  /* Attempt to open AESECB. */
  s_aesEcbHandle = AESECB_open(Board_AESECB0, NULL);

  if( NULL != s_aesEcbHandle )
  {
    /* Initialize CyrptoKey */
    CryptoKeyPlaintext_initKey( &gCryptoKey, gKey, AES_BLOCK_LENGTH );

    /* Initialize AES operation struct */
    AESECB_Operation_init(&s_aesEcbOperation);
    s_aesEcbOperation.key               = &gCryptoKey;
    s_aesEcbOperation.input             = (uint8_t*)pc_in;
    s_aesEcbOperation.output            = pc_tmpData;
    s_aesEcbOperation.inputLength       = AES_BLOCK_LENGTH;

    if( b_encrypt )
    {
      /* Encrypt. */
      i_result = AESECB_oneStepEncrypt( s_aesEcbHandle, &s_aesEcbOperation );
    }
    else
    {
      /* Decrypt. */
     i_result = AESECB_oneStepDecrypt( s_aesEcbHandle, &s_aesEcbOperation );
    } /* if() .. else */

    if( i_result == AESECB_STATUS_SUCCESS )
    {
      memcpy( pc_out, pc_tmpData, AES_BLOCK_LENGTH );
      b_return = true;
    } /* if() */

    AESECB_close(s_aesEcbHandle);
  } /* if() */
  return b_return;
} /* loc_aes() */

/*==============================================================================
                            HAL AES FUNCTIONS
==============================================================================*/
/*============================================================================*/
/* sf_hal_aes_init() */
/*============================================================================*/
bool sf_hal_aes_init(void)
{
  /* Initialize AESECB driver. */
  AESECB_init();

  return true;
} /* sf_hal_aes_init() */

/*----------------------------------------------------------------------------*/
/* st_stack_hal_aes_init() */
/*----------------------------------------------------------------------------*/
bool st_stack_hal_aes_init( uint8_t* pKey, uint16_t len, stackHalAes_t mode )
{
  bool ret = false;

  if( pKey && (len == AES_BLOCK_LENGTH))
  {
    memcpy( gKey, pKey, len );
    ret = true;
  } /* if() */

  return ret;
}

/*----------------------------------------------------------------------------*/
/* sf_stack_hal_aes_ecbEncrypt() */
/*----------------------------------------------------------------------------*/
bool sf_stack_hal_aes_ecbEncrypt( uint8_t* pPlaintext, uint16_t len,
                                  uint8_t* pCiphertext )
{
  bool ret = false;

  if( pPlaintext && pCiphertext && (len == AES_BLOCK_LENGTH) )
  {
    /* AES encrypt */
    if( loc_aes( pPlaintext, pCiphertext, true ) )
    {
      ret = true;
    }
  }

  return ret;
}

/*----------------------------------------------------------------------------*/
/* sf_stack_hal_aes_ecbDecrypt() */
/*----------------------------------------------------------------------------*/
bool sf_stack_hal_aes_ecbDecrypt( uint8_t* pPlaintext, uint16_t len,
                                  uint8_t* pCiphertext )
{
  bool ret = false;

  if( pPlaintext && pCiphertext && (len == AES_BLOCK_LENGTH) )
  {
    /* AES decrypt */
    if( loc_aes( pCiphertext, pPlaintext, false ) )
    {
      ret = true;
    }
  }
  return ret;
}


#ifdef __cplusplus
}
#endif
