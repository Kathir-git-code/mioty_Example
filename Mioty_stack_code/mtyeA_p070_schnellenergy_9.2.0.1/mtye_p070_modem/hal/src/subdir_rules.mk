################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
hal/src/%.obj: ../hal/src/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O0 --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/apps" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/apps/app_commons" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/apps/app_commons/driver" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/apps/app_commons/hal" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/apps/app_mioty" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/hal" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/hal/inc" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/hal/src" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/stack/inc" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/stack/lib" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/mtye_p070_modem" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --include_path="C:/ti/simplelink_cc13xx_cc26xx_sdk_5_30_01_01/source/ti/posix/ccs" --include_path="C:/ti/simplelink_cc13xx_cc26xx_sdk_5_30_01_01/source/ti/devices/cc13x2_cc26x2/" --preinclude="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/apps/app_commons/driver/target_config.h" --define=UART_ENABLED=1 -g --c99 --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="hal/src/$(basename $(<F)).d_raw" --include_path="D:/Development/workfolder/Mioty_statck_code/mtyeA_p070_schnellenergy_9.2.0.1/mtye_p070_modem/syscfg" --obj_directory="hal/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


