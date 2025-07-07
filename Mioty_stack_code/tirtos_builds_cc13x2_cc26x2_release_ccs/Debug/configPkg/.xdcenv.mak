#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/simplelink_cc13xx_cc26xx_sdk_5_30_01_01/source;C:/ti/simplelink_cc13xx_cc26xx_sdk_5_30_01_01/kernel/tirtos/packages
override XDCROOT = C:/ti/ccs1260/xdctools_3_62_01_16_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/simplelink_cc13xx_cc26xx_sdk_5_30_01_01/source;C:/ti/simplelink_cc13xx_cc26xx_sdk_5_30_01_01/kernel/tirtos/packages;C:/ti/ccs1260/xdctools_3_62_01_16_core/packages;..
HOSTOS = Windows
endif
