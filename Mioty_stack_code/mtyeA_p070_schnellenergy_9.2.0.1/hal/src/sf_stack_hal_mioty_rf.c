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
 * @copyright  STACKFORCE GmbH, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @brief      STACKFORCE example HAL for RF.
 */


/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
/* Standard libraries */
#include <stdint.h>
#include <stdbool.h>
/* SDK header. */
#include <ti/sysbios/knl/Task.h>
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/rf_data_entry.h)
#include DeviceFamily_constructPath(driverlib/rf_prop_mailbox.h)
/* Module specific headers. */
#if(SF_CC13XX_TARGET == SF_TARGET_CC13X0_LP ||\
    SF_CC13XX_TARGET == SF_TARGET_CC13X0_COUA)
#include "sf_cc13xx_miotyRegisters.h"
#elif(SF_CC13XX_TARGET == SF_TARGET_CC13X2_LP)
#include "sf_cc13xx_miotyRegisters.h"
#endif /* SF_CC13XX_TARGET */
#include "sf_stack_hal_mioty_rf.h"

/*==============================================================================
                            MACROS
==============================================================================*/
#ifndef SF_CC13XX_TARGET
#error Please define which target is used.
#endif /* SF_CC13XX_TARGET */
/* Oversampling x8 is enabled by default */
#ifndef SF_MIOTY_RADIO_OVERSAMPLINGX8_ENABLED
  #define SF_MIOTY_RADIO_OVERSAMPLINGX8_ENABLED 0U
#endif
#ifndef UINT8_TO_UINT32
#define UINT8_TO_UINT32(x)                 ((((uint32_t) (x)[0U])<<24U) + \
                                            (((uint32_t) (x)[1U])<<16U) + \
                                            (((uint32_t) (x)[2U])<<8U) + \
                                                         (x)[3U])
#endif /* UINT8_TO_UINT32 */
/* Number of bit inside one byte. */
#define SF_MIOTY_RADIO_HALF_BYTE_IN_BIT        0x04U
/* The minimum Tx payload length. */
#define SF_MIOTY_RADIO_TX_PAYLOAD_LEN_MIN      (4)
/* Number of samples in pingpong entry. */
#define SF_MIOTY_RADIO_SAMPLES_PINGPONG_ENTRY  (32)
/* The index of the first sample to be saved */
#define SF_MIOTY_RADIO_FIRST_SAMPLE_TO_SAVE    (0)
/* Read entry disable status. */
#define SF_MIOTY_RADIO_DATA_ENTRY_DISABLE      (5)
/* Number of history samples. */
#define SF_MIOTY_RADIO_DS8_N_TAPS              (108)
#define SF_MIOTY_RADIO_DS_FACTOR               (8)
#define SF_MIOTY_RADIO_HISTORY_SAMPLES         (SF_MIOTY_RADIO_DS8_N_TAPS -\
                                               SF_MIOTY_RADIO_DS_FACTOR)
/* Number of samples of the initial entry. */
#define SF_MIOTY_RADIO_SAMPLES_INITIAL_ENTRY   (SF_MIOTY_RADIO_SAMPLES_PINGPONG_ENTRY + \
                                               SF_MIOTY_RADIO_HISTORY_SAMPLES)
/* Rate word used to determine symbol rate. */
#define SF_MIOTY_RADIO_RATEWORD                (0xD0U)
/* Prescaler value used to determine symbol rate. */
#define SF_MIOTY_RADIO_PRESCALE                (0x4)
/* Receiver bandwidth. */
#define SF_MIOTY_RADIO_RXBW                    (0x20)
/* Packed sample length */
#define SF_MIOTY_RADIO_PACKED_SAMPLE_LEN       (3U)
/* Unpacked sample length */
#define SF_MIOTY_RADIO_UNPACKED_SAMPLE_LEN     (4U)
/* Number of partial read entries */
#define SF_MIOTY_RADIO_PARTIAL_READ_ENTRY_CNT  (3U)
/* A buffer for a received hop IQ data is in packed format (3B/sample).
   It also reserves additional 12B in front for the header filled by
   the RF core. We substract 4 in size because 'sizeof(rfc_dataEntryPartial_t)'
   is 16 instead of 12. That is because the last field of the rfc_dataEntryPartial_t
   is already a buffer for IQ data. See th rfc_dataEntryPartial_t definition. */
#define SF_MIOTY_RADIO_INITIAL_ENTRY_BUF_SIZE  (sizeof(rfc_dataEntryPartial_t) +\
                                               (SF_MIOTY_RADIO_SAMPLES_INITIAL_ENTRY *\
                                                SF_MIOTY_RADIO_PACKED_SAMPLE_LEN ) - 4 )
/* Size of ping-pong entry buffer. The same rules applied as for initial entry
   buffer size. */
#define SF_MIOTY_RADIO_PINGPONG_ENTRY_BUF_SIZE (sizeof(rfc_dataEntryPartial_t) +\
                                                (SF_MIOTY_RADIO_SAMPLES_PINGPONG_ENTRY *\
                                                 SF_MIOTY_RADIO_PACKED_SAMPLE_LEN) - 4)
