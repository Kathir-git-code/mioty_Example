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
 * @brief      Type definitions for the STACKFORCE Stack.
 *
 */

#ifndef __SF_STACK_TYPES_H__
#define __SF_STACK_TYPES_H__

/*! @addtogroup MS_COM_IF
 *
 * @{
 */

/*==============================================================================
                            INCLUDES
==============================================================================*/
#include <stdint.h>
#include <stdbool.h>

/*==============================================================================
                            DEFINES
==============================================================================*/
/** Length of the parameter WMBUS_DEVADDR in byte. */
#define STACK_PARAM_LENGTH_WMBUS_DEVADDR         8U
/** Length of the parameter WMBUS_KEY in byte. */
#define STACK_PARAM_LENGTH_WMBUS_KEY            16U
/** Length of the parameter WMBUS_INTERVAL in byte. */
#define STACK_PARAM_LENGTH_WMBUS_INTERVAL        4U
/** Length of the parameter WMBUS_EVENT_TYPE in byte. */
#define STACK_PARAM_LENGTH_WMBUS_EVENT_TYPE      1U
/** Length of the parameter WMBUS_ENCRYPT_MODE in byte. */
#define STACK_PARAM_LENGTH_WMBUS_ENCRYPT_MODE    1U

/** Length of the parameter LORAWAN_DEV_EUI in byte. */
#define STACK_PARAM_LENGTH_LORAWAN_DEV_EUI       8U
/** Length of the parameter LORAWAN_DEV_ADDR in byte. */
#define STACK_PARAM_LENGTH_LORAWAN_DEV_ADDR      4U
/** Length of the parameter LORAWAN_NET_ID in byte. */
#define STACK_PARAM_LENGTH_LORAWAN_NET_ID        4U
/** Length of the parameter LORAWAN_JOIN_EUI in byte. */
#define STACK_PARAM_LENGTH_LORAWAN_JOIN_EUI      8U
/** Length of the parameter LORAWAN_ACTIVATION in byte. */
#define STACK_PARAM_LENGTH_LORAWAN_ACTIVATION    1U
/** Length of the parameter LORAWAN_FPORT in byte. */
#define STACK_PARAM_LENGTH_LORAWAN_FPORT         1U
/** Length of the parameter LORAWAN_UPLINK_TYPE in byte. */
#define STACK_PARAM_LENGTH_LORAWAN_UPLINK_TYPE   1U

/** Length of the parameter SIGFOX_DEVID in byte. */
#define STACK_PARAM_LENGTH_SIGFOX_DEVID          8U
/** Length of the parameter SIGFOX_PAC in byte. */
#define STACK_PARAM_LENGTH_SIGFOX_PAC            4U
/** Length of the parameter SIGFOX_MANUVERSION in byte. */
#define STACK_PARAM_LENGTH_SIGFOX_MANUVERSION    1U
/** Length of the parameter SIGFOX_DEVKEY in byte. */
#define STACK_PARAM_LENGTH_DEVKEY               16U

/** Length of the parameter MIOTY_PROFILE in byte. */
#define STACK_PARAM_LENGTH_MIOTY_PROFILE         1U
/** Length of the parameter MIOTY_MODE in byte. */
#define STACK_PARAM_LENGTH_MIOTY_MODE            1U
/** Length of the parameter MIOTY_EUI64 in byte. */
#define STACK_PARAM_LENGTH_MIOTY_EUI64           8U
/** Length of the parameter MIOTY_NWKKEY in byte. */
#define STACK_PARAM_LENGTH_MIOTY_NWKKEY         16U
/** Length of the parameter MIOTY_MPF in byte. */
#define STACK_PARAM_LENGTH_MIOTY_MPF             1U
/** Length of the parameter MIOTY_SHORT_ADDR in byte. */
#define STACK_PARAM_LENGTH_MIOTY_SHORT_ADDR      2U
/** Length of the parameter MIOTY_TX_POWER in byte. */
#define STACK_PARAM_LENGTH_MIOTY_TX_POWER        1U
/** Length of the parameter MIOTY_ACK_REQUEST in byte. */
#define STACK_PARAM_LENGTH_MIOTY_ACK_REQUEST     1U
/** Length of the parameter MIOTY_RX_WINDOW in byte. */
#define STACK_PARAM_LENGTH_MIOTY_RX_WINDOW       1U

/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/
/*! @brief Definition of Application Layer return codes.
 *  @details
 *    <b>Stack return codes.</b> [1 Byte] \n
 *    > @copydetails E_STACK_RETURN_SUCCESS \n
 *    > @copydetails E_STACK_RETURN_ERROR \n
 *    > @copydetails E_STACK_RETURN_ERROR_NPE \n
 *    > @copydetails E_STACK_RETURN_ERROR_INVALID_PARAM \n
 *    > @copydetails E_STACK_RETURN_ERROR_NO_ACTIVE_STACK \n
 *    > @copydetails E_STACK_RETURN_ERROR_BUSY \n
 *    > @copydetails E_STACK_RETURN_NOT_AVAILABLE \n
 *    > @copydetails E_STACK_RETURN_NOT_ACTIVATED \n
 *    > @copydetails E_STACK_RETURN_SUCCESS_WFE \n
*/
typedef enum
{
  /*!
   * <b>0x00 : @ref E_STACK_RETURN_SUCCESS - Return code success</b>
   */
  E_STACK_RETURN_SUCCESS = 0x00,
  /*!
   * <b>0x01 : @ref E_STACK_RETURN_ERROR - Return code general error</b>
   */
  E_STACK_RETURN_ERROR = 0x01,
  /*!
   * <b>0x02 : @ref E_STACK_RETURN_ERROR_NPE - Return code for null pointer exception (NPE) error</b>
   */
  E_STACK_RETURN_ERROR_NPE = 0x02,
  /*!
   * <b>0x03 : @ref E_STACK_RETURN_ERROR_INVALID_PARAM - Return code invalid parameter</b>
   */
  E_STACK_RETURN_ERROR_INVALID_PARAM = 0x03,
  /*!
   * <b>0x04 : @ref E_STACK_RETURN_ERROR_NO_ACTIVE_STACK - Return code no active stack</b>
   */
  E_STACK_RETURN_ERROR_NO_ACTIVE_STACK = 0x04,
  /*!
   * <b>0x05 : @ref E_STACK_RETURN_ERROR_BUSY - Return code busy error</b>
   */
  E_STACK_RETURN_ERROR_BUSY = 0x05,
  /*!
   * <b>0x06 : @ref E_STACK_RETURN_NOT_AVAILABLE - The selected stack is not available</b>
   */
  E_STACK_RETURN_NOT_AVAILABLE = 0x06,
  /*!
   * <b>0x07 : @ref E_STACK_RETURN_NOT_ACTIVATED - A transmission is not possible as the
   * device is not activated. </b>
   */
  E_STACK_RETURN_NOT_ACTIVATED = 0x07,
  /*!
   * <b>0x08 : @ref E_STACK_RETURN_SUCCESS_WFE - Return code success and the state
   * is waiting for an event. </b>
   */
  E_STACK_RETURN_SUCCESS_WFE = 0x08,
} stackReturn_t;

