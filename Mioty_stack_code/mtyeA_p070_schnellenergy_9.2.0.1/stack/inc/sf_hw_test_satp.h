#ifdef __cplusplus
extern "C" {
#endif
/*!
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file
 * @copyright  STACKFORCE GmbH, Germany, http://www.stackforce.de
 * @brief      Serial API command definitions for the RF tests.
 * @details    List of all serial hw test commands.
 *
 */

#ifndef __SF_HW_TEST_SATP_H__
#define __SF_HW_TEST_SATP_H__
/******************************************************************************/
 /*! @defgroup SATP_SERIAL_HW_TEST_COMMON_TEXT Serial HW test common information
 *   @ingroup SATP_HW_TEST_SERIAL_CMD
 *
 *   @details
 *
 * Before this command can be used it is required that no stack is active.
 * This can be ensured by calling the command @ref SATP_STACK_SELECT_STACK
 * with the parameter @ref E_STACK_ID_NONE.  \n
 *
 * If this is ensured the device will start the selected test mode after sending
 * the shown command below. The device will stay in the selected test mode until
 * the command @ref SATP_HW_TEST_STOP is called. \n
 * <b>NOTE:</b> \n
 * After starting a HW test modes it must be ensured that the command
 * @ref SATP_HW_TEST_STOP is called before any stack is selected by using the
 * command @ref SATP_STACK_SELECT_STACK.
 *
 *
 *@{
 *@}
 */
/******************************************************************************/

/******************************************************************************/
 /*! @defgroup SATP_SERIAL_HW_TEST_COMMON_EXAMPLE Serial HW test common Example
 *   @ingroup SATP_HW_TEST_SERIAL_CMD
 *
 *   @details
 *
 * Confirmation:
 * | STACK ID | API ID                                 | Confirmation |
 * |:--------:|:--------------------------------------:|:------------:|
 * | 0A       | @ref SATP_HW_TEST_API_ID_CMD "00"      | 00           |
 *
 *@{
 *@}
 */
/******************************************************************************/

/*! @defgroup SATP_HW_TEST_SERIAL_CMD SATP for the Radio Test API
 *
 *  @details
 *
 * <b>STACK ID 0x0A:</b>
 *
 * | STACK ID | API ID                                 | CMD ID  | SATP Command                      | Description                               |
 * |:--------:|:--------------------------------------:|:-------:|:----------------------------------|:------------------------------------------|
 * | 0A       | @ref SATP_HW_TEST_API_ID_CMD "00"      |<b>01</b>| @ref SATP_HW_TEST_START_TX_CW     | @copybrief SATP_HW_TEST_START_TX_CW       |
 * | ^        | ^                                      |<b>02</b>| @ref SATP_HW_TEST_START_TX_MOD_CW | @copybrief SATP_HW_TEST_START_TX_MOD_CW   |
 * | ^        | ^                                      |<b>03</b>| @ref SATP_HW_TEST_START_RX        | @copybrief SATP_HW_TEST_START_RX          |
 * | ^        | ^                                      |<b>04</b>| @ref SATP_HW_TEST_STOP            | @copybrief SATP_HW_TEST_STOP              |
 * | ^        | ^                                      |<b>05</b>| @ref SATP_HW_TEST_START_TX        | @copybrief SATP_HW_TEST_START_TX          |
 *  @{
 */

/*==============================================================================
                            DEFINES
==============================================================================*/

/**
 * <b>0x00:</b> @ref SATP_HW_TEST_SERIAL_CMD
 */
#define SATP_HW_TEST_API_ID_CMD            0x00U

/*!
 * @brief @copybrief sf_hw_test_startTxCw
 *
 * @copydetails SATP_SERIAL_HW_TEST_COMMON_TEXT
 *
 *  <b>Request parameter:</b>
 *     * Frequency in Hz, [4 Bytes]
 *     * TX power in dBm, [1 Byte]
 *
 *  <b>Confirmation parameter:</b>
 *  * <b>Success</b>
 *    * <b>Confirmation OK "00"</b> [1 Byte]
 *  * <b>Failed</b>
 *    * <b>Confirmation failed</b> [1 Byte]
 *    * @copydetails hwTestReturn_t \n
 *
 *
 *  <b>Example :</b> \n
 *  Start an continuous wave test on frequency 868.1 MHz, 14dBm.
 *
 * Request:
 * | STACK ID | API ID                                 | CMD ID | Frequency    | TX power  |
 * |:--------:|:--------------------------------------:|:------:|:------------:|:---------:|
 * | 0A       | @ref SATP_HW_TEST_API_ID_CMD "00"      | 01     | 33 BE 27 A0  | 0E        |
 *
 *
 * @copydetails SATP_SERIAL_HW_TEST_COMMON_EXAMPLE
 */
#define SATP_HW_TEST_START_TX_CW                                0x01

/*!
 * @brief @copybrief sf_hw_test_startTxModCw
 *
 * @copydetails SATP_SERIAL_HW_TEST_COMMON_TEXT
 *
 *  <b>Request parameter:</b>
 *     * Mode, [2 Bytes]
 *       * @copydetails hwTestMode_t
 *     * TX power in dBm, [1 Byte]
 *
 *  <b>Confirmation parameter:</b>
 *  * <b>Success</b>
 *    * <b>Confirmation OK "00"</b> [1 Byte]
 *  * <b>Failed</b>
 *    * <b>Confirmation failed</b> [1 Byte]
 *    * @copydetails hwTestReturn_t \n
 *
 *
 *  <b>Example :</b> \n
 *  Start modulated carrier wave test with wMBus mode S and a tx power of 14dbm.
 *
 * Request:
 * | STACK ID | API ID                                 | CMD ID | Mode         | TX power  |
 * |:--------:|:--------------------------------------:|:------:|:------------:|:---------:|
 * | 0A       | @ref SATP_HW_TEST_API_ID_CMD "00"      | 02     | 00 00        | 0E        |
 *
 * @copydetails SATP_SERIAL_HW_TEST_COMMON_EXAMPLE
 */
#define SATP_HW_TEST_START_TX_MOD_CW                            0x02

/*!
 * @brief @copybrief sf_hw_test_startRx
 *
 * @copydetails SATP_SERIAL_HW_TEST_COMMON_TEXT
 *
 *  <b>Request parameter:</b>
 *     * Mode, [2 Bytes]
 *       * @copydetails hwTestMode_t
 *
 *  <b>Confirmation parameter:</b>
 *  * <b>Success</b>
 *    * <b>Confirmation OK "00"</b> [1 Byte]
 *  * <b>Failed</b>
 *    * <b>Confirmation failed</b> [1 Byte]
 *    * @copydetails hwTestReturn_t \n
 *
 *
 *  <b>Example :</b> \n
 *  Start receiption test on wMBus mode S
 *
 * Request:
 * | STACK ID | API ID                                 | CMD ID | Mode           |
 * |:--------:|:--------------------------------------:|:------:|:--------------:|
 * | 0A       | @ref SATP_HW_TEST_API_ID_CMD "00"      | 03     | 00 00          |
 *
 * @copydetails SATP_SERIAL_HW_TEST_COMMON_EXAMPLE
 */
#define SATP_HW_TEST_START_RX                                   0x03

/*!
 * @brief @copybrief sf_hw_test_stop
 *
 * Same as for the other hw tests commands it must be ensured that no stack is
 * selected before using this command.
 *
 *  <b>Request parameter:</b>
 *     * none
 *
 *  <b>Confirmation parameter:</b>
 *  * <b>Success</b>
 *    * <b>Confirmation OK "00"</b> [1 Byte]
 *  * <b>Failed</b>
 *    * <b>Confirmation failed</b> [1 Byte]
 *    * @copydetails hwTestReturn_t \n
 *
 *
 *  <b>Example :</b> \n
 *  Cancel an on going hardware test.
 *
 * Request:
 * | STACK ID | API ID                                 | CMD ID |
 * |:--------:|:--------------------------------------:|:------:|
 * | 0A       | @ref SATP_HW_TEST_API_ID_CMD "00"      | 04     |
 *
 * @copydetails SATP_SERIAL_HW_TEST_COMMON_EXAMPLE
 */
#define SATP_HW_TEST_STOP                                     0x04
/*!
 * @brief @copybrief sf_hw_test_startTx
 *
 * @copydetails SATP_SERIAL_HW_TEST_COMMON_TEXT
 *
 *  <b>Request parameter:</b>
 *     * Mode, [2 Bytes]
 *       * @copydetails hwTestMode_t
 *     * Frequency in Hz, [4 Bytes]
 *     * TX power in dBm, [1 Byte]
 *     * Modulation [1 Byte]
 *       * 0 = unmodulated carrier wave
 *       * 1 = modulated carrier wave
 *
 *  <b>Confirmation parameter:</b>
 *  * <b>Success</b>
 *    * <b>Confirmation OK "00"</b> [1 Byte]
 *  * <b>Failed</b>
 *    * <b>Confirmation failed</b> [1 Byte]
 *    * @copydetails hwTestReturn_t \n
 *
 *
 *  <b>Example :</b> \n
 *  Start mioty unmodulated carrier wave test on 868'180'000 Hz using a tx power of 14dbm.
 *
 * Request:
 * | STACK ID | API ID                                 | CMD ID | Mode         | Frequency    | TX power  | Modulation  |
 * |:--------:|:--------------------------------------:|:------:|:------------:|:------------:|:---------:|:-----------:|
 * | 0A       | @ref SATP_HW_TEST_API_ID_CMD "00"      | 05     | 02 00        | 33 BF 60 20  |    0E     |     00      |
 *
 * @copydetails SATP_SERIAL_HW_TEST_COMMON_EXAMPLE
 */
#define SATP_HW_TEST_START_TX                                 0x05

/*!@} end of SATPHW_TEST_SERIAL_CMD */
/******************************************************************************/

#endif /* __SF_HW_TEST_SATP_H__ */

#ifdef __cplusplus
}
#endif
