################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm.c \
../Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Atom.c \
../Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Cmu.c \
../Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Dpll.c \
../Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Dtm.c \
../Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Spe.c \
../Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Tbu.c \
../Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Tim.c \
../Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Tom.c 

OBJS += \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm.o \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Atom.o \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Cmu.o \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Dpll.o \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Dtm.o \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Spe.o \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Tbu.o \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Tim.o \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Tom.o 

COMPILED_SRCS += \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm.src \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Atom.src \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Cmu.src \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Dpll.src \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Dtm.src \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Spe.src \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Tbu.src \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Tim.src \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Tom.src 

C_DEPS += \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm.d \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Atom.d \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Cmu.d \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Dpll.d \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Dtm.d \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Spe.d \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Tbu.d \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Tim.d \
./Libraries/iLLD/TC33A/Tricore/Gtm/Std/IfxGtm_Tom.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC33A/Tricore/Gtm/Std/%.src: ../Libraries/iLLD/TC33A/Tricore/Gtm/Std/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc33x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC334 Lite Kit/ASB_SimpleAudioLoopback_TC334/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc33x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/iLLD/TC33A/Tricore/Gtm/Std/%.o: ./Libraries/iLLD/TC33A/Tricore/Gtm/Std/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