/*! @brief Identifiers of different stacks.
 *  @details
 *    <b>Stack identifier codes.</b> [1 Byte] \n
 *    > @copydetails E_STACK_ID_NONE \n
 *    > @copydetails E_STACK_ID_WMBUS \n
 *    > @copydetails E_STACK_ID_LORAWAN \n
 *    > @copydetails E_STACK_ID_SIGFOX \n
 *    > @copydetails E_STACK_ID_MIOTY \n
 *    > @copydetails E_STACK_ID_MBUS_OVER_LORAWAN \n
 *    > @copydetails E_STACK_ID_WMBUS_COLLECTOR \n
 *    > @copydetails E_STACK_ID_MBUS_PRIMARY \n
 *    > @copydetails E_STACK_ID_MBUS_SECONDARY \n
 *    > @copydetails E_STACK_ID_NUMBER_OF_STACK_IDS \n
 *    > @copydetails E_STACK_ID_INVALID \n
*/
typedef enum
{
  /*!
   * <b>0x00 : @ref E_STACK_ID_NONE - Stack identifier for no stack</b>
   */
  E_STACK_ID_NONE = 0x00,
  /*!
   * <b>0x01 : @ref E_STACK_ID_WMBUS - Stack identifier of WMBus Meter</b>
   */
  E_STACK_ID_WMBUS = 0x01,
  /*!
   * <b>0x02 : @ref E_STACK_ID_LORAWAN - Stack identifier of LoRaWAN</b>
   */
  E_STACK_ID_LORAWAN = 0x02,
  /*!
   * <b>0x03 : @ref E_STACK_ID_SIGFOX - Stack identifier of Sigfox</b>
   */
  E_STACK_ID_SIGFOX = 0x03,
  /*!
   * <b>0x04 : @ref E_STACK_ID_MIOTY - Stack identifier of MIOTY</b>
   */
  E_STACK_ID_MIOTY = 0x04,
  /*!
   * <b>0x05 : @ref E_STACK_ID_MBUS_OVER_LORAWAN - Stack identifier of WMBus over LoRaWAN</b>
   */
  E_STACK_ID_MBUS_OVER_LORAWAN = 0x05,
  /*!
   * <b>0x06 : @ref E_STACK_ID_WMBUS_COLLECTOR - Stack identifier of WMBus Collector</b>
   */
  E_STACK_ID_WMBUS_COLLECTOR = 0x06,
    /*!
   * <b>0x07 : @ref E_STACK_ID_MBUS_PRIMARY - Stack identifier of wired MBus
     primary device</b>
   */
  E_STACK_ID_MBUS_PRIMARY = 0x07,
    /*!
   * <b>0x08 : @ref E_STACK_ID_MBUS_SECONDARY - Stack identifier of wired MBus
     secondary device</b>
   */
  E_STACK_ID_MBUS_SECONDARY = 0x08,
  /*!
   * <b>0x09 : @ref E_STACK_ID_NUMBER_OF_STACK_IDS - Current number of Stack IDs is 9</b>
   */
  E_STACK_ID_NUMBER_OF_STACK_IDS = 0x09,
  /*!
   * <b>0xFF : @ref E_STACK_ID_INVALID - Invalid stack identifier</b>
   */
  E_STACK_ID_INVALID = 0xFF,
} stackId_t;

/*!
 * @brief Parameter IDs for implemented stacks
 * @details
 *    @if (WMBUS_DOC || MBUS_OVER_LORAWAN_DOC)
 *  * <b>Parameters of WMBus and MBus over LoRaWAN:</b> \n
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_DEVADDR \n
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_KEY \n
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_ENCRYPT_MODE \n
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_C_FIELD \n
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_ALA \n
 *    @endif
 *    @if (LORAWAN || MBUS_OVER_LORAWAN_DOC)
 *  * <b>Parameters of LoRaWAN and MBus over LoRaWAN:</b> \n
 *    > @copydetails E_STACK_PARAM_ID_LORAWAN_DEV_EUI \n
 *    > @copydetails E_STACK_PARAM_ID_LORAWAN_DEV_ADDR \n
 *    > @copydetails E_STACK_PARAM_ID_LORAWAN_NET_ID \n
 *    > @copydetails E_STACK_PARAM_ID_LORAWAN_JOIN_EUI \n
 *    > @copydetails E_STACK_PARAM_ID_LORAWAN_APP_KEY \n
 *    > @copydetails E_STACK_PARAM_ID_LORAWAN_GEN_APP_KEY \n
 *    > @copydetails E_STACK_PARAM_ID_LORAWAN_NWK_S_KEY \n
 *    > @copydetails E_STACK_PARAM_ID_LORAWAN_APP_S_KEY \n
 *    > @copydetails E_STACK_PARAM_ID_LORAWAN_ACTIVATION \n
 *    > @copydetails E_STACK_PARAM_ID_LORAWAN_FPORT \n
 *    > @copydetails E_STACK_PARAM_ID_LORAWAN_UPLINK_TYPE \n
 *    > @copydetails E_STACK_PARAM_ID_LORAWAN_NB_TRIALS \n
 *    @endif
 *    @if SIGFOX_DOC
 *  * <b>Parameters of Sigfox:</b> \n
 *    > @copydetails E_STACK_PARAM_ID_SIGFOX_DEVID \n
 *    > @copydetails E_STACK_PARAM_ID_SIGFOX_PAC \n
 *    > @copydetails E_STACK_PARAM_ID_SIGFOX_MANUVERSION \n
 *    > @copydetails E_STACK_PARAM_ID_SIGFOX_DEVKEY \n
 *    @endif
 *    @if MIOTY_DOC
 *  * <b>Parameters of MIOTY:</b> \n
 *    > @copydetails E_STACK_PARAM_ID_MIOTY_PROFILE \n
 *    > @copydetails E_STACK_PARAM_ID_MIOTY_MODE \n
 *    > @copydetails E_STACK_PARAM_ID_MIOTY_EUI64 \n
 *    > @copydetails E_STACK_PARAM_ID_MIOTY_NWKKEY \n
 *    > @copydetails E_STACK_PARAM_ID_MIOTY_SHORT_ADDR \n
 *    > @copydetails E_STACK_PARAM_ID_MIOTY_TX_POWER \n
 *    @endif
 *    @if WMBUS_COLLECTOR_DOC
 *  * <b>Parameters of WMBus Collector:</b> \n
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_COL_ADDR
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_COL_MODE
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_COL_TX_POWER
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_COL_RX_NO_DECRYPT
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_COL_TPL_ACC_NO
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_COL_ELL_ACC_NO
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_COL_TX_ELL_HEADER
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_COL_TX_PARAMS
 *    > @copydetails E_STACK_PARAM_ID_WMBUS_COL_MSG_CTR_INCREMENT_VALUE
 *    @endif
 *    @if MBUS_PRIMARY_DEVICE_DOC
 *  * <b>Parameters of the wired M-Bus Primary Device:</b> \n
 *    > @copydetails E_STACK_PARAM_ID_MBUS_PRIMARY_BAUD_RATE
 *    @endif
 *    @if MBUS_SECONDARY_DEVICE_DOC
 *  * <b>Parameters of the wired M-Bus Secondary Device:</b> \n
 *    > @copydetails E_STACK_PARAM_ID_MBUS_SECONDARY_BAUD_RATE
 *    > @copydetails E_STACK_PARAM_ID_MBUS_SECONDARY_DLL_A_FIELD
 *    > @copydetails E_STACK_PARAM_ID_MBUS_SECONDARY_SEC_ADDR
 *    > @copydetails E_STACK_PARAM_ID_MBUS_SECONDARY_ENCRYPT_MODE
 *    > @copydetails E_STACK_PARAM_ID_MBUS_SECONDARY_KEY
 *    > @copydetails E_STACK_PARAM_ID_MBUS_SECONDARY_STATUS
 *    @endif
 *  * <b>Generic parameters:</b> \n
 *    > @copydetails E_STACK_PARAM_ID_MEMORY_OCCUPIED
 *    > @copydetails E_STACK_PARAM_ID_MEMORY_PEAK
 *    > @copydetails E_STACK_PARAM_ID_GENERIC_RX_DATA_LENGTH
 *
 */