/* Align values to 4 byte boundary */
#define SF_MIOTY_RADIO_4BYTE_ALIGN(value)      ((value + 3) & ~3)
/*==============================================================================
                              GLOBAL VARIABLES
==============================================================================*/
/* Hop IQ receiver object's data. */
struct
{
  /* Pointers to partial read entries in memory. */
  union
  {
    rfc_dataEntryPartial_t* pFields;
    uint8_t* pBytes;
  } partialReadEntry[SF_MIOTY_RADIO_PARTIAL_READ_ENTRY_CNT];
  /* A handle to the RX command posted in PrepareRx(). */
  RF_CmdHandle rxCmd;
  /* A number of samples to save in app. buffer. */
  uint16_t samplesToSave;
  /* Remaining number of samples to be captured. */
  uint16_t samplesToCapture;
  /* Identifies which partial buffer is currently filled. */
  uint8_t currentPartialEntry;
  /* Application IQ buffer. */
  int16_t* pOutIQBuf;
  /** We need to store 1 byte of payload for each transmission. The remaining
   *  bits will be transmitted and stored inside the syncword configuration. */
  uint8_t payloadByte;
  /* Buffer to store unpacked chunk of IQ data */
  int16_t* pUnpackedIqBuf;
  /* Shift value used to recenter frequency after reception */
  int32_t shift;
  /** Stores the handle to the test command. */
  RF_CmdHandle rfCmdHandleTest;
} gMiotyRfCtx;
/* Global rfObject used to open a rf handle.  */
RF_Object gRfObject;
/* Pointer to the opened rf handle. */
RF_Handle gpRfHandle = NULL;
/* RF Tx Test command. */
rfc_CMD_TX_TEST_t gRfCmdTxTest = {.commandNo               = 0x0808,
                                 .status                   = 0x0000,
                                 .pNextOp                  = 0,
                                 .startTime                = 0x00000000,
                                 .startTrigger.triggerType = 0x0,
                                 .startTrigger.bEnaCmd     = 0x0,
                                 .startTrigger.triggerNo   = 0x0,
                                 .startTrigger.pastTrig    = 0x0,
                                 .condition.rule           = 0x1,
                                 .condition.nSkip          = 0x0,
                                 .config.bUseCw            = 0,
                                 .config.bFsOff            = 0x1,
                                 .config.whitenMode        = 0x2,
                                 .__dummy0                 = 0x00,
                                 .txWord                   = 0xAAAA,
                                 .__dummy1                 = 0x00,
                                 .endTrigger.triggerType   = 0x1,
                                 .endTrigger.bEnaCmd       = 0x0,
                                 .endTrigger.triggerNo     = 0x0,
                                 .endTrigger.pastTrig      = 0x0,
                                 .syncWord                 = 0x930B51DE,
                                 .endTime                  = 0x00000000};
/* RF Rx Test command. */
rfc_CMD_RX_TEST_t gRfCmdRxTest = {.commandNo               = 0x0807,
                                 .status                   = 0x0000,
                                 .pNextOp                  = 0,
                                 .startTime                = 0x00000000,
                                 .startTrigger.triggerType = 0x0,
                                 .startTrigger.bEnaCmd     = 0x0,
                                 .startTrigger.triggerNo   = 0x0,
                                 .startTrigger.pastTrig    = 0x0,
                                 .condition.rule           = 0x1,
                                 .condition.nSkip          = 0x0,
                                 .config.bEnaFifo          = 0,
                                 .config.bFsOff            = 0x1,
                                 .config.bNoSync           = 0x1,
                                 .endTrigger.triggerType   = 0x1,
                                 .endTrigger.bEnaCmd       = 0x0,
                                 .endTrigger.triggerNo     = 0x0,
                                 .endTrigger.pastTrig      = 0x0,
                                 .syncWord                 = 0x930B51DE,
                                 .endTime                  = 0x00000000};

const int16_t gSinLut256[256] =
{
  0, 804, 1608, 2410, 3212, 4011, 4808, 5602, 6393, 7179, 7962, 8739, 9512, 10278, 11039, 11793,
  12539, 13279, 14010, 14732, 15446, 16151, 16846, 17530, 18204, 18868, 19519, 20159, 20787, 21403, 22005, 22594,
  23170, 23731, 24279, 24811, 25329, 25832, 26319, 26790, 27245, 27683, 28105, 28510, 28898, 29268, 29621, 29956,
  30273, 30571, 30852, 31113, 31356, 31580, 31785, 31971, 32137, 32285, 32412, 32521, 32609, 32678, 32728, 32757,
  32767, 32757, 32728, 32678, 32609, 32521, 32412, 32285, 32137, 31971, 31785, 31580, 31356, 31113, 30852, 30571,
  30273, 29956, 29621, 29268, 28898, 28510, 28105, 27683, 27245, 26790, 26319, 25832, 25329, 24811, 24279, 23731,
  23170, 22594, 22005, 21403, 20787, 20159, 19519, 18868, 18204, 17530, 16846, 16151, 15446, 14732, 14010, 13279,
  12539, 11793, 11039, 10278, 9512, 8739, 7962, 7179, 6393, 5602, 4808, 4011, 3212, 2410, 1608, 804,
  0, -804, -1608, -2410, -3212, -4011, -4808, -5602, -6393, -7179, -7962, -8739, -9512, -10278, -11039, -11793,
  -12539, -13279, -14010, -14732, -15446, -16151, -16846, -17530, -18204, -18868, -19519, -20159, -20787, -21403, -22005, -22594,
  -23170, -23731, -24279, -24811, -25329, -25832, -26319, -26790, -27245, -27683, -28105, -28510, -28898, -29268, -29621, -29956,
  -30273, -30571, -30852, -31113, -31356, -31580, -31785, -31971, -32137, -32285, -32412, -32521, -32609, -32678, -32728, -32757,
  -32767, -32757, -32728, -32678, -32609, -32521, -32412, -32285, -32137, -31971, -31785, -31580, -31356, -31113, -30852, -30571,
  -30273, -29956, -29621, -29268, -28898, -28510, -28105, -27683, -27245, -26790, -26319, -25832, -25329, -24811, -24279, -23731,
  -23170, -22594, -22005, -21403, -20787, -20159, -19519, -18868, -18204, -17530, -16846, -16151, -15446, -14732, -14010, -13279,
  -12539, -11793, -11039, -10278, -9512, -8739, -7962, -7179, -6393, -5602, -4808, -4011, -3212, -2410, -1608, -804
};

