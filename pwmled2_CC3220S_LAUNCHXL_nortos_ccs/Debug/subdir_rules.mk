################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/sstut/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/sstut/workspace_v12/pwmled2_CC3220S_LAUNCHXL_nortos_ccs" --include_path="C:/Users/sstut/workspace_v12/pwmled2_CC3220S_LAUNCHXL_nortos_ccs/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_4_30_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_4_30_00_06/kernel/nortos" --include_path="C:/ti/simplelink_cc32xx_sdk_4_30_00_06/kernel/nortos/posix" --include_path="C:/Users/sstut/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/sstut/workspace_v12/pwmled2_CC3220S_LAUNCHXL_nortos_ccs/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-642115183: ../pwmled2.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1_12_0/sysconfig_cli.bat" --script "C:/Users/sstut/workspace_v12/pwmled2_CC3220S_LAUNCHXL_nortos_ccs/pwmled2.syscfg" -o "syscfg" -s "C:/ti/simplelink_cc32xx_sdk_4_30_00_06/.metadata/product.json" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-642115183 ../pwmled2.syscfg
syscfg/ti_drivers_config.h: build-642115183
syscfg/ti_utils_build_linker.cmd.genlibs: build-642115183
syscfg/syscfg_c.rov.xs: build-642115183
syscfg/ti_utils_runtime_model.gv: build-642115183
syscfg/ti_utils_runtime_Makefile: build-642115183
syscfg: build-642115183

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/sstut/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/sstut/workspace_v12/pwmled2_CC3220S_LAUNCHXL_nortos_ccs" --include_path="C:/Users/sstut/workspace_v12/pwmled2_CC3220S_LAUNCHXL_nortos_ccs/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_4_30_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_4_30_00_06/kernel/nortos" --include_path="C:/ti/simplelink_cc32xx_sdk_4_30_00_06/kernel/nortos/posix" --include_path="C:/Users/sstut/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/sstut/workspace_v12/pwmled2_CC3220S_LAUNCHXL_nortos_ccs/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