typedef enum
{
  /* WMBus parameters */
  /*! <b> 0x00 : @ref E_STACK_PARAM_ID_WMBUS_DEVADDR - WMBus Address</b> \n
     Address of the device. The address is formed in the following way <b>[8 Bytes]</b>: \n
    \verbatim
    Byte:  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
    Name:  | M | M | I | I | I | I | V | T |
      - M = Manufacture ID (2 Byte)
      - I = Ident number   (4 Byte)
      - V = Version        (1 Byte)
      - T = Type           (1 Byte)
    \endverbatim */
  E_STACK_PARAM_ID_WMBUS_DEVADDR = 0x00U,
  /*! <b> 0x01 : @ref E_STACK_PARAM_ID_WMBUS_KEY - Encryption key</b> \n
      128 bit encryption key of the device <b>[16 Bytes]</b>. \n
      <b>This parameter is a write ony parameter and can't be requested using @ref SATP_STACK_GET.</b> \n*/
  E_STACK_PARAM_ID_WMBUS_KEY = 0x01U,
  /*! <b>0x02 : @ref E_STACK_PARAM_ID_WMBUS_ENCRYPT_MODE - Encryption mode</b> \n Supported encryption modes <b>[1 Byte]</b>: \n
   * \verbatim
     - 0x00: no encryption
     - 0x05: security Profile A (AES-CBC)
     - 0x07: security Profile B (AES-CBC + CMAC)
   \endverbatim */
  E_STACK_PARAM_ID_WMBUS_ENCRYPT_MODE = 0x02U,
  /*! <b> 0x03: @ref E_STACK_PARAM_ID_WMBUS_C_FIELD - Control field of the last received frame</b> \n
    This parameter is read only and limited to bidirectional wM-Bus Meter devices. <b>[1 Byte]</b> */
  E_STACK_PARAM_ID_WMBUS_C_FIELD = 0x03U,
  /*! <b> 0x04: @ref E_STACK_PARAM_ID_WMBUS_ALA - Address of the Meters/Actuators application layer.</b> <b>[8 Byte]</b> \n
      By default the ALA is set to invalid (FF-FF-FF-FF-FF-FF-FF-FF) and the stack transmits with
      short TPL header. As a result, the async-/synchronous SND-NR telegrams will use CI field 7Ah for TPL header. \n
      When this parameter (ALA) is set to a valid value, the stack will transmit with long TPL header instead.
      This setting affects all transmissions of the stack that a TPL header is applied.
      Additionally, the CI field to be applied depends on the current status of the meter.
      In general the following CI fields are used by the stack:

      | CI-Field description                      | Short | Long |
      | ----------------------------------------- | ----- | ---- |
      | Response from device                      | 7Ah   | 72h  |
      | Alarm from device                         | 74h   | 75h  |
      | Transport Layer from device (without APL) | 8Ah   | 8Bh  |*/
  E_STACK_PARAM_ID_WMBUS_ALA = 0x04U,

  /* LoRaWAN parameters */
  /*! <b>0x20 : @ref E_STACK_PARAM_ID_LORAWAN_DEV_EUI - Device EUI</b> \n Unique
      device EUI. Required for ABP and OTAA.<b>.[8 Bytes]</b>. \n */
  E_STACK_PARAM_ID_LORAWAN_DEV_EUI = 0x20U,
  /*! <b>0x22 : @ref E_STACK_PARAM_ID_LORAWAN_DEV_ADDR - Device address</b> \n
      Device short address required for ABP activation.<b>.[4 Bytes]</b>. \n */
  E_STACK_PARAM_ID_LORAWAN_DEV_ADDR = 0x22U,
  /*! <b>0x23 : @ref E_STACK_PARAM_ID_LORAWAN_NET_ID - Network identifier</b> \n
      Network identifier required for ABP activation.<b>.[4 Bytes]</b>. \n */
  E_STACK_PARAM_ID_LORAWAN_NET_ID = 0x23U,
  /*! <b>0x24 : @ref E_STACK_PARAM_ID_LORAWAN_JOIN_EUI - Join EUI</b> \n
      Join EUI required for ABP and OTAA activation.<b>.[8 Bytes]</b>. \n */
  E_STACK_PARAM_ID_LORAWAN_JOIN_EUI = 0x24U,
  /*! <b>0x25 : @ref E_STACK_PARAM_ID_LORAWAN_APP_KEY - Application Key</b> \n
      App Key required for OTAA activation.<b>.[16 Bytes]</b>. \n */
  E_STACK_PARAM_ID_LORAWAN_APP_KEY = 0x25U,
  /*! <b>0x26 : @ref E_STACK_PARAM_ID_LORAWAN_NWK_S_KEY - NwkSKey</b> \n
      NwkSKey required for ABP activation.<b>.[16 Bytes]</b>. \n */
  E_STACK_PARAM_ID_LORAWAN_NWK_S_KEY = 0x26U,
  /*! <b>0x27 : @ref E_STACK_PARAM_ID_LORAWAN_APP_S_KEY - AppSKey</b> \n
      AppSKey required for ABP activation.<b>.[16 Bytes]</b>. \n */
  E_STACK_PARAM_ID_LORAWAN_APP_S_KEY = 0x27U,
  /*! <b>0x28 : @ref E_STACK_PARAM_ID_LORAWAN_ACTIVATION - Network activation</b> \n
      Network activation configuration. Set to 1 for OTAA and to
      0 for ABP<b>.[1 Byte]</b>. \n */
  E_STACK_PARAM_ID_LORAWAN_ACTIVATION = 0x28U,
  /*! <b>0x29 : @ref E_STACK_PARAM_ID_LORAWAN_FPORT - Port</b> \n Port number on
      which the data has to be transmitted. Default port is 2<b>.[1 Byte]</b>. \n */
  E_STACK_PARAM_ID_LORAWAN_FPORT = 0x29U,
  /*! <b>0x2A : @ref E_STACK_PARAM_ID_LORAWAN_UPLINK_TYPE - Uplink type
      selection</b> Enables or disables confirmed uplinks. Set to
      0 for unconfirmed uplinks and to 1 for confirmed uplinks<b>[1 Byte]</b>. \n */
  E_STACK_PARAM_ID_LORAWAN_UPLINK_TYPE = 0x2AU,
  /*! <b>0x2B : @ref E_STACK_PARAM_ID_LORAWAN_NB_TRIALS - Number of trials for
      confirmed uplinks</b>Set to 8 by default. Only applicable for LoRaWAN v103.
      <b>[1 Byte]</b>. \n */
  E_STACK_PARAM_ID_LORAWAN_NB_TRIALS = 0x2BU,
  /*! <b>0x2C : @ref E_STACK_PARAM_ID_LORAWAN_GEN_APP_KEY - Application Gen Key</b> \n
      AppGenKey required key derivation.<b>.[16 Bytes]</b>. \n */
  E_STACK_PARAM_ID_LORAWAN_GEN_APP_KEY = 0x2CU,

  /* Sigfox parameters */
  /*! <b>0x40 : @ref E_STACK_PARAM_ID_SIGFOX_DEVID - Device ID</b> \n 64-bit long unique device ID of the Sigfox end point <b>[8 Bytes]</b>. \n */
  E_STACK_PARAM_ID_SIGFOX_DEVID = 0x40U,
  /*! <b>0x41 : @ref E_STACK_PARAM_ID_SIGFOX_PAC - PAC</b> \n
   *  32-bit long Porting Authorization Code which is used for device registration
   *  and is valid only once. The PAC should be kept secret as it proves
   *  the ownership of a device <b>[4 Bytes]</b>. \n */
  E_STACK_PARAM_ID_SIGFOX_PAC = 0x41U,
  /*! <b>0x42 @ref E_STACK_PARAM_ID_SIGFOX_MANUVERSION - Manufacturer Version</b> \n
   * 1 byte for individual use by manufacturer,
   *  used for indicating current software version <b>[1 Byte]</b>. \n */
  E_STACK_PARAM_ID_SIGFOX_MANUVERSION = 0x42U,
  /*! <b>0x43 : @ref E_STACK_PARAM_ID_SIGFOX_DEVKEY - Device Key</b> \n 128-bit long device key for encrypting and decrypting messages <b>[16 Bytes]</b>. \n */
  E_STACK_PARAM_ID_SIGFOX_DEVKEY = 0x43U,

  /* Mioty parameters */
  /*! <b>0x60 : @ref E_STACK_PARAM_ID_MIOTY_PROFILE - Profile</b> \n Uplink profile of current region, possible values are <b>[1 Byte]</b>: \n
   * \verbatim
    - 0x00: [EU0] Singleband Standard in 868.180 MHz
    - 0x01: [EU1] Dualband Standard in 868.180 MHz and 868.080 MHz
    - 0x02: [EU2] Dualband Standard in 867.625 MHz and 866.825 MHz
    - 0x03: [US0] Dualband Standard in 916.400 MHz and 915.600 MHz
    - 0x04: [IN866] Dualband Standard in 866.775 MHz and 866.875 MHz
   \endverbatim */
  E_STACK_PARAM_ID_MIOTY_PROFILE = 0x60U,
  /*! <b>0x61 : @ref E_STACK_PARAM_ID_MIOTY_MODE - Mode</b> \n Could have the following values <b>[1 Byte]</b>: \n
   * \verbatim
    - 0x00: [Standard] Best tradeoff between power consumption, range and robustness
    - 0x01: [Retransmission] Increased range and robustness, but twice the power consumption
    - 0x02: [Low latency] Lower latency, but lowest robustness and highest battery stress
   \endverbatim
    In profile <b>EU0</b> the mode <i>Retransmission</i> is not supported. \n*/
  E_STACK_PARAM_ID_MIOTY_MODE = 0x61U,
  /*! <b>0x62 : @ref E_STACK_PARAM_ID_MIOTY_EUI64 - EUI64</b> \n 64-bit long (at least inside the network) unique device EUI, MSB first <b>[8 Bytes]</b>. \n */
  E_STACK_PARAM_ID_MIOTY_EUI64 = 0x62U,
  /*! <b>0x63 : @ref E_STACK_PARAM_ID_MIOTY_NWKKEY - Network Key</b> \n
      128-bit long secret network key, MSB first <b>[16 Bytes]</b>. \n
      <b>This parameter is a write ony parameter and can't be requested using @ref SATP_STACK_GET.</b> \n*/
  E_STACK_PARAM_ID_MIOTY_NWKKEY = 0x63U,
  /*! <b>0x64 : @ref E_STACK_PARAM_ID_MIOTY_SHORT_ADDR - Short Address</b> \n
      The short address is a 16 bit address, MSB first. <b>[2 Byte].</b> \n*/
  E_STACK_PARAM_ID_MIOTY_SHORT_ADDR = 0x64U,
  /*! <b>0x65 : @ref E_STACK_PARAM_ID_MIOTY_TX_POWER - Transmission power in dBm</b> \n
   The transmission power is a signed integer value (two's complement) with a theoretical range of [-128dBm to +127dBm]. \n
   Please note that each target device allows different ranges. <b>[1 Byte].</b> <br> Example:
   * \verbatim
    - 0x05: represents a tx power of 5dBm
    - 0xFB: represents a tx power of -5dBm
   \endverbatim \n */
  E_STACK_PARAM_ID_MIOTY_TX_POWER = 0x65U,

  /*! <b>0xA0 : @ref E_STACK_PARAM_ID_WMBUS_COL_ADDR - WMBus Address</b>
     Address of the device. The address is formed in the following way <b>[8 Bytes]</b>: \n
    \verbatim
    Byte:  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
    Name:  | M | M | I | I | I | I | V | T |
      - M = Manufacture ID (2 Byte)
      - I = Ident number   (4 Byte)
      - V = Version        (1 Byte)
      - T = Type           (1 Byte)
    \endverbatim */
  E_STACK_PARAM_ID_WMBUS_COL_ADDR = 0xA0U,

  /*! <b>0xA1 : @ref E_STACK_PARAM_ID_WMBUS_COL_MODE -  WMBus mode </b> \n
      WMBUs mode for the collector device. <b>[2 Bytes]</b>. \n
   * \verbatim
     - 0x0002: S1
     - 0x0008: S2
     - 0x0010: T1
     - 0x0020: T2
     - 0x0100: C1
     - 0x0200: C2
   \endverbatim */
  E_STACK_PARAM_ID_WMBUS_COL_MODE = 0xA1U,
  /*! <b>0xA2 : @ref E_STACK_PARAM_ID_WMBUS_COL_TX_POWER - Transmission power in dBm</b> \n
   The transmission power is a signed integer value (two's complement) with a theoretical range of [-128dBm to +127dBm]. \n
   Please note that each target device allows different ranges. <b>[1 Byte].</b> <br> Example:
   * \verbatim
    - 0x05: represents a tx power of 5dBm
    - 0xFB: represents a tx power of -5dBm
   \endverbatim */
  E_STACK_PARAM_ID_WMBUS_COL_TX_POWER = 0xA2U,

  /*! <b>0xA3 : @ref E_STACK_PARAM_ID_WMBUS_COL_RX_NO_DECRYPT -  Controls if not installed meters will be received. </b> \n
      If the property is enabled the collector forwards all incoming telegrams to higher layers.
      If the property is diasbled only telegrams from installed meters and installation requests will be forwarded. <b>[1 Byte]</b>. \n
   * \verbatim
     - 0x00: disable
     - 0x01: enable (default)
   \endverbatim */
  E_STACK_PARAM_ID_WMBUS_COL_RX_NO_DECRYPT = 0xA3U,
  /*! <b>0xA4 : @ref E_STACK_PARAM_ID_WMBUS_COL_TPL_ACC_NO -  Collector TPL access number. </b> \n
      This access number appears in TPL header of collector telegram. <b>[1 Byte]</b>. \n */
  E_STACK_PARAM_ID_WMBUS_COL_TPL_ACC_NO = 0xA4U,
  /*! <b>0xA5 : @ref E_STACK_PARAM_ID_WMBUS_COL_ELL_ACC_NO -  Collector ELL access number. </b> \n
      This access number appears in ELL header of collector telegram. <b>[1 Byte]</b>. \n */
  E_STACK_PARAM_ID_WMBUS_COL_ELL_ACC_NO = 0xA5U,
  /*! <b>0xA6 : @ref E_STACK_PARAM_ID_WMBUS_COL_TX_ELL_HEADER -  Controls sending telegram with ELL Header. </b> \n
      If the property is enabled, the collector sends telegram with ELL header.
      If the property is diasbled, the collector sends telegram without ELL header. <b>[1 Bytes]</b>. \n
   * \verbatim
     - 0x00: disable
     - 0x01: enable (default)
   \endverbatim */
  E_STACK_PARAM_ID_WMBUS_COL_TX_ELL_HEADER = 0xA6U,
  /*! <b>0xA7 : @ref E_STACK_PARAM_ID_WMBUS_COL_TX_PARAMS - TX parameters. </b> \n
      Read only. The TX parameters contain information of the previously sent telegram <b>[11 Bytes]</b>. \n
   * \verbatim
     Byte:  |        0 - 7        |    8    |      9      |     10      |
     Name:  | Dest. meter address | C-field | ELL acc no. | TPL acc no. |
   \endverbatim */
  E_STACK_PARAM_ID_WMBUS_COL_TX_PARAMS = 0xA7U,
  /*! <b>0xA8 : @ref E_STACK_PARAM_ID_WMBUS_COL_MSG_CTR_INCREMENT_VALUE -  Increment value for the message counter in sending telegram. </b> \n
      When a sending telegram is created with AFL layer, the message counter will be increment with this value. <b>[1 Byte]</b>. \n */
  E_STACK_PARAM_ID_WMBUS_COL_MSG_CTR_INCREMENT_VALUE = 0xA8U,
  /*! <b>0xC0 : @ref E_STACK_PARAM_ID_MBUS_PRIMARY_BAUD_RATE -  Baud rate </b> \n
      Defined the used baud rate to transmit/receive over wired M-Bus.
      <b>[1 Bytes]</b> \n
      The following baud rates are supported:
    \verbatim
     - 0x00: 300 Bd (default)
     - 0x01: 2400 Bd
     - 0x02: 9600 Bd
     - 0x03: 19200 Bd
     - 0x04: 38400 Bd
   \endverbatim */
  E_STACK_PARAM_ID_MBUS_PRIMARY_BAUD_RATE = 0xC0U,
  /*! <b>0xD0 : @ref E_STACK_PARAM_ID_MBUS_SECONDARY_BAUD_RATE -  Baud rate </b> \n
      Defined the used baud rate to transmit/receive over wired M-Bus.
      <b>[1 Bytes]</b> \n
      <b>Note:</b> \n
      This value only needs to be configured if the Device does not support the
      automatic baud rate detection. Check your device documentation for more
      information.
      The following baud rates are supported:
    \verbatim
     - 0x00: 300 Bd (default)
     - 0x01: 2400 Bd
     - 0x02: 9600 Bd
     - 0x03: 19200 Bd
     - 0x04: 38400 Bd
   \endverbatim */
  E_STACK_PARAM_ID_MBUS_SECONDARY_BAUD_RATE = 0xD0U,
  /*! <b>0xD1 : @ref E_STACK_PARAM_ID_MBUS_SECONDARY_DLL_A_FIELD -  A-Field </b> \n
      Specifies the A-Field inside the Data Link Layer (Primary address). <b>[1 Bytes]</b> \n
      The following A-fields are supported:
    \verbatim
     - 0x00        : Reserved for unconfigured secondary devices.
     - 0x01 - 0xFA : Used for primary addressing of secondary devices.
     - 0xFD        : Used for secondary addressing.
   \endverbatim */
  E_STACK_PARAM_ID_MBUS_SECONDARY_DLL_A_FIELD = 0xD1U,
  /*! <b>0xD2 : @ref E_STACK_PARAM_ID_MBUS_SECONDARY_SEC_ADDR -  Secondary address </b> \n
      Specifies the secondary (TPL) address of the wired M-Bus secondary device.
      <b>[8 Bytes]</b> \n
      The secondary address is formed in the following way: \n
    \verbatim
    Byte:  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
    Name:  | M | M | I | I | I | I | V | T |
      - M = Manufacture ID (2 Byte)
      - I = Ident number   (4 Byte)
      - V = Version        (1 Byte)
      - T = Type           (1 Byte)
    \endverbatim */
  E_STACK_PARAM_ID_MBUS_SECONDARY_SEC_ADDR = 0xD2U,
  /*! <b>0xD3 : @ref E_STACK_PARAM_ID_MBUS_SECONDARY_ENCRYPT_MODE - Encryption mode</b> \n
      Supported encryption modes <b>[1 Byte]</b>: \n
   \verbatim
     - 0x00: no encryption
     - 0x05: security Profile A (AES-CBC)
     - 0x07: security Profile B (AES-CBC + CMAC)
   \endverbatim */
  E_STACK_PARAM_ID_MBUS_SECONDARY_ENCRYPT_MODE = 0xD3U,
  /*! <b> 0xD4 : @ref E_STACK_PARAM_ID_MBUS_SECONDARY_KEY - Encryption key</b> \n
      128 bit encryption key of the device <b>[16 Bytes]</b>. \n*/
  E_STACK_PARAM_ID_MBUS_SECONDARY_KEY = 0xD4U,
  /*! <b>0xD5 : @ref E_STACK_PARAM_ID_MBUS_SECONDARY_STATUS - TPL status field</b> \n
      Status byte in meter message <b>[1 Byte]</b>: \n
   \verbatim
        ___________________________________
       |Bit  | Meaning when bit is set     |
       |-----|-----------------------------|
       | 7   | Manufacture specific        |
       |-----|-----------------------------|
       | 6   | Manufacture specific        |
       |-----|-----------------------------|
       | 5   | Manufacture specific        |
       |-----|-----------------------------|
       | 4   | Temporary error             |
       |-----|-----------------------------|
       | 3   | Permanent error             |
       |-----|-----------------------------|
       | 2   | Power low                   |
       |-----|-----------------------------|
       | 1,0 | 00 No error                 |
       |     | 01 Application busy         |
       |     | 10 Any application error    |
       |     | 11 Abnormal condition/alarm |
       |-----|-----------------------------|
   \endverbatim */
  E_STACK_PARAM_ID_MBUS_SECONDARY_STATUS = 0xD5,
  /* Generic parameters */
  /*! <b>0xFD : @ref E_STACK_PARAM_ID_MEMORY_OCCUPIED - RAM memory occupied</b> \n
      RAM memory usage in bytes. <b>[2 Byte]</b>. \n */
  E_STACK_PARAM_ID_MEMORY_OCCUPIED = 0xFDU,
  /*! <b>0xFE : @ref E_STACK_PARAM_ID_MEMORY_PEAK - RAM usage memory peak</b> \n
      Memory peak allocation in bytes. <b>[2 Byte]</b>. \n */
  E_STACK_PARAM_ID_MEMORY_PEAK = 0xFEU,
  /*! <b>0xFF : @ref E_STACK_PARAM_ID_GENERIC_RX_DATA_LENGTH - Received data length</b> \n
      Data length of the received message <b>[2 Byte]</b>. \n */
  E_STACK_PARAM_ID_GENERIC_RX_DATA_LENGTH = 0xFFU,
} stackParamId_t;

