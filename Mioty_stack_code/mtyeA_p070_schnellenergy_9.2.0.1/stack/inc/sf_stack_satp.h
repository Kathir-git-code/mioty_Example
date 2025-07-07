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
 * @author
 * @brief      SATP stack API.
 */

#ifndef __SF_STACK_SATP_H__
#define __SF_STACK_SATP_H__

/*! @defgroup SATP_MS_API SATP for the Stack Common API
 *
 *  @details
 *
 * <b>STACK ID 0x07:</b>
 *
 * | STACK ID | API ID                                   | CMD ID  | SATP Command                      | Description                               |
 * |:--------:|:----------------------------------------:|:-------:|:----------------------------------|:------------------------------------------|
 * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      |<b>02</b>| @ref SATP_STACK_SET               | @copybrief SATP_STACK_SET                 |
 * | ^        | ^                                        |<b>03</b>| @ref SATP_STACK_GET               | @copybrief SATP_STACK_GET                 |
 * | ^        | ^                                        |<b>04</b>| @ref SATP_STACK_SELECT_STACK      | @copybrief SATP_STACK_SELECT_STACK        |
 * | ^        | ^                                        |<b>08</b>| @ref SATP_STACK_SEND_PARAMS       | @copybrief SATP_STACK_SEND_PARAMS         |
 * | ^        | ^                                        |<b>05</b>| @ref SATP_STACK_SEND              | @copybrief SATP_STACK_SEND                |
 * | ^        | ^                                        |<b>0C</b>| @ref SATP_STACK_NB_SEND           | @copybrief SATP_STACK_NB_SEND    |
 * | ^        | ^                                        |<b>09</b>| @ref SATP_STACK_RECEIVE_PARAMS    | @copybrief SATP_STACK_RECEIVE_PARAMS      |
 * | ^        | ^                                        |<b>06</b>| @ref SATP_STACK_RECEIVE           | @copybrief SATP_STACK_RECEIVE             |
 * | ^        | ^                                        |<b>07</b>| @ref SATP_STACK_GET_ACTIVE_STACK  | @copybrief SATP_STACK_GET_ACTIVE_STACK    |
 * | 07       | @ref SATP_STACK_API_ID_INDICATION "01"   |<b>02</b>| @ref SATP_STACK_IND_GEN           | @copybrief SATP_STACK_IND_GEN             |
 * | 07       | @ref SATP_STACK_API_ID_MANUFACTURER "FF" |<b>01</b>| @ref SATP_STACK_MANUFACTURER      | @copybrief SATP_STACK_MANUFACTURER        |

 * \if MBUS_PRIMARY_DEVICE_DOC
 *  <b>STACK ID 0x07: (continued)</b>\n
 * | STACK ID | API ID                                      | CMD ID  | SATP Command                      | Description                               |
 * |:--------:|:-------------------------------------------:|:-------:|:----------------------------------|:------------------------------------------|
 * | 07       | @ref SATP_STACK_API_ID_PRIMARY_COMMAND "02" |<b>0A</b>| @ref SATP_STACK_ADD_DEVICE        | @copybrief SATP_STACK_ADD_DEVICE          |
 * | ^        | ^                                           |<b>0B</b>| @ref SATP_STACK_REMOVE_DEVICE     | @copybrief SATP_STACK_REMOVE_DEVICE       |
 * \endif

 *  @{
 */

/*==============================================================================
                            INCLUDES
==============================================================================*/
#include <stdint.h>
#include <stdbool.h>

/*==============================================================================
                            DEFINES
==============================================================================*/
/**
 * <b>0x00:</b> @ref SATP_MS_API
 */
#define SATP_STACK_API_ID_COMMAND                     0x00U

/**
 * <b>0x01:</b> @ref SATP_MS_API
 */
#define SATP_STACK_API_ID_INDICATION                  0x01U

/**
 * <b>0x02:</b> @ref SATP_MS_API
 */
#define SATP_STACK_API_ID_PRIMARY_COMMAND             0x02U

/**
 * <b>0xFF:</b> @ref SATP_MS_API
 */