/* Filter coefficients for the /8 downsampler in Q19 format. */
const int32_t pDownsamplerDiv8CoeffInv[SF_MIOTY_RADIO_DS8_N_TAPS] =
{
  -194, -272, -428, -604, -781, -931, -1025, -1030, -922, -686, -326, 138, 662, 1188, 1641,
  1948, 2039, 1868, 1418, 711, -187, -1173, -2113, -2860, -3273, -3239, -2696, -1648, -176,
  1564, 3351, 4925, 6019, 6395, 5883, 4418, 2063, -982, -4386, -7710, -10452, -12100, -12192,
  -10379, -6476, -499, 7319, 16535, 26530, 36563, 45839, 53595, 59172, 62087, 62087, 59172,
  53595, 45839, 36563, 26530, 16535, 7319, -499, -6476, -10379, -12192, -12100, -10452, -7710,
  -4386, -982, 2063, 4418, 5883, 6395, 6019, 4925, 3351, 1564, -176, -1648, -2696, -3239, -3273,
  -2860, -2113, -1173, -187, 711, 1418, 1868, 2039, 1948, 1641, 1188, 662, 138, -326,
  -686, -922, -1030, -1025, -931, -781, -604, -428, -272, -194
};

/*==============================================================================
                               LOCAL FUNCTION
==============================================================================*/
/*============================================================================*/
/*!
 * @brief Returns radio RAM memory information: free RAM size + free RAM start.
 *
 * @param pFreeRamStart   Pointer to the memory where to write the free ram
 *                        start offset.
 *
 * @return total free ram size.
 */
/*============================================================================*/
uint16_t loc_getRadioMemInfo(uint16_t* pFreeRamStart)
{
  rfc_CMD_GET_FW_INFO_t RF_cmdGetFwInfo;
  /* Parameters to initialize RF core. */
  RF_Params rfParams;

  if( NULL == pFreeRamStart )
  {
    return 0;
  }

  RF_cmdGetFwInfo.commandNo = CMD_GET_FW_INFO;

  memset(&gRfObject, 0, sizeof(RF_Object));

  RF_Params_init(&rfParams);

  /* Ensure that the previous handle is closed before we open a new one. */
  if(NULL != gpRfHandle)
  {
    RF_close(gpRfHandle);
    gpRfHandle = NULL;
  }/* if */

  gpRfHandle = RF_open(&gRfObject, &gRfDl_prop,
                                  (RF_RadioSetup*)&gRfDl_cmdPropRadioDivSetup,
                                  &rfParams);
  gRfDl_cmdFs.synthConf.bTxMode = 0;
  RF_runCmd(gpRfHandle, (RF_Op*)&gRfDl_cmdFs, RF_PriorityNormal, 0, 0);
  RF_Stat st = RF_runImmediateCmd(gpRfHandle, (uint32_t*)&RF_cmdGetFwInfo);

  RF_close(gpRfHandle);
  gpRfHandle = NULL;

  *pFreeRamStart = RF_cmdGetFwInfo.startOffset;

  return RF_cmdGetFwInfo.freeRamSz;
}

#if SF_MIOTY_RADIO_OVERSAMPLINGX8_ENABLED
/*============================================================================*/
/*!
 * @brief A function that shifts a frequency of a packed IQ block.
 *
 *  @param pInPackedIq    Array of captured samples in packed format (3B/smpl)
 *  @param pOutUnpackedIq Array of unpacked samples
 *  @param samplesCnt     Number of samples
 *  @param resetPhase     End of phase flag
 */
/*============================================================================*/
static void loc_shiftFrequency(uint8_t* pInPackedIq, int16_t* pOutUnpackedIq,
                               uint32_t samplesCnt, bool resetPhase)
{
  static uint32_t phaseCos = 64 << 24;
  static uint32_t phaseSin = 0;

  if(resetPhase)
  {
    phaseCos = 64 << 24;
    phaseSin = 0;
  }

  for(uint16_t i = 0; i < samplesCnt; i++)
  {
    int16_t I = ((pInPackedIq[0] << 4) | ( (pInPackedIq[1] & 0x000F) << 12 ));
    int16_t Q = ((pInPackedIq[2] << 8) | ( (pInPackedIq[1] & 0xFFF0)));

    int16_t cosine = gSinLut256[phaseCos >> 24];
    int16_t sine   = gSinLut256[phaseSin >> 24];

    phaseCos += gMiotyRfCtx.shift;
    phaseSin += gMiotyRfCtx.shift;

    int32_t shI = _ssata((int32_t)I*cosine + (int32_t)Q*sine, 15, 16);
    int32_t shQ = _ssata((int32_t)Q*cosine - (int32_t)I*sine, 15, 16);

    pOutUnpackedIq[0] = shI;
    pOutUnpackedIq[1] = shQ;

    pInPackedIq += 3;
    pOutUnpackedIq += 2;
  } /* for */
}/* loc_shiftFrequency */
#else
/*============================================================================*/
/*!
 * @brief A function that shifts a frequency to recenter it.
 */