/*!
 * @brief Sending related parameter IDs for implemented stacks
 * @details
 *    @if MIOTY_DOC
 *  * <b>Parameters of the mioty endpoint device:</b> \n
 *    > @copydetails E_STACK_SEND_PARAM_ID_MIOTY_MPF
 *    > @copydetails E_STACK_SEND_PARAM_ID_MIOTY_ACK_REQUEST
 *    > @copydetails E_STACK_SEND_PARAM_ID_MIOTY_RX_WINDOW
 *    @endif
 *    @if MBUS_PRIMARY_DEVICE_DOC
 *  * <b>Parameters of the wired M-Bus Primary Device:</b> \n
 *    > @copydetails E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_DLL_C_FIELD
 *    > @copydetails E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_DLL_A_FIELD
 *    > @copydetails E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_TPL_CI_FIELD
 *    > @copydetails E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_SEC_ADDR
 *    @endif
 *    @if MBUS_SECONDARY_DEVICE_DOC
 *  * <b>Parameters of the wired M-Bus Secondary Device:</b> \n
 *    > @copydetails E_STACK_SEND_PARAM_ID_MBUS_SECONDARY_DATA_TYPE
 *    @endif
 */
typedef enum
{
  /*! <b>0x60 : @ref E_STACK_SEND_PARAM_ID_MIOTY_MPF - MAC Payload format</b> \n
      Used to indicate the format of the MAC payload. Set to 0x00 to omit that
      the MPF field is used. <b>[1 Byte].</b> \n*/
  E_STACK_SEND_PARAM_ID_MIOTY_MPF = 0x60U,
  /*! <b>0x61 : @ref E_STACK_SEND_PARAM_ID_MIOTY_ACK_REQUEST - Transmission acknowledgement</b> \n
      If an end point requires a downlink response from the base station after
      its uplink communication, e.g. for acknowledgment of the uplink message,
      it shall set this param to 0x01. This setting is only valid for the next
      uplink transmission. In the default case no transmission acknowledgment
      will be requested. The base station may refuse the downlink transmission
      due to the limited duty cycle in the base station transmission.
      This parameter is only available for bidirectional mioty end points.
      <b>[1 Byte].</b> \n
      \verbatim
       - 0x00: No transmission acknowledgement required (default).
       - 0x01: Transmission acknowledgement required.
      \endverbatim */
  E_STACK_SEND_PARAM_ID_MIOTY_ACK_REQUEST = 0x61U,
  /*! <b>0x62 : @ref E_STACK_SEND_PARAM_ID_MIOTY_RX_WINDOW - Enables/Disables RX Window</b> \n
   Bidirectional end points provide a rx window after each uplink transmission by default.
   In order to save energy it could be usefull to deactivate the rx window by setting this param to 0x00.
   This setting is valid until the user set this param back to 0x01.
   This parameter is only available for bidirectional mioty end points. <b>[1 Byte].</b> \n
   * \verbatim
    - 0x00: No rx window will be opened after transmitting an uplink frame.
    - 0x01: A rx  window will be opened after transmitting an uplink frame (default).
   \endverbatim */
  E_STACK_SEND_PARAM_ID_MIOTY_RX_WINDOW = 0x62U,

  /*! <b>0xC0 : @ref E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_DLL_C_FIELD -  C-Field </b> \n
      Used control field in the Data link layer. <b>[1 Bytes]</b> \n
      The following C-fields are supported:
    \verbatim
     - 0x00: SND-NKE Link Reset after communication.
     - 0x03: SND-UD  Send Command (Send user Data).
     - 0x0A: REQ_UD1 Alarm Request (Request User Data Class1)
     - 0x0B: REQ_UD2 Data Request (Request User Data Class2)
   \endverbatim */
  E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_DLL_C_FIELD = 0xC0U,
  /*! <b>0xC1 : @ref E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_DLL_A_FIELD -  A-Field </b> \n
      Specifies the A-Field inside the Data Link Layer (Primary address). <b>[1 Bytes]</b> \n
      The following A-fields are supported:
    \verbatim
     - 0x00        : Reserved for unconfigured secondary devices.
     - 0x01 - 0xFA : Used for primary addressing of secondary devices.
     - 0xFB        : Used for management communication with primary master repeater.
     - 0xFC        : (reserved)
     - 0xFD        : Used for secondary addressing.
     - 0xFE        : Used for test and diagnostics.
     - 0xFF        : Broadcast address.
   \endverbatim */
  E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_DLL_A_FIELD = 0xC1U,
  /*! <b>0xC2 : @ref E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_TPL_CI_FIELD -  CI-Field </b> \n
      Used Control Information-Field inside the TPL. This value is only used if
      the param @ref E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_DLL_C_FIELD is configured
      to transmit a SND-UD message. <b>[1 Bytes]</b> \n
      The following CI-fields are supported:
    \verbatim
    | CI-Field|             Function            | TPL-header-type |
    |=========|=================================|=================|
    | 0x50    | Application Reset or Select     | None            |
    | 0x51    | Command                         | None            |
    | 0x52    | Selection of Device             | None            |
    | 0x54    | Request of selected Application | None            |
    | 0x5A    | Command                         | Short           |
    | 0xB8    | Set baud rate to 300 baud       | None            |
    | 0xBB    | Set baud rate to 2400 baud      | None            |
    | 0xBD    | Set baud rate to 9600 baud      | None            |
    | 0xBE    | Set baud rate to 19200 baud     | None            |
    | 0xBF    | Set baud rate to 38400 baud     | None            |
   \endverbatim */
  E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_TPL_CI_FIELD = 0xC2U,
  /*! <b>0xC3 : @ref E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_SEC_ADDR -  Secondary address </b> \n
      Specifies the secondary address of the wired M-Bus secondary device which
      should be addressed. If the secondary device is installed the enryption
      mode will be selected automatically. If the secondary device is not
      installed no encryption/decryption is supported. <b>[8 Bytes]</b> \n
      The secondary address is formed in the following way: \n
    \verbatim
    Byte:  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
    Name:  | M | M | I | I | I | I | V | T |
      - M = Manufacture ID (2 Byte)
      - I = Ident number   (4 Byte)
      - V = Version        (1 Byte)
      - T = Type           (1 Byte)
    \endverbatim */
  E_STACK_SEND_PARAM_ID_MBUS_PRIMARY_SEC_ADDR = 0xC3U,
  /*! <b>0xD0 : @ref E_STACK_SEND_PARAM_ID_MBUS_SECONDARY_DATA_TYPE -  Data Type </b> \n
      Specifies the type of data which should be send. \n
      Possible data types: \n
      \verbatim
      | Data types|  Data Type   | Request telegram |
      |===========|==============|==================|
      | 0x00      |  User Data   | REQ-UD2          |
      | 0x01      |  Alarm Data  | REQ-UD1          |
      \endverbatim
      Caused by the wired M-Bus frame format a maximum of 240 bytes is
      supported. \n If encryption is enabled less bytes are supported. \n
      <b>Note:</b> \n
      The secondary device is polled by the primary device. So when calling the
      @ref sf_stack_send() function the data can not be transmitted immediately.
      The data and the len of the data which needs to be transmitted will be
      stored. In case the primary device request User/Alarm Data the data will
      be transmitted. */
  E_STACK_SEND_PARAM_ID_MBUS_SECONDARY_DATA_TYPE = 0xD0,
} stackSendParamId_t;

