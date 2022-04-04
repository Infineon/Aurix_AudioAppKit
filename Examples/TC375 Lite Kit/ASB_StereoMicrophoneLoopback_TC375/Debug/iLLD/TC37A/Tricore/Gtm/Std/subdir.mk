################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../iLLD/TC37A/Tricore/Gtm/Std/IfxGtm.c \
../iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Atom.c \
../iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Cmu.c \
../iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Dpll.c \
../iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Dtm.c \
../iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Psm.c \
../iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Spe.c \
../iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Tbu.c \
../iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Tim.c \
../iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Tom.c 

OBJS += \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm.o \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Atom.o \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Cmu.o \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Dpll.o \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Dtm.o \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Psm.o \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Spe.o \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Tbu.o \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Tim.o \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Tom.o 

COMPILED_SRCS += \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm.src \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Atom.src \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Cmu.src \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Dpll.src \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Dtm.src \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Psm.src \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Spe.src \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Tbu.src \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Tim.src \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Tom.src 

C_DEPS += \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm.d \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Atom.d \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Cmu.d \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Dpll.d \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Dtm.d \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Psm.d \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Spe.d \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Tbu.d \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Tim.d \
./iLLD/TC37A/Tricore/Gtm/Std/IfxGtm_Tom.d 


# Each subdirectory must supply rules for building sources it contributes
iLLD/TC37A/Tricore/Gtm/Std/%.src: ../iLLD/TC37A/Tricore/Gtm/Std/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC375 Lite Kit/ASB_StereoMicrophoneLoopback/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O3 --tradeoff=0 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

iLLD/TC37A/Tricore/Gtm/Std/%.o: ./iLLD/TC37A/Tricore/Gtm/Std/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