/*============================================================================*/
static void loc_shiftFrequency(void)
{
  uint32_t phaseCos = 64 << 24;
  uint32_t phaseSin = 0;

  for(uint16_t i = 0; i < gMiotyRfCtx.samplesToSave; i++)
  {
    int16_t cosine = gSinLut256[phaseCos >> 24];
    int16_t sine   = gSinLut256[phaseSin >> 24];

    phaseCos += gMiotyRfCtx.shift;
    phaseSin += gMiotyRfCtx.shift;

    int32_t re = ((int32_t)gMiotyRfCtx.pOutIQBuf[0] * cosine +
                  (int32_t)gMiotyRfCtx.pOutIQBuf[1] * sine) >> 15;
    int32_t im = ((int32_t)gMiotyRfCtx.pOutIQBuf[1] * cosine -
                  (int32_t)gMiotyRfCtx.pOutIQBuf[0] * sine) >> 15;

    gMiotyRfCtx.pOutIQBuf[0] = re;
    gMiotyRfCtx.pOutIQBuf[1] = im;
    gMiotyRfCtx.pOutIQBuf += 2;
  } /* for */
}/* loc_shiftFrequency */
#endif

/*============================================================================*/
/*!
 * @brief Perform downsampling by a factor of 8 using packed samples as
 *         input and unpacked as output.
 *
 *  @param pPackedIq      Array of captured samples in packed format (3B/smpl)
 *  @param samplesCnt     Number of all samples in pPackedIq array
 *  @param pOutSamples    Array filled by this function with downsampled,
 *                        unpacked complex int16 samples
 *  @param outSamplesCnt  Number of samples to write to outSamples array
 */
/*============================================================================*/
#if SF_MIOTY_RADIO_OVERSAMPLINGX8_ENABLED
void loc_downsamplerDiv8(int16_t* pPackedIq, uint32_t samplesCnt,
                         int16_t* pOutSamples, uint32_t outSamplesCnt)
{
  if(((samplesCnt - 107 + 7) >> 3) >= outSamplesCnt)
  {
    for(uint32_t i = 0; i < outSamplesCnt; i++)
    {
      int32_t accRe = 0, accIm = 0;

      for(uint32_t j = 0; j < SF_MIOTY_RADIO_DS8_N_TAPS; j++)
      {
        int32_t re = pDownsamplerDiv8CoeffInv[j] * pPackedIq[2*j+0];
        int32_t im = pDownsamplerDiv8CoeffInv[j] * pPackedIq[2*j+1];

        accRe += (re >> 4);
        accIm += (im >> 4);
      } /* for */

      pOutSamples[0] = accRe >> 16;
      pOutSamples[1] = accIm >> 16;

      pPackedIq += (2*8);
      pOutSamples += 2;
    } /* for */
  } /* if */
}
#endif

/*==============================================================================
                            API FUNCTIONS IMPLEMENTATION
==============================================================================*/
/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_rf_configTx */
/*----------------------------------------------------------------------------*/
bool sf_stack_hal_mioty_rf_configTx(uint16_t centerFreq, uint16_t fractFreq,
                              uint32_t* pOverrides, uint16_t txPower)
{
  /* Return value from rtos related functions. */
  RF_EventMask rfEvent;
  /* Stores local rf params which are used to open an rf handle.  */
  RF_Params rfParams;

  /* Modify frequency specific settings for the next transmission. */
  gRfUl_cmdPropRadioDivSetup.centerFreq = centerFreq;
  gRfUl_cmdPropRadioDivSetup.pRegOverride = pOverrides;

  gRfUl_cmdFS.frequency = centerFreq;
  gRfUl_cmdFS.fractFreq = fractFreq;

  /* Open a rf handle. */
  RF_Params_init(&rfParams);

  /* Set transmit power. */
  gRfUl_cmdPropRadioDivSetup.txPower = txPower;

  if(NULL != gpRfHandle)
  {
    RF_close(gpRfHandle);
    gpRfHandle = NULL;
  }
  gpRfHandle = RF_open(&gRfObject, &gRfProp,
                     (RF_RadioSetup*)&gRfUl_cmdPropRadioDivSetup, &rfParams);
  if (NULL != gpRfHandle)
  {
    rfEvent = RF_runCmd(gpRfHandle, (RF_Op*)&gRfUl_cmdFS, RF_PriorityNormal,
                        NULL, 0);

    if(RF_EventLastCmdDone == rfEvent)
    {
      return true;
    } /* if() */
  }/* if */

  return false;
}/* sf_stack_hal_mioty_rf_configTx() */

