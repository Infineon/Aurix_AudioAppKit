################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.c \
../Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.c \
../Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc1.c \
../Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc2.c 

OBJS += \
./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.o \
./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.o \
./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc1.o \
./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc2.o 

COMPILED_SRCS += \
./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.src \
./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.src \
./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc1.src \
./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc2.src 

C_DEPS += \
./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.d \
./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.d \
./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc1.d \
./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc2.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Infra/Ssw/TC37A/Tricore/%.src: ../Libraries/Infra/Ssw/TC37A/Tricore/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC375 Lite Kit/MAB_ArrayMicrophoneLoopback_TC375/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/Infra/Ssw/TC37A/Tricore/%.o: ./Libraries/Infra/Ssw/TC37A/Tricore/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


