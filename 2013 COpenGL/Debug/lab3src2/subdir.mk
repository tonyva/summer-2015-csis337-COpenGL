################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab3src2/Lab3C02.c 

LAB32OBJS += \
./lab3src2/Lab3C02.o 

OBJS += \
./lab3src2/Lab3C02.o 

C_DEPS += \
./lab3src2/Lab3C02.d 


# Each subdirectory must supply rules for building sources it contributes
lab3src2/%.o: ../lab3src2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