#define SATP_STACK_API_ID_MANUFACTURER                0xFFU

/*! @brief SATP commands for the Stack common interface. */
enum SATP_STACK_CMD
{
  /*!
   * @brief @copybrief sf_stack_set
   *
   *  <b>Request ID:</b> 0x02
   *
   *  <b>Request parameter:</b>
   *  @copydetails stackParamId_t
   *
   *
   *  <b>Confirmation parameter:</b>
   *  * <b>Success</b>
   *    * <b>Confirmation OK</b> [1 Byte]
   *  * <b>Failed</b>
   *    * <b>Confirmation failed</b> [1 Byte] \n
   *    * @copydetails stackReturn_t
   *
   *
   *  @if (WMBUS_DOC || MBUS_OVER_LORAWAN_DOC)
   *  <b>Example:</b> \n
   *  Set the <b><i>WMBUS device address</i></b> with the following configurations:
   *  * Parameter ID of WMBUS Address = "00h"
   *  * New WMBUS Address = "4E 86 80 00 00 01 23 07"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                  | Parameter value(s)      |
   * |:--------:|:----------------------------------------:|:----------:|:---------------------------------------------:|:-----------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 02         | @ref E_STACK_PARAM_ID_WMBUS_DEVADDR "00"      | 4E 86 80 00 00 01 23 07 |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   *
   * \n
   * @endif
   * @if (LORAWAN || MBUS_OVER_LORAWAN_DOC)
   * <b>Example:</b> \n
   *  Set the <b><i>LORAWAN device address </i></b> with the following configurations:
   *  * Parameter ID of LORAWAN address = "21h"
   *  * Device Address = "00 00 00 01"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                    | Parameter value(s) |
   * |:--------:|:----------------------------------------:|:----------:|:-----------------------------------------------:|:------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 02         | @ref E_STACK_PARAM_ID_LORAWAN_DEV_ADDR "21"      | 00 00 00 01        |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   *
   * \n
   * @endif
   * @if SIGFOX_DOC
   * <b>Example:</b> \n
   *  Set the <b><i>SIGFOX device address</i></b> with the following configurations:
   *  * Parameter ID of Sigfox address = "40h"
   *  * Device Address = "01 02 03 04 05 06 07 08"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                 | Parameter value(s)      |
   * |:--------:|:----------------------------------------:|:----------:|:--------------------------------------------:|:-----------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 02         | @ref E_STACK_PARAM_ID_SIGFOX_DEVID "40"      | 01 02 03 04 05 06 07 08 |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   *
   * \n
   * @endif
   * @if MIOTY_DOC
   * <b>Example:</b> \n
   *  Set the <b><i>MIOTY device EUI</i></b> with the following configurations:
   *  * Parameter ID of MIOTY EUI = "62h"
   *  * EUI = "00 00 00 00 00 00 00 01"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                | Parameter value(s)      |
   * |:--------:|:----------------------------------------:|:----------:|:-------------------------------------------:|:-----------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 02         | @ref E_STACK_PARAM_ID_MIOTY_EUI64 "62"      | 00 00 00 00 00 00 00 01 |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   *
   * \n
   * @endif
   * @if WMBUS_COLLECTOR_DOC
   * <b>Example:</b> \n
   *  Set the <b><i>WMBUS collector address</i></b> with the following configurations:
   *  * Parameter ID of WMBUS Address = "A0"
   *  * New WMBUS Address = "4E 86 80 00 00 02 23 00"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                  | Parameter value(s)      |
   * |:--------:|:----------------------------------------:|:----------:|:---------------------------------------------:|:-----------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 02         | @ref E_STACK_PARAM_ID_WMBUS_COL_ADDR "A0"     | 4E 86 80 00 00 02 23 00 |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   * \n
   * @endif
   * @if MBUS_PRIMARY_DEVICE_DOC
   * <b>Example:</b> \n
   *  Set the <b><i>Baud rate</i></b> to 9600 Bd:
   *  * Parameter ID of Baud rate = "C0"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                       | Parameter value(s)      |
   * |:--------:|:----------------------------------------:|:----------:|:--------------------------------------------------:|:-----------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 02         | @ref E_STACK_PARAM_ID_MBUS_PRIMARY_BAUD_RATE "C0"  | 02 |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   * \n
   * @endif
   * @if MBUS_SECONDARY_DEVICE_DOC
   * <b>Example:</b> \n
   *  Set the <b><i>Baud rate</i></b> to 9600 Bd:
   *  * Parameter ID of Baud rate = "D0"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                         | Parameter value(s)      |
   * |:--------:|:----------------------------------------:|:----------:|:----------------------------------------------------:|:-----------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 02         | @ref E_STACK_PARAM_ID_MBUS_SECONDARY_BAUD_RATE "D0"  | 02 |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   * \n
   * @endif
   */
  SATP_STACK_SET = 0x02,
  /*!
   * @brief @copybrief sf_stack_get
   *
   *  <b>Request ID:</b> 0x03
   *
   *  <b>Request parameter:</b>
   *  @copydetails stackParamId_t
   *
   *
   *  <b>Confirmation parameter:</b>
   *  * <b>Success</b>
   *    * <b>Confirmation OK</b> [1 Byte]
   *    * <b>Value of the requested parameter</b> [X Byte (depends on paramter)]
   *  * <b>Failed</b>
   *    * <b>Confirmation failed</b> [1 Byte] \n
   *    * @copydetails stackReturn_t
   *
   *  @if (WMBUS_DOC || MBUS_OVER_LORAWAN_DOC)
   *  <b>Example:</b> \n
   *  Get the <b><i>WMBUS device address</i></b> with the following configurations:
   *  * Parameter ID of WMBUS Address = "00h"
   *
   *  Response:
   *  * WMBUS Address = "4E 86 80 00 00 01 23 07"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                  |
   * |:--------:|:----------------------------------------:|:----------:|:---------------------------------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 03         | @ref E_STACK_PARAM_ID_WMBUS_DEVADDR "00"      |
   *
   * Response:
   * | STACK ID | API ID                                   | Confirmation OK | Parameter value         |
   * |:--------:|:----------------------------------------:|:---------------:|:-----------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00              | 4E 86 80 00 00 01 23 07 |
   *
   * \n
   * @endif
   * @if (LORAWAN || MBUS_OVER_LORAWAN_DOC)
   * <b>Example:</b> \n
   *  Get the <b><i>LORAWAN device address </i></b> with the following configurations:
   *  * Parameter ID of LORAWAN address = "21h"
   *
   *  Response:
   *  * Device Address = "00 00 00 01"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                    |
   * |:--------:|:----------------------------------------:|:----------:|:-----------------------------------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 03         | @ref E_STACK_PARAM_ID_LORAWAN_DEV_ADDR "21"      |
   *
   * Response:
   * | STACK ID | API ID                                   | Confirmation OK | Parameter value   |
   * |:--------:|:----------------------------------------:|:---------------:|:-----------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00              | 00 00 00 01       |
   *
   * \n
   * @endif
   * @if SIGFOX_DOC
   * <b>Example:</b> \n
   *  Get the <b><i>SIGFOX device address</i></b> with the following configurations:
   *  * Parameter ID of Sigfox address = "40h"
   *
   *  Response:
   *  * Device Address = "01 02 03 04 05 06 07 08"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                 |
   * |:--------:|:----------------------------------------:|:----------:|:--------------------------------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 03         | @ref E_STACK_PARAM_ID_SIGFOX_DEVID "40"      |
   *
   * Response:
   * | STACK ID | API ID                                   | Confirmation OK | Parameter value         |
   * |:--------:|:----------------------------------------:|:---------------:|:-----------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00              | 01 02 03 04 05 06 07 08 |
   *
   * \n
   * @endif
  * @if MIOTY_DOC
   * <b>Example:</b> \n
   *  Get the <b><i>MIOTY device EUI</i></b> with the following configurations:
   *  * Parameter ID of MIOTY EUI = "62h"
   *
   *  Response:
   *  * EUI = "00 00 00 00 00 00 00 01"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                |
   * |:--------:|:----------------------------------------:|:----------:|:-------------------------------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 03         | @ref E_STACK_PARAM_ID_MIOTY_EUI64 "62"      |
   *
   * Response:
   * | STACK ID | API ID                                   | Confirmation OK | Parameter value         |
   * |:--------:|:----------------------------------------:|:---------------:|:-----------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00              | 00 00 00 00 00 00 00 01 |
   *
   * @endif
   * @if MBUS_PRIMARY_DEVICE_DOC
   * <b>Example:</b> \n
   *  Get the <b><i>Baud rate</i></b> with the following configurations:
   *  * Parameter ID of <b><i>Baud rate</i></b> = "C0h"
   *
   *  Response:
   *  * Baud rate = "02" (9600 Bd)
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                      |
   * |:--------:|:----------------------------------------:|:----------:|:-------------------------------------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 03         | @ref E_STACK_PARAM_ID_MBUS_PRIMARY_BAUD_RATE "C0" |
   *
   * Response:
   * | STACK ID | API ID                                   | Confirmation OK | Parameter value         |
   * |:--------:|:----------------------------------------:|:---------------:|:-----------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00              | 02 |
   * \n
   * @endif
   * @if MBUS_SECONDARY_DEVICE_DOC
   * <b>Example:</b> \n
   *  Get the <b><i>Baud rate</i></b> with the following configurations:
   *  * Parameter ID of <b><i>Baud rate</i></b> = "D0h"
   *
   *  Response:
   *  * Baud rate = "02" (9600 Bd)
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                        |
   * |:--------:|:----------------------------------------:|:----------:|:---------------------------------------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 03         | @ref E_STACK_PARAM_ID_MBUS_SECONDARY_BAUD_RATE "D0" |
   *
   * Response:
   * | STACK ID | API ID                                   | Confirmation OK | Parameter value         |
   * |:--------:|:----------------------------------------:|:---------------:|:-----------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00              | 02                      |
   * \n
   * @endif
   */
  SATP_STACK_GET = 0x03,
  /*!
   * @brief @copybrief sf_stack_selectStack
   *
   *  <b>Request ID:</b> 0x04
   *
   *  <b>Request parameter:</b>
   *  * @copydetails stackId_t
   *
   *
   *  <b>Confirmation parameter:</b>
   *  * <b>Success</b>
   *    * <b>Confirmation OK</b> [1 Byte]
   *  * <b>Failed</b>
   *    * <b>Confirmation failed</b> [1 Byte] \n
   *    * @copydetails stackReturn_t
   *
   *
   *  <b>Example:</b> \n
   *  Set the <b><i>WMBUS stack</i></b> (Stack ID = 00) as currently active stack:
   *  * WMBUS Stack ID = "00"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Stack ID to select              |
   * |:--------:|:----------------------------------------:|:----------:|:-------------------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 04         | @ref E_STACK_ID_WMBUS "00"      |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   *
   */
  SATP_STACK_SELECT_STACK = 0x04,
  /*!
   * @brief @copybrief sf_stack_send
   *
   *  <b>Request ID:</b> 0x05
   *
   *  <b>Request parameter:</b>
   *  * <b>Data:</b> Data to be sent.
   *
   *  <b>Note:</b> The ID of the desired stack must be set by calling @ref sf_stack_selectStack() in advance.
   *
   *
   *  <b>Confirmation parameter:</b>
   *  * <b>Success</b>
   *    * <b>Confirmation OK</b> [1 Byte]
   *  * <b>Failed</b>
   *    * <b>Confirmation failed</b> [1 Byte] \n
   *    * @copydetails stackReturn_t
   *
   *
   *  <b>Example:</b> \n
   *  Send the following data and parameters:
   *  * Data = "01 23 45 67 89"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID   | Data to send   |
   * |:--------:|:----------------------------------------:|:------------:|:--------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 05           | 01 23 45 67 89 |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   *
   */
  SATP_STACK_SEND = 0x05,
  /*!
   * @brief @copybrief sf_stack_receive
   *
   *  <b>Request ID:</b> 0x06
   *
   *  <b>Note:</b> The ID of the desired stack must be set by calling @ref sf_stack_selectStack() in advance.
   *
   *
   *  <b>Confirmation parameter:</b>
   *  * <b>Success</b>
   *    * <b>Confirmation OK</b> [1 Byte]
   *    * <b>Received data</b> [x Byte]
   *  * <b>Failed</b>
   *    * <b>Confirmation failed</b> [1 Byte] \n
   *    * @copydetails stackReturn_t
   *
   *
   *  <b>Example:</b> \n
   *  Assumption of received data:
   *  * Data = "01 23 45 67 89"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID   |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 06           |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation | Received data  |
   * |:--------:|:----------------------------------------:|:------------:|:--------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           | 01 23 45 67 89 |
   *
   */
  SATP_STACK_RECEIVE = 0x06,
  /*!
   * @brief @copybrief sf_stack_getActiveStack
   *
   *  <b>Request ID:</b> 0x07
   *
   *
   *  <b>Confirmation parameter:</b>
   *  * <b>Success</b>
   *    * <b>Confirmation OK</b> [1 Byte]
   *    * <b>Value of the active stack ID</b> [1 Byte]: @copydetails stackId_t
   *  * <b>Failed</b>
   *    * <b>Confirmation failed</b> [1 Byte] \n
   *    * @copydetails stackReturn_t
   *
   *
   *  <b>Example:</b> \n
   *  Get the currently active stack ID while the mioty stack is active:
   *  * mioty Stack ID = "04"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID   |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 07           |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation | Received data  |
   * |:--------:|:----------------------------------------:|:------------:|:--------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           | 04             |
   *
   */
  SATP_STACK_GET_ACTIVE_STACK = 0x07,