/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_rf_configTxData */
/*----------------------------------------------------------------------------*/
bool sf_stack_hal_mioty_rf_configTxData(uint8_t* pPayload, uint8_t length)
{
  /* Local storage used for bit shifting */
  uint32_t dataSyncword;

  /* This driver is currently only supporting mioty uplink messages
     Which have a fixed size of 5 byte.! */
  if(length == 0x05U)
  {
    /* Prepare the payload of the sub packet. We will use a 28 bit syncword and
       and 1 byte payload to transmit our sub packet.
       Calc syncword part. */
    dataSyncword = UINT8_TO_UINT32(pPayload);
    dataSyncword >>= SF_MIOTY_RADIO_HALF_BYTE_IN_BIT;

    /* Calc payload part. */
    gMiotyRfCtx.payloadByte = (pPayload[3] << SF_MIOTY_RADIO_HALF_BYTE_IN_BIT) & 0xF0;
    gMiotyRfCtx.payloadByte |= (pPayload[4] >> SF_MIOTY_RADIO_HALF_BYTE_IN_BIT) & 0x0F;

    /* Configure the tx command to transmit our calculated payload. */
    gRf_cmdPropTx.syncWord = dataSyncword;
    gRf_cmdPropTx.pPkt = &gMiotyRfCtx.payloadByte;
  }
  else
  {
    return false;
  }/* if .. else */

  return true;
}/* sf_stack_hal_mioty_rf_configTxData() */

/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_rf_tx */
/*----------------------------------------------------------------------------*/
bool sf_stack_hal_mioty_rf_tx(void)
{
  RF_EventMask rfEvent;
  bool ret = false;

  rfEvent = RF_runCmd(gpRfHandle, (RF_Op*)&gRf_cmdPropTx, RF_PriorityHighest,
                      NULL, 0 );
  if((rfEvent == RF_EventCmdDone) || (rfEvent == RF_EventLastCmdDone))
  {
    ret = true;
  }/* if */

  /* Clean up. */
  RF_close(gpRfHandle);
  gpRfHandle = NULL;

  return ret;
}/* sf_stack_hal_mioty_rf_tx() */

