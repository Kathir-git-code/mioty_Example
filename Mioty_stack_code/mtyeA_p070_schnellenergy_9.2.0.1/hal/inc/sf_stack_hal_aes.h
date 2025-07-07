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
 * @brief      Stack HAL for AES.
 *
 */

#ifndef __SF_STACK_HAL_AES_H__
#define __SF_STACK_HAL_AES_H__

/**
 *  @addtogroup SF_STACK_HAL
 *
 *  @details
 *
 *  - <b>AES API</b>\n
 *    | API Function                       | Description                            |
 *    |------------------------------------|----------------------------------------|
 *    | @ref st_stack_hal_aes_init()       | @copybrief st_stack_hal_aes_init       |
 *    | @ref sf_stack_hal_aes_finalize()   | @copybrief sf_stack_hal_aes_finalize   |
 *    | @ref sf_stack_hal_aes_cbcEncrypt() | @copybrief sf_stack_hal_aes_cbcEncrypt |
 *    | @ref sf_stack_hal_aes_cbcDecrypt() | @copybrief sf_stack_hal_aes_cbcDecrypt |
 *    | @ref sf_stack_hal_aes_ecbEncrypt() | @copybrief sf_stack_hal_aes_ecbEncrypt |
 *    | @ref sf_stack_hal_aes_ecbDecrypt() | @copybrief sf_stack_hal_aes_ecbDecrypt |
 *    | @ref sf_stack_hal_aes_ctrEncrypt() | @copybrief sf_stack_hal_aes_ctrEncrypt |
 *    | @ref sf_stack_hal_aes_ctrDecrypt() | @copybrief sf_stack_hal_aes_ctrDecrypt |
 *    | @ref sf_stack_hal_aes_ccmEncrypt() | @copybrief sf_stack_hal_aes_ccmEncrypt |
 *    | @ref sf_stack_hal_aes_ccmDecrypt() | @copybrief sf_stack_hal_aes_ccmDecrypt |
 *    | @ref sf_stack_hal_aes_keyWrap()    | @copybrief sf_stack_hal_aes_keyWrap    |
 *    | @ref sf_stack_hal_aes_keyUnwrap()  | @copybrief sf_stack_hal_aes_keyUnwrap  |
 *  @{
 */

#include <stdint.h>
#include <stdbool.h>

/*!
 * @brief Supported operation modes.
 */
typedef enum
{
  /*!
   * Encryption operation
   */
  E_STACK_HAL_AES_ENCRYPT,
  /*!
   * Decryption operation
   */
  E_STACK_HAL_AES_DECRYPT
} stackHalAes_t;

/*! @brief Type of function pointer used as callback to increment the key in
 *         AES-CTR mode.
 *
 * @details When the counter used in AES-CTR mode has to be incremented this
 *          function will be called. This function increments the counter.
 *
 * @param   pCtr Pointer to the counter.
 */
typedef void ( sf_stack_hal_aes_cb_t )( uint8_t *pCtr );

/*============================================================================*/
/*!
 * @brief Initialization of an AES session.
 *
 * @param pKey  Pointer to the AES key.
 * @param len   Length of the AES key.
 * @param mode  Encryption mode, refer to \ref stackHalAes_t.
 *
 * @return Returns true, if successful, false otherwise.
 */
/*============================================================================*/
bool st_stack_hal_aes_init( uint8_t* pKey, uint16_t len, stackHalAes_t mode );