/*!
 * @brief Parameter IDs for implemented stacks
 * @details
 *    @if MBUS_PRIMARY_DEVICE_DOC
 *  * <b>Available parameters for wired M-Bus Primary Devices:</b> \n
 *    > @copydetails E_STACK_RECEIVE_PARAM_ID_MBUS_PRIMARY_DETAILS
 *    @endif
 *    @if MBUS_SECONDARY_DEVICE_DOC
 *  * <b>Available parameters for wired M-Bus Secondary Devices:</b> \n
 *    > @copydetails E_STACK_RECEIVE_PARAM_ID_MBUS_SECONDARY_DETAILS
 *    @endif
 */
typedef enum
{
  /*! <b>0xC0 : @ref E_STACK_RECEIVE_PARAM_ID_MBUS_PRIMARY_DETAILS -  Detailed
      wired m-Bus frame </b> \n
   */
  E_STACK_RECEIVE_PARAM_ID_MBUS_PRIMARY_DETAILS = 0xC0U,
  /*! <b>0xD0 : @ref E_STACK_RECEIVE_PARAM_ID_MBUS_SECONDARY_DETAILS -  Detailed
      wired m-Bus frame </b> \n
   */
  E_STACK_RECEIVE_PARAM_ID_MBUS_SECONDARY_DETAILS = 0xD0U,
} stackReceiveParamId_t;

