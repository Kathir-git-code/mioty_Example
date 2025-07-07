################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-2045854031: ../cc13x2.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1260/ccs/utils/sysconfig_1.19.0/sysconfig_cli.bat" --script "D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/cc13x2.syscfg" -o "syscfg" -s "C:/ti/simplelink_cc13xx_cc26xx_sdk_5_30_01_01/.metadata/product.json" -s "C:/ti/simplelink_cc13xx_cc26xx_sdk_5_30_01_01/.metadata/product.json" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_devices_config.c: build-2045854031 ../cc13x2.syscfg
syscfg/ti_drivers_config.c: build-2045854031
syscfg/ti_drivers_config.h: build-2045854031
syscfg/ti_utils_build_linker.cmd.genlibs: build-2045854031
syscfg/syscfg_c.rov.xs: build-2045854031
syscfg/ti_utils_runtime_model.gv: build-2045854031
syscfg/ti_utils_runtime_Makefile: build-2045854031
syscfg: build-2045854031

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O0 --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/apps" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/apps/app_commons" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/apps/app_commons/driver" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/apps/app_commons/hal" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/apps/app_mioty" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/hal" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/hal/inc" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/hal/src" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/stack/inc" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/stack/lib" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/mtye_p070_modem" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --include_path="C:/ti/simplelink_cc13xx_cc26xx_sdk_5_30_01_01/source/ti/posix/ccs" --include_path="C:/ti/simplelink_cc13xx_cc26xx_sdk_5_30_01_01/source/ti/devices/cc13x2_cc26x2/" --preinclude="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/apps/app_commons/driver/target_config.h" --define=UART_ENABLED=1 -g --c99 --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/mtye_p070_modem/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