  /*!
   * @brief @copybrief sf_stack_sendParams
   *
   * @if (MBUS_PRIMARY_DEVICE_DOC || MBUS_SECONDARY_DEVICE_DOC || MIOTY_DOC)
   *  <b>Request ID:</b> 0x08
   *
   *  <b>Request parameter:</b>
   *  @copydetails stackSendParamId_t
   *
   *
   *  <b>Confirmation parameter:</b>
   *  * <b>Success</b>
   *    * <b>Confirmation OK</b> [1 Byte]
   *  * <b>Failed</b>
   *    * <b>Confirmation failed</b> [1 Byte] \n
   *    * @copydetails stackReturn_t
   *
   *
   * @if MIOTY_DOC
   *  <b>Example:</b> \n
   *  Disable the transmission of the MPF-Field by setting it to zero:
   *  * Parameter ID of MAC Payload format = "60h"
   *  * New MAC Payload format = "0x00"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                              | Parameter value(s) |
   * |:--------:|:----------------------------------------:|:----------:|:-----------------------------------------:|:------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 08         | @ref E_STACK_SEND_PARAM_ID_MIOTY_MPF "60" | 00                 |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   *
   * \n
   * @endif
   * @if MBUS_PRIMARY_DEVICE_DOC
   *  <b>Example:</b> \n
   *  Set the <b><i>C-Field</i></b> with the following configurations:
   *  * Parameter ID of C-Field = "C0h"
   *  * New C-Field = "0x03" (SND-UD)
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                             | Parameter value(s) |
   * |:--------:|:----------------------------------------:|:----------:|:--------------------------------------------------------:|:------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 08         | @ref E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_DLL_C_FIELD "C0" | 03                 |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   *
   * \n
   * @endif
   * @if MBUS_SECONDARY_DEVICE_DOC
   *  <b>Example:</b> \n
   *  Set the <b><i>Data Type</i></b> to Alarm Data:
   *  * Parameter ID of Data Type = "D0h"
   *  * Alarm Data = "0x01" (Will be transmitted when a REQ-UD1 message is
   *    received by the primary device).
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID | Parameter ID                                             | Parameter value(s) |
   * |:--------:|:----------------------------------------:|:----------:|:--------------------------------------------------------:|:------------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 08         | @ref E_STACK_SEND_PARAM_ID_MBUS_SECONDARY_DATA_TYPE "D0" | 01                 |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   *
   * \n
   * @endif
   * @endif
   *
   */
  SATP_STACK_SEND_PARAMS = 0x08,
  /*!
    @brief @copybrief sf_stack_receiveParams
    @if (MBUS_PRIMARY_DEVICE_DOC || MBUS_SECONDARY_DEVICE_DOC)

     <b>Request ID:</b> 0x09

     <b>Request parameter:</b>
     @copydetails stackReceiveParamId_t
     @if MBUS_PRIMARY_DEVICE_DOC
     > @copydetails stack_mbusPrimaryRxFrame_t
     @endif
     @if MBUS_SECONDARY_DEVICE_DOC
     > @copydetails stack_mbusSecondaryRxFrame_t
     @endif

     <b>Confirmation parameter:</b>
     - <b>Success</b>
       - <b>Confirmation OK</b> [1 Byte]
       - <b>Value of the requested parameter</b> [X Byte (depends on parameter)]
     - <b>Failed</b>
       - <b>Confirmation failed</b> [1 Byte] \n
       - @copydetails stackReturn_t \n


    @if MBUS_PRIMARY_DEVICE_DOC
     <b>Example:</b> \n
     Receive the details of a wired M-Bus frame. \n
     Assumption of received data:\n
     \verbatim
     C-Field          : 0x08 (RSP-UD)
     Primary Address  : 253 (Secondary Addressing Mode)
     CI-Field         : 0x72 (long header)
     secondary Address: ID: 0x80 0x00 0x00 0x01 MAN: 0xCE 0x86 VERSION: 0x23 TYPE: 0x07
     ACC              : 0xD1
     STS              : 0x00
     CONF_WORD        : 0x0000 (no encryption)
     Decrypted        : 1 (decrypted, ore unencrypted frame)
     Header lengths   : TPL = 13byte AFL = 0byte ELL = 0byte
     Data             : "01 23 45 67 89"
     \endverbatim

    Request:
    | STACK ID | API ID                                   | Request ID   |Parameter Id                                                |
    |:--------:|:----------------------------------------:|:------------:|:----------------------------------------------------------:|
    | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 09           |   @ref E_STACK_RECEIVE_PARAM_ID_MBUS_PRIMARY_DETAILS "C0"  |

    Confirmation:
    | STACK ID | API ID                                   | Confirmation | Control-Field | Primary Address | Decrypted | TPL | AFL | ELL | Received frame                                        |
    |:--------:|:----------------------------------------:|:------------:|:-------------:|:---------------:|:---------:|:---:|:---:|:---:|:-----------------------------------------------------:|
    | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |  08           |  FD             | 01        | 0D  | 00  | 00  | 72 01 00 00 80 86 CE 23 07 D1 00 00 00 01 23 45 67 89 |

    \n
    @endif
    @if MBUS_SECONDARY_DEVICE_DOC
     <b>Example:</b> \n
     Receive the details of a wired M-Bus frame. \n
     Assumption of received data:\n
     \verbatim
     C-Field          : 0x53 (SND-UD)
     Primary Address  : 1 (Primary Addressing Mode)
     CI-Field         : 0x5A (short header)
     ACC              : 0x00
     STS              : 0x00
     CONF_WORD        : 0x0000 (no encryption)
     Decrypted        : 1 (decrypted, ore unencrypted frame)
     Header lengths   : TPL = 4byte AFL = 0byte ELL = 0byte
     Data             : "01 02 03 04"
     \endverbatim

    Request:
    | STACK ID | API ID                                   | Request ID   |Parameter Id                                                  |
    |:--------:|:----------------------------------------:|:------------:|:------------------------------------------------------------:|
    | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 09           |   @ref E_STACK_RECEIVE_PARAM_ID_MBUS_SECONDARY_DETAILS "D0"  |

    Confirmation:
    | STACK ID | API ID                                   | Confirmation | Control-Field | Primary Address | Decrypted | TPL | AFL | ELL | Received frame             |
    |:--------:|:----------------------------------------:|:------------:|:-------------:|:---------------:|:---------:|:---:|:---:|:---:|:--------------------------:|
    | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |  53           |  01             | 01        | 05  | 00  | 00  | 5A 00 00 00 00 01 02 03 04 |

    \n
    @endif
    @endif
   */
  SATP_STACK_RECEIVE_PARAMS = 0x09,
  /*! @if (MBUS_PRIMARY_DEVICE_DOC)
   * @brief Add a device to the list.
   *  <b>Request ID:</b> 0x0A
   *
   *  <b>Device Type:</b>
   *  @copydetails stackDevice_t
   *
   *  <b> Device Details:</b> \n
   *  Depending on the selected Device Type different parameters needs to be
   *  provided. \n
   *  @if MBUS_PRIMARY_DEVICE_DOC
   *  * @copydetails stack_mbusPrimaryAddDevice_t
   *  @endif
   *
   *  <b>Confirmation parameter:</b>
   *  * <b>Success</b>
   *    * <b>Confirmation OK</b> [1 Byte]
   *  * <b>Failed</b>
   *    * <b>Confirmation failed</b> [1 Byte] \n
   *    * @copydetails stackReturn_t
   *
    @if MBUS_PRIMARY_DEVICE_DOC
     <b>Example:</b> \n
     Adding a @ref E_STACK_DEVICE_SECONDARY
     \verbatim
      Secondary address: 4E 86 80 00 00 01 23 07
      Encryption mode  : security Profile A (AES-CBC)
      Key              : 00 11 22 33 44 55 66 77 88 99 AA BB CC DD EE FF
     \endverbatim
   *
   * Request:
   * | STACK ID | API ID                                      | Request ID                               | Device Type                       | Secondary Address       | Encryption Mode | Key                                            |
   * |:--------:|:-------------------------------------------:|:----------------------------------------:|:---------------------------------:|:-----------------------:|:---------------:|:----------------------------------------------:|
   * | 07       | @ref SATP_STACK_API_ID_PRIMARY_COMMAND "02" | @ref SATP_STACK_ADD_DEVICE "0A"          | @ref E_STACK_DEVICE_SECONDARY "00"| 4E 86 80 00 00 01 23 07 | 05              | 00 11 22 33 44 55 66 77 88 99 AA BB CC DD EE FF|
   *
   * Confirmation:
   * | STACK ID | API ID                                      | Confirmation |
   * |:--------:|:-------------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_PRIMARY_COMMAND "02" | 00           |
   * @endif
   * @else
   * @brief This function is not available for the selected product.
   * @endif
   */
  SATP_STACK_ADD_DEVICE = 0x0A,
  /*! @if (MBUS_PRIMARY_DEVICE_DOC)
   * @brief Remove a device from the list.
   *
   *  <b>Request ID:</b> 0x0B
   *
   *  <b>Device Type:</b>
   *  @copydetails stackDevice_t
   *
   *  <b> Device Details:</b> \n
   *  Depending on the selected Device Type different parameters needs to be
   *  provided. \n
   *  @if MBUS_PRIMARY_DEVICE_DOC
   *  * @copydetails stack_mbusPrimaryRemoveDevice_t
   *  @endif
   *
   *  <b>Confirmation parameter:</b>
   *  * <b>Success</b>
   *    * <b>Confirmation OK</b> [1 Byte]
   *  * <b>Failed</b>
   *    * <b>Confirmation failed</b> [1 Byte] \n
   *    * @copydetails stackReturn_t
   *
    @if MBUS_PRIMARY_DEVICE_DOC
     <b>Example:</b> \n
     Removing a @ref E_STACK_DEVICE_SECONDARY
     \verbatim
      Secondary address: 4E 86 80 00 00 01 23 07
     \endverbatim
   *
   * Request:
   * | STACK ID | API ID                                      | Request ID                               | Device Type                       | Secondary Address       |
   * |:--------:|:-------------------------------------------:|:----------------------------------------:|:---------------------------------:|:-----------------------:|
   * | 07       | @ref SATP_STACK_API_ID_PRIMARY_COMMAND "02" | @ref SATP_STACK_REMOVE_DEVICE "0B"       | @ref E_STACK_DEVICE_SECONDARY "00"| 4E 86 80 00 00 01 23 07 |
   *
   * Confirmation:
   * | STACK ID | API ID                                      | Confirmation |
   * |:--------:|:-------------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_PRIMARY_COMMAND "02" | 00           |
   * @endif
   * @else
   * @brief This function is not available for the selected product.
   * @endif
   */
  SATP_STACK_REMOVE_DEVICE = 0x0B,
  /*!
   * @brief @copybrief sf_stack_nb_send
   *
   *  <b>Request ID:</b> 0x0C
   *
   *  <b>Request parameter:</b>
   *  * <b>Data:</b> Data to be sent.
   *
   *  <b>Note:</b> The ID of the desired stack must be set by calling @ref sf_stack_selectStack() in advance.
   *
   *
   *  <b>Confirmation parameter:</b>
   *  * <b>Success</b>
   *    * <b>Confirmation OK</b> [1 Byte]
   *  * <b>Failed</b>
   *    * <b>Confirmation failed</b> [1 Byte] \n
   *    * @copydetails stackReturn_t
   *
   *
   *  <b>Example:</b> \n
   *  Send the following data and parameters:
   *  * Data = "01 23 45 67 89"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID   | Data to send   |
   * |:--------:|:----------------------------------------:|:------------:|:--------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 0C           | 01 23 45 67 89 |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_COMMAND "00"      | 00           |
   *
   */
  SATP_STACK_NB_SEND = 0x0C,
};