/*!
 * @brief Supported Devices.
 * @details
 *    @if MBUS_PRIMARY_DEVICE_DOC
 *    > @copydetails E_STACK_DEVICE_SECONDARY
 *    @endif
 */
typedef enum
{
  /*! <b>0x00 : @ref E_STACK_DEVICE_SECONDARY -  wired M-Bus secondary device
      </b> \n */
  E_STACK_DEVICE_SECONDARY = 0x00U,
} stackDevice_t;

/*!
 * @brief Type of occurred event.
 * @details
 *    <b>Stack event type [1 Byte]:</b> \n
 *    > @copydetails E_STACK_EVENT_SLEEP \n
 *    > @copydetails E_STACK_EVENT_RX_ERROR \n
 *    > @copydetails E_STACK_EVENT_TX_SUCCESS \n
 *    > @copydetails E_STACK_EVENT_RX_SUCCESS \n
 *    > @copydetails E_STACK_EVENT_PERSISTENT_DATA_UPDATE \n
 *    > @copydetails E_STACK_EVENT_CRYPTO_ERROR \n
 *    > @copydetails E_STACK_EVENT_WAKEUP \n
 *    @cond DOC_SERIAL_STACK_HOST
 *    > @copydetails E_STACK_EVENT_SERIAL_CONFIRM_SUCCESS \n
 *    > @copydetails E_STACK_EVENT_SERIAL_CONFIRM_FAIL \n
 *    @endcond
 */
