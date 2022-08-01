################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./ISR.obj" \
"./config.obj" \
"./main.obj" \
"./drivers_MSP/fletcher16.obj" \
"./drivers_MSP/rbuffer.obj" \
"./drivers_MSP/timer_a.obj" \
"./drivers_MSP/uart_baudrate.obj" \
"./drivers_MSP/usci_a_spi.obj" \
"./drivers_MSP/usci_a_uart.obj" \
"./drivers_MSP/usci_b_i2c.obj" \
"./drivers_MSP/wdt_a.obj" \
"../lnk_msp430f2618.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include drivers_MSP/subdir_vars.mk
-include subdir_rules.mk
-include drivers_MSP/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
WalkieTalkie.out \

EXE_OUTPUTS__QUOTED += \
"WalkieTalkie.out" \

BIN_OUTPUTS += \
WalkieTalkie.hex \

BIN_OUTPUTS__QUOTED += \
"WalkieTalkie.hex" \


# All Target
all: WalkieTalkie.out

# Tool invocations
WalkieTalkie.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=16 --advice:power=all -g --define=__MSP430F2618__ --display_error_number --diag_warning=225 --diag_wrap=off --printf_support=minimal -z -m"WalkieTalkie.map" --stack_size=80 --heap_size=80 --cinit_hold_wdt=on -i"C:/ti/ccs1200/ccs/ccs_base/msp430/include" -i"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/lib" -i"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --reread_libs --warn_sections --diag_wrap=off --display_error_number --xml_link_info="WalkieTalkie_linkInfo.xml" --use_hw_mpy=16 --rom_model -o "WalkieTalkie.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

WalkieTalkie.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/hex430" --memwidth=8 --romwidth=8 --diag_wrap=off -o "WalkieTalkie.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "ISR.obj" "config.obj" "main.obj" "drivers_MSP\fletcher16.obj" "drivers_MSP\rbuffer.obj" "drivers_MSP\timer_a.obj" "drivers_MSP\uart_baudrate.obj" "drivers_MSP\usci_a_spi.obj" "drivers_MSP\usci_a_uart.obj" "drivers_MSP\usci_b_i2c.obj" "drivers_MSP\wdt_a.obj" 
	-$(RM) "ISR.d" "config.d" "main.d" "drivers_MSP\fletcher16.d" "drivers_MSP\rbuffer.d" "drivers_MSP\timer_a.d" "drivers_MSP\uart_baudrate.d" "drivers_MSP\usci_a_spi.d" "drivers_MSP\usci_a_uart.d" "drivers_MSP\usci_b_i2c.d" "drivers_MSP\wdt_a.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

