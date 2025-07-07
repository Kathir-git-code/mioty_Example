#ifndef __SF_CC13XX_MIOTY_REGISTERS__
#define __SF_CC13XX_MIOTY_REGISTERS__


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
 @brief      This header contains rf settings which are used for mioty
             transmissions.
*/

/*==============================================================================
                             INCLUDES
==============================================================================*/
#include <ti/drivers/rf/RF.h>

#if( SF_CC13XX_TARGET == SF_TARGET_CC13X0_LP )
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(rf_patches/rf_patch_mce_iqdump.h)
#include DeviceFamily_constructPath(rf_patches/rf_patch_cpe_genfsk.h)
#include DeviceFamily_constructPath(rf_patches/rf_patch_rfe_genfsk.h)
#endif

/*==============================================================================
                         EXTERN VARIABLES
==============================================================================*/
/*  RF Core API commands */
extern rfc_CMD_PROP_RADIO_DIV_SETUP_t gRfUl_cmdPropRadioDivSetup;
/* TI-RTOS RF Mode Object */
extern rfc_CMD_FS_t gRfUl_cmdFS;
extern rfc_CMD_PROP_TX_ADV_t gRf_cmdPropTx;
/* RF Mode settings */
extern RF_Mode gRfProp;

/* RF Core API commands */
extern rfc_CMD_PROP_RADIO_DIV_SETUP_t gRfDl_cmdPropRadioDivSetup;
extern rfc_CMD_FS_t gRfDl_cmdFs;
extern rfc_CMD_PROP_RX_t gRfDl_cmdPropRx;
/* overrides */
extern uint32_t gRfDl_propRadioDivSetup_overrides[32];
/* TI-RTOS RF Mode Object */
extern RF_Mode gRfDl_prop;

#endif /* __SF_CC13XX_MIOTY_REGISTERS__*/