typedef enum
{
  /*! <b>0x00 : @ref E_STACK_EVENT_SLEEP - Sleep event </b> \n
      It is possible to set the device in a sleep state without RAM loss. \n
      It is not recommended to do anything else at this event. \n
      This event does not provide additional payload. */
  E_STACK_EVENT_SLEEP = 0x00U,
  /*! <b>0x01 : @ref E_STACK_EVENT_RX_ERROR - Reception error </b> \n
      An error occurred while receiving a message. \n
      This event does not provide additional payload. */
  E_STACK_EVENT_RX_ERROR = 0x01U,
  /*! <b>0x02 : @ref E_STACK_EVENT_TX_SUCCESS - Transmission successful </b> \n
      Indicates a transmission. \n
      This event does not provide additional payload. */
  E_STACK_EVENT_TX_SUCCESS = 0x02U,
  /*! <b>0x03 : @ref E_STACK_EVENT_RX_SUCCESS - Reception successful </b> \n
      A message has been received successfully. \n
      The content of the data is the message size in bytes. */
  E_STACK_EVENT_RX_SUCCESS = 0x03U,
  /*! <b>0x04 : @ref E_STACK_EVENT_PERSISTENT_DATA_UPDATE - Persistent data update </b> \n
      Indicates the stack has updated the persistent data. The application should store the updated data to a NVM.\n
      The content of the data is number of bytes to update. */
  E_STACK_EVENT_PERSISTENT_DATA_UPDATE = 0x04U,
  /*! <b>0x05 : @ref E_STACK_EVENT_CRYPTO_ERROR - En-/decryption error </b> \n
      An error in enryption or decryption of a message occurred. \n
      This event does not provide additional payload. */
  E_STACK_EVENT_CRYPTO_ERROR = 0x05U,
  /// @cond DOC_SERIAL_STACK_HOST
  /*! <b>0x06 : @ref E_STACK_EVENT_SERIAL_CONFIRM_SUCCESS - Serial confirmation success </b> \n
      Confirms that the last SATP request was successful. In case the last request
      results in a confirmation with data then this data is attached to this event.
      The data memory is released once the event function returns. Data is e.g.
      attached to confirmation of the function @ref sf_stack_get(). \n
      This event is only used for Stack host implementation. */
  E_STACK_EVENT_SERIAL_CONFIRM_SUCCESS = 0x06U,
  /// @endcond
  /// @cond DOC_SERIAL_STACK_HOST
  /*! <b>0x07 : @ref E_STACK_EVENT_SERIAL_CONFIRM_FAIL - Serial confirmation fail </b> \n
      Confirms that the last SATP request has failed. This event may be raised with 1 Byte payload of type
      @ref stackReturn_t. \n
      This event is only used for Stack host implementation. */
  E_STACK_EVENT_SERIAL_CONFIRM_FAIL = 0x07U,
  /// @endcond
  /*! <b>0x08 : @ref E_STACK_EVENT_WAKEUP - Wakeup event </b> \n
      Indicates an wakeup of the system. \n
      This event does not provide additional payload. */
  E_STACK_EVENT_WAKEUP = 0x08U,
  /*! <b>0x00 : @ref E_STACK_EVENT_DEEP_SLEEP - Deep Sleep event </b> \n
      It is possible to set the device in a sleep state without RAM loss. \n
      It is not recommended to do anything else at this event. \n
      This event does not provide additional payload. */
  E_STACK_EVENT_DEEP_SLEEP = 0x09U,
} stackEvent_t;

