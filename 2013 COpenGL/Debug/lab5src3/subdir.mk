################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab5src3/Lab5C3.c 

LAB53OBJS += \
./lab5src3/Lab5C3.o 

OBJS += \
./lab5src3/Lab5C3.o 

C_DEPS += \
./lab5src3/Lab5C3.d 


# Each subdirectory must supply rules for building sources it contributes
lab5src3/%.o: ../lab5src3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


