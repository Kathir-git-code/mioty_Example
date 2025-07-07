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
 @brief      Register settings required for the mioty protocol.

*/
/*=============================================================================
                                INCLDUES
=============================================================================*/

#include "sf_cc13xx_miotyRegisters.h"

#include DeviceFamily_constructPath(rf_patches/rf_patch_mce_iqdump.h)

/*=============================================================================
                                GLOBAL VARIABLES
=============================================================================*/
RF_Mode gRfProp =
{
  .rfMode      = RF_MODE_MULTIPLE,
  .cpePatchFxn = NULL,
  .mcePatchFxn = NULL,
  .rfePatchFxn = NULL,
};

rfc_CMD_PROP_RADIO_DIV_SETUP_t gRfUl_cmdPropRadioDivSetup =
{
  .commandNo                  = 0x3807,
  .status                     = 0x0000,
  .pNextOp                    = 0,
  .startTime                  = 0x00000000,
  .startTrigger.triggerType   = 0x0,
  .startTrigger.bEnaCmd       = 0x0,
  .startTrigger.triggerNo     = 0x0,
  .startTrigger.pastTrig      = 0x0,
  .condition.rule             = 0x1,
  .condition.nSkip            = 0x0,
  .modulation.modType         = 0x1,
  .modulation.deviation       = 0x02,
  .symbolRate.preScale        = 0xF,
  .symbolRate.rateWord        = 0x0618,
  .rxBw                       = 0x27,
  .preamConf.nPreamBytes      = 0x0, //1bit preamble
  .preamConf.preamMode        = 0x0,
  .formatConf.nSwBits         = 0x1C,//28 bit syncword
  .formatConf.bBitReversal    = 0x0,
  .formatConf.bMsbFirst       = 0x1,
  .formatConf.fecMode         = 0x0,
  .formatConf.whitenMode      = 0x0,
  .config.frontEndMode        = 0x0,
  .config.biasMode            = 0x0,
  .config.analogCfgMode       = 0x0,
  .config.bNoFsPowerUp        = 0x0,
  .txPower                    = 0x10C8,
  .pRegOverride               = 0,
  .centerFreq                 = 0x0364,
  .intFreq                    = 0x0000,
  .loDivider                  = 0x05,
};

rfc_CMD_FS_t gRfUl_cmdFS =
{
  .commandNo = 0x0803,
  .status = 0x0000,
  .pNextOp = 0,
  .startTime = 0x00000000,
  .startTrigger.triggerType = 0x0,
  .startTrigger.bEnaCmd = 0x0,
  .startTrigger.triggerNo = 0x0,
  .startTrigger.pastTrig = 0x0,
  .condition.rule = 0x1,
  .condition.nSkip = 0x0,
  .frequency = 0x0364,
  .fractFreq = 0xF333,
  .synthConf.bTxMode = 0x1,
  .synthConf.refFreq = 0x0,
  .__dummy0 = 0x00,
  .__dummy1 = 0x00,
  .__dummy2 = 0x00,
  .__dummy3 = 0x0000,
};

rfc_CMD_PROP_TX_ADV_t gRf_cmdPropTx =
{
  .commandNo = 0x3803,
  .status = 0x0000,
  .pNextOp = 0,
  .startTime = 0x00000000,
  .startTrigger.triggerType = TRIG_NOW,
  .startTrigger.bEnaCmd = 0x0,
  .startTrigger.triggerNo = 0x0,
  .startTrigger.pastTrig = 0x1,
  .condition.rule = 0x1,
  .condition.nSkip = 0x0,
  .pktConf.bFsOff = 0x0,
  .pktConf.bUseCrc = 0x0,
  .pktConf.bCrcIncSw = 0x0,
  .pktConf.bCrcIncHdr = 0x0,
  .numHdrBits = 0x0,
  .pktLen = 0x01,// We transmit 1 byte payload and 28 bit syncword
  .startConf.bExtTxTrig = 0x0,
  .startConf.inputMode = 0x0,
  .startConf.source = 0x0,
  .preTrigger.triggerType = TRIG_NOW,
  .preTrigger.bEnaCmd = 0x0,
  .preTrigger.triggerNo = 0x0,
  .preTrigger.pastTrig = 0x1,
  .preTime = 0x0,
  .syncWord = 0x00000000,
  .pPkt = 0,
};

uint32_t rfDl_propRadioDivSetup_overrides[] = {
    MCE_RFE_OVERRIDE(1, 0, 2, 0, 4, 0),     // MCE run from Patch
    HW32_ARRAY_OVERRIDE(0x405C, 1),         // Sets RF_FSCA.ANADIV.DIV_SEL_BIAS = 1. Bits [0:16, 24, 30] are don't care. Set elsewhere
    (uint32_t)  0x8141131,
    (uint32_t)  0x00F788D3,                 // Setting IPEAK = 7 and DCDC dither off for TX
    (uint32_t)  0x00058683,                 // increase mid code calibration time from 1us to 5us.
    HW32_ARRAY_OVERRIDE(0x4004, 1),         // increase mid code calibration time from 1us to 5us.
    (uint32_t)  0x38183C30,                 // increase mid code calibration time from 1us to 5us.
    HW_REG_OVERRIDE(0x609C, 0x001A),        // RFE.SPARE1 AGC reference level [dB]
    (uint32_t)  0x000188A3,                 // RSSI offset of -1 dB at 779-930 MHz
    ADI_HALFREG_OVERRIDE(0, 61, 0xF,0x8),   // ADI_0_RF:IFAMPCTL3.AAF_CAP_EN = 0x8 (bit 7:4)
    (uint32_t)  0xFFFFFFFF,
};

