################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab5src2/Lab5C2.c 

LAB52OBJS += \
./lab5src2/Lab5C2.o 

OBJS += \
./lab5src2/Lab5C2.o 

C_DEPS += \
./lab5src2/Lab5C2.d 


# Each subdirectory must supply rules for building sources it contributes
lab5src2/%.o: ../lab5src2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


