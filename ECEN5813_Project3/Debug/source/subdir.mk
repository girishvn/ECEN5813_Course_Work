################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/GPIO.c \
../source/Homework_4.c \
../source/circbuf.c \
../source/conversion.c \
../source/main.c \
../source/project2.c \
../source/project3.c \
../source/uart.c 

OBJS += \
./source/GPIO.o \
./source/Homework_4.o \
./source/circbuf.o \
./source/conversion.o \
./source/main.o \
./source/project2.o \
./source/project3.o \
./source/uart.o 

C_DEPS += \
./source/GPIO.d \
./source/Homework_4.d \
./source/circbuf.d \
./source/conversion.d \
./source/main.d \
./source/project2.d \
./source/project3.d \
./source/uart.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DCPU_MKL25Z128VFM4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCPU_MKL25Z128VFM4_cm0plus -I../CMSIS -I../board -I../drivers -I../utilities -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


