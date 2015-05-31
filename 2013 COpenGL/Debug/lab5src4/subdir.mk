################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab5src4/Lab5C4.c 

LAB54OBJS += \
./lab5src4/Lab5C4.o 

OBJS += \
./lab5src4/Lab5C4.o 

C_DEPS += \
./lab5src4/Lab5C4.d 


# Each subdirectory must supply rules for building sources it contributes
lab5src4/%.o: ../lab5src4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