/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_rf_configRx */
/*----------------------------------------------------------------------------*/
void sf_stack_hal_mioty_rf_configRx(uint16_t freq, uint16_t freqFrac,
                                    int32_t shift, uint16_t samplesToCapture,
                                    int16_t* pOutBuf)
{
  static dataQueue_t dataQueue;
  /* Parameters to initialize RF core. */
  RF_Params rfParams;

  gMiotyRfCtx.samplesToCapture = samplesToCapture;
  gMiotyRfCtx.samplesToSave = samplesToCapture;
  gMiotyRfCtx.pOutIQBuf = pOutBuf;
  gMiotyRfCtx.shift = shift;

  gpRfHandle = NULL;
  memset(&gRfObject, 0, sizeof(RF_Object));

  RF_Params_init(&rfParams);

  gRfDl_cmdPropRadioDivSetup.symbolRate.rateWord = SF_MIOTY_RADIO_RATEWORD;
  gRfDl_cmdPropRadioDivSetup.symbolRate.preScale = SF_MIOTY_RADIO_PRESCALE;
  gRfDl_cmdPropRadioDivSetup.rxBw = SF_MIOTY_RADIO_RXBW;

  /* Update number of samples to capture and the rate-word if oversampling x8
     is enabled*/
#if(SF_MIOTY_RADIO_OVERSAMPLINGX8_ENABLED)
  gMiotyRfCtx.samplesToCapture = (gMiotyRfCtx.samplesToCapture * 8) + 100;
  gRfDl_cmdPropRadioDivSetup.symbolRate.rateWord *= 8;
#endif

  /* Ensure that the previous handle is closed before we open a new one. */
  if(NULL != gpRfHandle)
  {
    RF_close(gpRfHandle);
    gpRfHandle = NULL;
  }/* if */

  gpRfHandle = RF_open(&gRfObject, &gRfDl_prop,
                                 (RF_RadioSetup*)&gRfDl_cmdPropRadioDivSetup,
                                 &rfParams);
  if(NULL != gpRfHandle)
  {
    gRfDl_cmdFs.frequency = freq;
    gRfDl_cmdFs.fractFreq = freqFrac;
    RF_runCmd(gpRfHandle, (RF_Op*)&gRfDl_cmdFs, RF_PriorityNormal, 0, 0);

    /* Only configure the partial read entry in case that a valid pointer was
       provided. */
    if(NULL == pOutBuf)
    {
      /* In case that the rx function is used inside a HW-Test no
         buffer is required. So we leaf this function here. */
      return;
    }/* if */

    for(uint8_t i = 0; i < SF_MIOTY_RADIO_PARTIAL_READ_ENTRY_CNT; i++)
    {
      /* Reset read entries. */
      memset(gMiotyRfCtx.partialReadEntry[i].pBytes, 0, sizeof(rfc_dataEntryPartial_t));

      /* Configure the read entries. */
      gMiotyRfCtx.partialReadEntry[i].pFields->config.type = DATA_ENTRY_TYPE_PARTIAL;
      gMiotyRfCtx.partialReadEntry[i].pFields->status      = SF_MIOTY_RADIO_DATA_ENTRY_DISABLE;
    } /* for */

    gMiotyRfCtx.partialReadEntry[0].pFields->pNextEntry = gMiotyRfCtx.partialReadEntry[1].pBytes;
    gMiotyRfCtx.partialReadEntry[1].pFields->pNextEntry = gMiotyRfCtx.partialReadEntry[2].pBytes;
    gMiotyRfCtx.partialReadEntry[2].pFields->pNextEntry = gMiotyRfCtx.partialReadEntry[1].pBytes;

    gMiotyRfCtx.currentPartialEntry = 0;

    gMiotyRfCtx.partialReadEntry[0].pFields->status = DATA_ENTRY_PENDING;

    if(gMiotyRfCtx.samplesToCapture > SF_MIOTY_RADIO_SAMPLES_INITIAL_ENTRY)
    {
      /* Only +4 seems to fill the entire buffer space. */
      gMiotyRfCtx.partialReadEntry[0].pFields->length = (SF_MIOTY_RADIO_SAMPLES_INITIAL_ENTRY * 3) + 4;
      gMiotyRfCtx.samplesToCapture -= SF_MIOTY_RADIO_SAMPLES_INITIAL_ENTRY;

      if(gMiotyRfCtx.samplesToCapture > SF_MIOTY_RADIO_SAMPLES_PINGPONG_ENTRY)
      {
        /* Only +4 seems to fill the entire buffer space. */
        gMiotyRfCtx.partialReadEntry[1].pFields->length = (SF_MIOTY_RADIO_SAMPLES_PINGPONG_ENTRY * 3) + 4;
        gMiotyRfCtx.partialReadEntry[1].pFields->status = DATA_ENTRY_PENDING;
        gMiotyRfCtx.samplesToCapture -= SF_MIOTY_RADIO_SAMPLES_PINGPONG_ENTRY;
      }
      else if(gMiotyRfCtx.samplesToCapture > 0)
      {
        /* Only +4 seems to fill the entire buffer space. */
        gMiotyRfCtx.partialReadEntry[1].pFields->length = (gMiotyRfCtx.samplesToCapture * 3) + 4;
        gMiotyRfCtx.partialReadEntry[1].pFields->status = DATA_ENTRY_PENDING;
        gMiotyRfCtx.samplesToCapture = 0;
      } /* if .. else */
    }
    else
    {
      /* Only +4 seems to fill the entire buffer space. */
      gMiotyRfCtx.partialReadEntry[0].pFields->length = (gMiotyRfCtx.samplesToCapture * 3) + 4;
      gMiotyRfCtx.samplesToCapture = 0;
    } /* if .. else */

    dataQueue.pCurrEntry = gMiotyRfCtx.partialReadEntry[0].pBytes;
    dataQueue.pLastEntry = NULL;

    /* The RX command is posted here to the RF core, it is processed in the RF core,
      however as triggerType = TRIG_NEVER it will wait for an additional command to
      actually start a reception. */
    gRfDl_cmdPropRx.status = 0;
    gRfDl_cmdPropRx.pQueue = &dataQueue;
    gRfDl_cmdPropRx.startTrigger.triggerType = TRIG_NEVER;
    gRfDl_cmdPropRx.startTrigger.bEnaCmd = 1;
    gMiotyRfCtx.rxCmd = RF_postCmd(gpRfHandle, (RF_Op*)&gRfDl_cmdPropRx,
                                  RF_PriorityNormal, 0, RF_EventRxEntryDone);
  } /* if */
}/* sf_stack_hal_mioty_rf_configRx() */