/*! @brief SATP indications for the Stack common interface. */
enum SATP_STACK_IND
{
  /*! @brief Generic Stack indication.
   *
   *  <b>Indication ID:</b> 0x02
   *
   *  <b>Indication parameter:</b> \n
   *  * @copydetails stackEvent_t
   *  * <b>Data:</b> \n Event specific data. Optional parameter. See @ref stackEvent_t for the details.
   *
   *  <b>Example:</b> \n
   *
   *  The following indication informs the user that 5 bytes where received from the device:
   *  * Event type: @ref E_STACK_EVENT_RX_SUCCESS
   *  * Data length = "00 05"
   *
   * Indication:
   * | STACK ID | API ID                                      | Indication ID   | Event type | Received data length  |
   * |:--------:|:-------------------------------------------:|:---------------:|:----------:|:--------------:|
   * | 07       | @ref SATP_STACK_API_ID_INDICATION "01"      | 02              | 03         | 00 05 |
   */
  SATP_STACK_IND_GEN = 0x02,
};

/*! @brief SATP indications for the Stack common interface. */
enum SATP_STACK_MANUFACTURER
{
  /*! @brief Generic manufacturer command
   *
   *  <b>Request ID:</b> 0x01
   *
   *  <b>Request parameter:</b>
   *  * <b>Data:</b> The content and length of the Data field is variable and
   *                 can be defined by the manufacturer.
   *
   *  <b>Confirmation parameter:</b>
   *  * <b>Success</b>
   *    * <b>Confirmation OK</b> [1 Byte]
   *  * <b>Failed</b>
   *    * <b>Confirmation failed</b> [1 Byte] \n
   *    * @copydetails stackReturn_t
   *
   *  <b>Example:</b> \n
   *  Send the following data and parameters:
   *  * Data = "01 A5 B5"
   *
   * Request:
   * | STACK ID | API ID                                   | Request ID   | Data     |
   * |:--------:|:----------------------------------------:|:------------:|:--------:|
   * | 07       | @ref SATP_STACK_API_ID_MANUFACTURER "FF" | 01           | 01 A5 B5 |
   *
   * Confirmation:
   * | STACK ID | API ID                                   | Confirmation |
   * |:--------:|:----------------------------------------:|:------------:|
   * | 07       | @ref SATP_STACK_API_ID_MANUFACTURER "FF" | 00           |
   */
  SATP_STACK_MANUFACTURER = 0x01,
};
/*!@} end of SATP_MS_API */
/******************************************************************************/

#endif // __SF_STACK_SATP_H__
#ifdef __cplusplus
}
#endif