/*============================================================================*/
/*!
 * @brief Finalization function of the AES session.
 *
 * @return Returns true, if successful, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_aes_finalize( void );

/*============================================================================*/
/*!
 * @brief AES-CBC encryption function.
 *
 * @param pPlaintext  Pointer to the plain text.
 * @param len         Length of the plain text in bytes.
 * @param pCiphertext Pointer to the cipher text buffer. The function must
 *                    fill this buffer with the cipher text.
 * @param iv          Pointer to the initialization vector. The length of the
 *                    iv is 16 bytes.
 *
 * @return Returns true, if successful, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_aes_cbcEncrypt( uint8_t* pPlaintext, uint16_t len,
                                  uint8_t* pCiphertext, uint8_t* iv );

/*============================================================================*/
/*!
 * @brief AES-CBC decryption function.
 *
 * @param pPlaintext  Pointer to the plain text. The function must
 *                    fill this buffer with the cipher text.
 * @param len         Length of the plain text in bytes.
 * @param pCiphertext Pointer to the cipher text buffer.
 * @param iv          Pointer to the initialization vector. The length of the
 *                    iv is 16 bytes.
 *
 * @return Returns true, if successful, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_aes_cbcDecrypt( uint8_t* pPlaintext, uint16_t len,
                                  uint8_t* pCiphertext, uint8_t* iv );

/*============================================================================*/
/*!
 * @brief AES-ECB encryption function.
 *
 * @param pPlaintext  Pointer to the plain text.
 * @param len         Length of the plain text in bytes.
 * @param pCiphertext Pointer to the cipher text buffer. The function must
 *                    fill this buffer with the cipher text.
 *
 * @return Returns true, if successful, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_aes_ecbEncrypt( uint8_t* pPlaintext, uint16_t len,
                                  uint8_t* pCiphertext );

/*============================================================================*/
/*!
 * @brief AES-ECB decryption function.
 *
 * @param pPlaintext  Pointer to the plain text. The function must
 *                    fill this buffer with the cipher text.
 * @param len         Length of the plain text in bytes.
 * @param pCiphertext Pointer to the cipher text buffer.
 *
 * @return Returns true, if successful, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_aes_ecbDecrypt( uint8_t* pPlaintext, uint16_t len,
                                  uint8_t* pCiphertext );

/*============================================================================*/
/*!
 * @brief AES-CTR encryption function.
 *
 * @param pPlaintext  Pointer to the plain text.
 * @param len         Length of the plain text in bytes.
 * @param pCiphertext Pointer to the cipher text buffer. The function must
 *                    fill this buffer with the cipher text.
 * @param iv          Pointer to the initialization vector. The length of the
 *                    iv is 16 bytes.
 * @param callback    Callback to counter increment function.
 *
 * @return Returns true, if successful, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_aes_ctrEncrypt( uint8_t* pPlaintext, uint16_t len,
                                  uint8_t* pCiphertext, uint8_t* iv,
                                  sf_stack_hal_aes_cb_t callback );

/*============================================================================*/
/*!
 * @brief AES-CTR decryption function.
 *
 * @param pPlaintext  Pointer to the plain text. The function must
 *                    fill this buffer with the cipher text.
 * @param len         Length of the plain text in bytes.
 * @param pCiphertext Pointer to the cipher text buffer.
 * @param iv          Pointer to the initialization vector. The length of the
 *                    iv is 16 bytes.
 * @param callback    Callback to counter increment function.
 *
 * @return Returns true, if successful, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_aes_ctrDecrypt( uint8_t* pPlaintext, uint16_t len,
                                  uint8_t* pCiphertext, uint8_t* iv,
                                  sf_stack_hal_aes_cb_t callback );

/*============================================================================*/
/*!
 * @brief AES-CCM encryption function.
 *
 * @param pPlaintext  Pointer to the plaintext buffer.
 * @param len         Length of the plaintext and ciphertext in bytes.
 * @param pIv         Pointer to the initialization vector.
 * @param ivLen       Length of IV.
 * @param pDataAuth   Pointer to additioal data to be authenticated (AAD).
 * @param dataAuthLen Length of AAD.
 * @param pTag        Pointer to authentication tag.
 * @param tagLen      Length of authentication tag.
 * @param pCiphertext Pointer to the ciphertext buffer.
 *
 * @return Returns true, if successful, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_aes_ccmEncrypt( uint8_t* pPlaintext, uint16_t len,
                                  uint8_t* pIv, uint16_t ivLen,
                                  uint8_t* pDataAuth, uint16_t dataAuthLen,
                                  uint8_t* pTag, uint16_t tagLen,
                                  uint8_t* pCiphertext );

/*============================================================================*/
/*!
 * @brief AES-CCM decryption function.
 *
 * @param pPlaintext  Pointer to the plaintext buffer.
 * @param len         Length of the plaintext and ciphertext in bytes.
 * @param pIv         Pointer to the initialization vector.
 * @param ivLen       Length of IV.
 * @param pDataAuth   Pointer to additioal data to be authenticated (AAD).
 * @param dataAuthLen Length of AAD.
 * @param pTag        Pointer to authentication tag.
 * @param tagLen      Length of authentication tag.
 * @param pCiphertext Pointer to the cipher text buffer.
 *
 * @return Returns true, if successful, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_aes_ccmDecrypt( uint8_t* pPlaintext, uint16_t len,
                                  uint8_t* pIv, uint16_t ivLen,
                                  uint8_t* pDataAuth, uint16_t dataAuthLen,
                                  uint8_t* pTag, uint16_t tagLen,
                                  uint8_t* pCiphertext );

/*============================================================================*/
/*!
 * @brief AES Key Wrap according to RFC 3394 (NIST SP 800-38f KW).
 *
 * @param pPreparedPlaintext  Pointer to the prepared plaintext. This includes
 *                            IV(ICV + MLI) + Plaintext + Padding.
 * @param len                 Length of the prepared plaintext in bytes.
 *                            The size of ciphertext buffer must be equal or larger.
 * @param pCiphertext         Pointer to the ciphertext buffer.
 * @param pWrapperKey         Pointer to wrapper key in size of 16 bytes.
 *
 * @return Returns true, if successful, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_aes_keyWrap( uint8_t* pPreparedPlaintext, uint16_t len,
                               uint8_t* pCiphertext, uint8_t* pWrapperKey );

/*============================================================================*/
/*!
 * @brief AES Key Unwrap according to RFC 3394 (NIST SP 800-38f KW).
 *
 * @param pPlaintext          Pointer to the plaintext buffer.
 * @param len                 Length of the ciphertext in bytes.
 *                            The size of plaintext buffer must be equal or larger.
 * @param pCiphertext         Pointer to the ciphertext.
 * @param pWrapperKey         Pointer to wrapper key in size of 16 bytes.
 *
 * @return Returns true, if successful, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_aes_keyUnwrap( uint8_t* pPlaintext, uint16_t len,
                                 uint8_t* pCiphertext, uint8_t* pWrapperKey );

/*! @} */

#endif /* __SF_STACK_HAL_AES_H__ */
#ifdef __cplusplus
}
#endif
