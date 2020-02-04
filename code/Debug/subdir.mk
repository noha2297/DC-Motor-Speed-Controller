################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../External-Interrupt.c \
../adc.c \
../interrupt.c \
../lcd.c \
../project2.c \
../timer.c 

OBJS += \
./External-Interrupt.o \
./adc.o \
./interrupt.o \
./lcd.o \
./project2.o \
./timer.o 

C_DEPS += \
./External-Interrupt.d \
./adc.d \
./interrupt.d \
./lcd.d \
./project2.d \
./timer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