/*==============================================================================
                            TYPEDEF FUNCTION INDICATOR
==============================================================================*/
/*!
 * @brief Callback function to inform application about the events by the stack.
 *
 * @param event @copydetails stackEvent_t
 *
 * @param pData Pointer to data that are received from or required by the event occurred,
 *              depending on the event type.
 *
 * @param dataLen Length of data
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
typedef stackReturn_t ( sf_callbackFunc_t ) ( stackEvent_t event, uint8_t *pData,
                                              uint16_t dataLen );

/*!
 * @brief Callback function to inform application about incoming serial frames
 *        with the CUSTOMER STACK ID.
 *
 * @param pData Pointer to data that are received.
 *
 * @param len   Length of the data which have been received.
 *
 * @param pResp Pointer to a pointer to a data buffer which shall be sent as response.
 *
 * @param pRespLen Length of the data which shall be sent as a response.
 *
 * @return Status of the operation. \n
 *         @copydetails stackReturn_t
 */
typedef stackReturn_t ( sf_callbackFuncSerial_t ) ( uint8_t* pData, uint16_t len,
                                                    uint8_t **pResp, uint16_t* pRespLen );

/*!@} end of MS_COM_IF */
/******************************************************************************/

#endif /* __SF_STACK_TYPES_H__ */
#ifdef __cplusplus
}
#endif
