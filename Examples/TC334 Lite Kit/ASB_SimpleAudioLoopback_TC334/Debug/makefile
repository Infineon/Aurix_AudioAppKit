################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Libraries/iLLD/TC33A/Tricore/_PinMap/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/_Lib/DataHandling/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/_Impl/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Stm/Timer/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Stm/Std/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Src/Std/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Scu/Std/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Port/Std/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Pms/Std/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Mtu/Std/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Gtm/Std/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Cpu/Trap/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Cpu/Std/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Cpu/Irq/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Asclin/Std/subdir.mk
-include Libraries/iLLD/TC33A/Tricore/Asclin/Asc/subdir.mk
-include Libraries/UART/subdir.mk
-include Libraries/Service/CpuGeneric/StdIf/subdir.mk
-include Libraries/Infra/Ssw/TC33A/Tricore/subdir.mk
-include Libraries/Infra/Platform/Tricore/Compilers/subdir.mk
-include Libraries/I2C/subdir.mk
-include Libraries/FreeRTOS/portable/TriCore/subdir.mk
-include Libraries/FreeRTOS/portable/MemMang/subdir.mk
-include Libraries/FreeRTOS/subdir.mk
-include Libraries/AudioShield/subdir.mk
-include Configurations/Debug/subdir.mk
-include Configurations/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_SIZE += \
ASB_SimpleAudioLoopback_TC334.siz \


# All Target
all: ASB_SimpleAudioLoopback_TC334.elf secondary-outputs

# Tool invocations
ASB_SimpleAudioLoopback_TC334.elf: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: TASKING Linker'
	cctc -lrt -lfp_fpu -lcs_fpu  -Wl-Oc -Wl-OL -Wl-Ot -Wl-Ox -Wl-Oy -Wl--map-file="ASB_SimpleAudioLoopback_TC334.map" -Wl-mc -Wl-mf -Wl-mi -Wl-mk -Wl-ml -Wl-mm -Wl-md -Wl-mr -Wl-mu --no-warnings= -Wl--error-limit=42 --exceptions --strict --anachronisms --force-c++ -Ctc33x   -o"ASB_SimpleAudioLoopback_TC334.elf" -Wl-o"ASB_SimpleAudioLoopback_TC334.hex:IHEX" --lsl-core=vtc  --lsl-file=../Lcf_Tasking_Tricore_Tc.lsl $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

ASB_SimpleAudioLoopback_TC334.siz: ASB_SimpleAudioLoopback_TC334.elf
	@echo 'Invoking: Print Size'
	elfsize  "ASB_SimpleAudioLoopback_TC334.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	find . ! -name "*.mk" ! -name "makefile" ! -name "." -type f -delete 
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