/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_rf_rx */
/*----------------------------------------------------------------------------*/
void sf_stack_hal_mioty_rf_rx(void)
{
  RF_EventMask result;
  /* Number of sample to be saved. */
  uint16_t samplesSaved = 0;
  /* Number of samples in the current received portion. */
  uint16_t samplesInCurrentPortion = 0;
  /* Indicates if the CPU has finished accessing the entry. */
  bool radioCpuFinished = false;
  /* Entry index. */
  uint8_t schdEntry;
  /* Index of the first sample to be saved. */
  uint16_t firstSampleToSave = (uint16_t)SF_MIOTY_RADIO_FIRST_SAMPLE_TO_SAVE;

  /* Ensure that we only perform the reception in case of a valid handle. */
  if(NULL == gpRfHandle)
  {
    /* Handle invalid states. */
    return;
  }/* if */

  /* Trigger rx start. */
  RF_runDirectCmd(gpRfHandle, 0x04040001);

  do
  {
    /* We pend for a command completion, we repeat it until we get RF_EventLastCmdDone result. */
    result = RF_pendCmd(gpRfHandle, gMiotyRfCtx.rxCmd, RF_EventLastCmdDone |
                        RF_EventRxEntryDone | 0x8000000000000000);

    /* Check if Radio CPU is finished accessing the entry. */
    radioCpuFinished = gMiotyRfCtx.partialReadEntry[gMiotyRfCtx.currentPartialEntry].pFields->status ==
                       DATA_ENTRY_FINISHED   ||
                       gMiotyRfCtx.partialReadEntry[gMiotyRfCtx.currentPartialEntry].pFields->status ==
                       DATA_ENTRY_UNFINISHED;

    if(true == radioCpuFinished)
    {
      if(gMiotyRfCtx.samplesToCapture > 0)
      {
        if(gMiotyRfCtx.currentPartialEntry == 0 || gMiotyRfCtx.currentPartialEntry == 2)
        {
          schdEntry = 2;
        }
        else
        {
          schdEntry = 1;
        }/* if .. else */

        gMiotyRfCtx.partialReadEntry[schdEntry].pFields->status = DATA_ENTRY_PENDING;

        if(gMiotyRfCtx.samplesToCapture > SF_MIOTY_RADIO_SAMPLES_PINGPONG_ENTRY)
        {
          /* Only +4 seems to fill the entire buffer space. */
          gMiotyRfCtx.partialReadEntry[schdEntry].pFields->length = (SF_MIOTY_RADIO_SAMPLES_PINGPONG_ENTRY * 3) + 4;
          gMiotyRfCtx.samplesToCapture -= SF_MIOTY_RADIO_SAMPLES_PINGPONG_ENTRY;
        }
        else
        {
          /* only +4 seems to fill the entire buffer space. */
          gMiotyRfCtx.partialReadEntry[schdEntry].pFields->length = (gMiotyRfCtx.samplesToCapture * 3) + 4;
          gMiotyRfCtx.samplesToCapture = 0;
        }/* if .. else */
      }

      /* Employ oversampling.
         Fraunhofer uses x8-oversampling to improve downlink sensitivity */
#if(SF_MIOTY_RADIO_OVERSAMPLINGX8_ENABLED)
      uint16_t thisIterationOutSamples;

      if(gMiotyRfCtx.currentPartialEntry != 0)
      {
        samplesInCurrentPortion = SF_MIOTY_RADIO_HISTORY_SAMPLES +
          gMiotyRfCtx.partialReadEntry[gMiotyRfCtx.currentPartialEntry].pFields->nextIndex / 3;

        memcpy(gMiotyRfCtx.pUnpackedIqBuf, gMiotyRfCtx.pUnpackedIqBuf +
               SF_MIOTY_RADIO_SAMPLES_PINGPONG_ENTRY * 2,
               SF_MIOTY_RADIO_HISTORY_SAMPLES * 4);
        loc_shiftFrequency(
          &gMiotyRfCtx.partialReadEntry[gMiotyRfCtx.currentPartialEntry].pFields->rxData,
          gMiotyRfCtx.pUnpackedIqBuf + (SF_MIOTY_RADIO_HISTORY_SAMPLES * 2),
          SF_MIOTY_RADIO_SAMPLES_PINGPONG_ENTRY, false);
      }
      else
      {
        samplesInCurrentPortion = SF_MIOTY_RADIO_SAMPLES_INITIAL_ENTRY;
        loc_shiftFrequency(&gMiotyRfCtx.partialReadEntry[0].pFields->rxData,
                           gMiotyRfCtx.pUnpackedIqBuf, samplesInCurrentPortion,
                           true);
      } /* if .. else */

      thisIterationOutSamples = ((samplesInCurrentPortion - 107 + 7) >> 3);

      if(firstSampleToSave >= thisIterationOutSamples)
      {
        firstSampleToSave -= thisIterationOutSamples;
      }
      else
      {
        int16_t* pUnpackedIq = gMiotyRfCtx.pUnpackedIqBuf;
        pUnpackedIq += 2 * firstSampleToSave * 8;
        thisIterationOutSamples -= firstSampleToSave;
        samplesInCurrentPortion -= firstSampleToSave * 8;
        firstSampleToSave = 0;

        loc_downsamplerDiv8(pUnpackedIq, samplesInCurrentPortion,
                         gMiotyRfCtx.pOutIQBuf + (2 * samplesSaved),
                         thisIterationOutSamples);
        samplesSaved += thisIterationOutSamples;
      } /* if .. else */
#else
      /* Packet of IQ data. */
      uint8_t* pPackedIq = NULL;
      pPackedIq = &gMiotyRfCtx.partialReadEntry[gMiotyRfCtx.currentPartialEntry].pFields->rxData;
      samplesInCurrentPortion = gMiotyRfCtx.partialReadEntry[gMiotyRfCtx.currentPartialEntry].pFields->nextIndex / 3;

      if(gMiotyRfCtx.currentPartialEntry == 0)
      {
        if(firstSampleToSave <= samplesInCurrentPortion)
        {
          pPackedIq += 3 * firstSampleToSave;
          samplesInCurrentPortion -= firstSampleToSave;
        }/* if */
      }/* if */

      /* Unpack compressed IQ data in the target buffer. */
      while(samplesInCurrentPortion > 0 && samplesSaved < gMiotyRfCtx.samplesToSave)
      {
        int16_t I = ((pPackedIq[0] << 4) | ( (pPackedIq[1] & 0x000F) << 12 ));
        int16_t Q = ((pPackedIq[2] << 8) | ( (pPackedIq[1] & 0xFFF0)       ));

        gMiotyRfCtx.pOutIQBuf[2*samplesSaved    ] = I >> 4;
        gMiotyRfCtx.pOutIQBuf[2*samplesSaved + 1] = Q >> 4;

        pPackedIq += 3;
        samplesSaved++;
        samplesInCurrentPortion--;
      } /* while */
#endif
      if(gMiotyRfCtx.currentPartialEntry == 0 || gMiotyRfCtx.currentPartialEntry == 2)
      {
        gMiotyRfCtx.currentPartialEntry = 1;
      }
      else
      {
        gMiotyRfCtx.currentPartialEntry = 2;
      }
    }
  } while(!(result & RF_EventLastCmdDone));

  /* IQ data are now copied to application buffer, so we can safely disable radio now
     as this will also disable radio RAM containing received IQ data. */
  RF_close(gpRfHandle);
  gpRfHandle = NULL;
#if(!SF_MIOTY_RADIO_OVERSAMPLINGX8_ENABLED)
  loc_shiftFrequency();
#endif
}/* sf_stack_hal_mioty_rf_rx() */

