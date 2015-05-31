################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab5src6/Lab5C6.c 

LAB56OBJS += \
./lab5src6/Lab5C6.o 

OBJS += \
./lab5src6/Lab5C6.o 

C_DEPS += \
./lab5src6/Lab5C6.d 


# Each subdirectory must supply rules for building sources it contributes
lab5src6/%.o: ../lab5src6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


