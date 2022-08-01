################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
drivers_MSP/%.obj: ../drivers_MSP/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=16 --include_path="C:/ti/ccs1200/ccs/ccs_base/msp430/include" --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --advice:power=all -g --define=__MSP430F2618__ --display_error_number --diag_warning=225 --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="drivers_MSP/$(basename $(<F)).d_raw" --obj_directory="drivers_MSP" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