/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_rf_initRx */
/*----------------------------------------------------------------------------*/
bool sf_stack_hal_mioty_rf_initRx(uint8_t *pBuffer, uint32_t bufferSize)
{
  /* Initialization status */
  bool initStatus = false;
  /* Start address of the free radio RAM. */
  uint16_t radioRamStartOffset = 0U;
  /* Free radio RAM size */
  uint16_t radioRamSize = 0U;
  /* Pin-pong buffer size. */
  uint16_t pingPongEntryBufSize = 0U;
  /* The size of initial entry buffer. */
  uint16_t initialEntryBufSize = 0U;

  if((NULL == pBuffer) || ((SF_MIOTY_RADIO_SAMPLES_INITIAL_ENTRY *
                            SF_MIOTY_RADIO_UNPACKED_SAMPLE_LEN) > bufferSize))
  {
    return false;
  }

  radioRamSize = loc_getRadioMemInfo(&radioRamStartOffset);
  /* Align values to 4B boundary. */
  radioRamStartOffset = SF_MIOTY_RADIO_4BYTE_ALIGN(radioRamStartOffset);
  pingPongEntryBufSize = SF_MIOTY_RADIO_4BYTE_ALIGN(SF_MIOTY_RADIO_PINGPONG_ENTRY_BUF_SIZE);
  initialEntryBufSize = SF_MIOTY_RADIO_4BYTE_ALIGN(SF_MIOTY_RADIO_INITIAL_ENTRY_BUF_SIZE);
  /* Check if the radio free RAM is enough */
  if((radioRamSize - 3) >= (initialEntryBufSize + (2 * pingPongEntryBufSize)))
  {
    gMiotyRfCtx.partialReadEntry[0].pBytes = (uint8_t*)RFC_RAM_BASE +
                                                       radioRamStartOffset;
    gMiotyRfCtx.partialReadEntry[1].pBytes = (uint8_t*)RFC_RAM_BASE +
                                                       radioRamStartOffset +
                                                       initialEntryBufSize;
    gMiotyRfCtx.partialReadEntry[2].pBytes = (uint8_t*)RFC_RAM_BASE +
                                                       radioRamStartOffset +
                                                       initialEntryBufSize +
                                                       pingPongEntryBufSize;
    gMiotyRfCtx.pUnpackedIqBuf = (int16_t*)pBuffer;
    initStatus = true;
  }

  return initStatus;
}/* sf_stack_hal_mioty_rf_initRx() */

/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_rf_txTest */
/*----------------------------------------------------------------------------*/
bool sf_stack_hal_mioty_rf_txTest(bool useCw)
{
  bool ret = false;
  RF_ScheduleCmdParams scheduleParams;

  /* Apply correct modulation. */
  gRfCmdTxTest.config.bUseCw = useCw;

  if(NULL != gpRfHandle)
  {
    /* Send Tx-test command */
    RF_ScheduleCmdParams_init(&scheduleParams);
    gMiotyRfCtx.rfCmdHandleTest = RF_scheduleCmd(gpRfHandle,
                                                 (RF_Op*)&gRfCmdTxTest,
                                                 &scheduleParams, NULL, 0);
    if(gMiotyRfCtx.rfCmdHandleTest >= 0)
    {
      ret = true;
    }/* if */
  }/* if */

  return ret;
}/* sf_stack_hal_mioty_rf_txTest() */

/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_rf_rxTest */
/*----------------------------------------------------------------------------*/
bool sf_stack_hal_mioty_rf_rxTest(void)
{
  bool ret = false;
  RF_ScheduleCmdParams scheduleParams;

  if(NULL != gpRfHandle)
  {
    /* Send Tx-test command */
    RF_ScheduleCmdParams_init(&scheduleParams);
    gMiotyRfCtx.rfCmdHandleTest = RF_scheduleCmd(gpRfHandle,
                                                   (RF_Op*)&gRfCmdRxTest,
                                                   &scheduleParams, NULL, 0);
    if(gMiotyRfCtx.rfCmdHandleTest >= 0)
    {
      ret = true;
    }/* if */
  }/* if */

  return ret;
}/* sf_stack_hal_mioty_rf_rxTest() */

/*----------------------------------------------------------------------------*/
/*! sf_stack_hal_mioty_rf_deInit */
/*----------------------------------------------------------------------------*/
bool sf_stack_hal_mioty_rf_deInit(void)
{
  if(NULL != gpRfHandle)
  {

    /* Cancel previous command. */
    if( gMiotyRfCtx.rfCmdHandleTest > 0 )
    {
      RF_cancelCmd( gpRfHandle, gMiotyRfCtx.rfCmdHandleTest, 0 );
      gMiotyRfCtx.rfCmdHandleTest = -5;
    }/* if */

    RF_close(gpRfHandle);
    gpRfHandle = NULL;
  }/* if */

  return true;
}/* sf_stack_hal_mioty_rf_deInit() */

#ifdef __cplusplus
}
#endif