rfc_CMD_PROP_RADIO_DIV_SETUP_t gRfDl_cmdPropRadioDivSetup = {
    .commandNo                  = 0x3807,
    .status                     = 0x0000,
    .pNextOp                    = 0,
    .startTime                  = 0x00000000,
    .startTrigger.triggerType   = 0x0,
    .startTrigger.bEnaCmd       = 0x0,
    .startTrigger.triggerNo     = 0x0,
    .startTrigger.pastTrig      = 0x0,
    .condition.rule             = 0x1,
    .condition.nSkip            = 0x0,
    .modulation.modType         = 0x1,
    .modulation.deviation       = 0x19,
    .rxBw                       = 0x20,
    .symbolRate.preScale        = 0x4,
    .symbolRate.rateWord        = 0x600, //35156,25Hz
    .preamConf.nPreamBytes      = 0x4,
    .preamConf.preamMode        = 0x0,
    .formatConf.nSwBits         = 0x20,
    .formatConf.bBitReversal    = 0x0,
    .formatConf.bMsbFirst       = 0x0,
    .formatConf.fecMode         = 0x0,
    .formatConf.whitenMode      = 0x0,
    .config.frontEndMode        = 0x0,
    .config.biasMode            = 0x1,
    .config.bNoFsPowerUp        = 0x0,
    .txPower                    = 0xa73f,
    .pRegOverride               = rfDl_propRadioDivSetup_overrides,
    .centerFreq                 = 0x0364,
    .intFreq                    = 0x8000,
    .loDivider                  = 0x05,
};

rfc_CMD_FS_t gRfDl_cmdFs = {
    .commandNo                  = 0x0803,
    .status                     = 0x0000,
    .pNextOp                    = 0,
    .startTime                  = 0x00000000,
    .startTrigger.triggerType   = 0x0,
    .startTrigger.bEnaCmd       = 0x0,
    .startTrigger.triggerNo     = 0x0,
    .startTrigger.pastTrig      = 0x0,
    .condition.rule             = 0x1,
    .condition.nSkip            = 0x0,
    .frequency                  = 0x0365,
    .fractFreq                  = 0x8666,
    .synthConf.bTxMode          = 0x0,
    .synthConf.refFreq          = 0x0,
    .__dummy0                   = 0x00,
    .__dummy1                   = 0x00,
    .__dummy2                   = 0x00,
    .__dummy3                   = 0x0000,
};

rfc_CMD_PROP_RX_t gRfDl_cmdPropRx = {
    .commandNo                  = 0x3802,
    .status                     = 0x0000,
    .pNextOp                    = 0,
    .startTime                  = 0x00000000,
    .startTrigger.triggerType   = 0x0,
    .startTrigger.bEnaCmd       = 0x0,
    .startTrigger.triggerNo     = 0x0,
    .startTrigger.pastTrig      = 0x0,
    .condition.rule             = 0x1,
    .condition.nSkip            = 0x0,
    .pktConf.bFsOff             = 0x0,
    .pktConf.bRepeatOk          = 0x0,
    .pktConf.bRepeatNok         = 0x0,
    .pktConf.bUseCrc            = 0x0,
    .pktConf.bVarLen            = 0x0,
    .pktConf.bChkAddress        = 0x0,
    .pktConf.endType            = 0x0,
    .pktConf.filterOp           = 0x0,
    .rxConf.bAutoFlushIgnored   = 0x0,
    .rxConf.bAutoFlushCrcErr    = 0x0,
    .rxConf.bIncludeHdr         = 0x0,
    .rxConf.bIncludeCrc         = 0x0,
    .rxConf.bAppendRssi         = 0x0,
    .rxConf.bAppendTimestamp    = 0x0,
    .rxConf.bAppendStatus       = 0x0,
    .syncWord                   = 0x930b51de,
    .maxPktLen                  = 0,
    .address0                   = 0xaa,
    .address1                   = 0xbb,
    .endTrigger.triggerType     = 0x1,
    .endTrigger.bEnaCmd         = 0x0,
    .endTrigger.triggerNo       = 0x0,
    .endTrigger.pastTrig        = 0x0,
    .endTime                    = 0x00000000,
    .pQueue                     = 0,
    .pOutput                    = 0,
};

RF_Mode gRfDl_prop = {
    .rfMode      = RF_MODE_MULTIPLE,
    .cpePatchFxn = 0,
    .mcePatchFxn = rf_patch_mce_iqdump,
    .rfePatchFxn = 0,
};

#ifdef __cplusplus
}
#endif
