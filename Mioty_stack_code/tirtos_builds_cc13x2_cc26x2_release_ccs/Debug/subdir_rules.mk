################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1745043089:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1745043089-inproc

build-1745043089-inproc: ../release.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/ccs1260/xdctools_3_62_01_16_core/xs" --xdcpath="C:/ti/simplelink_cc13xx_cc26xx_sdk_5_30_01_01/source;C:/ti/simplelink_cc13xx_cc26xx_sdk_5_30_01_01/kernel/tirtos/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.simplelink:CC13X2_CC26X2 -r release -c "C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS" --compileOptions " -DDeviceFamily_CC13X2_CC26X2 " "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-1745043089 ../release.cfg
configPkg/compiler.opt: build-1745043089
configPkg: build-1745043089


