################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab2src/Lab2C.c 

LAB2OBJS += \
./lab2src/Lab2C.o 

OBJS += \
./lab2src/Lab2C.o 

C_DEPS += \
./lab2src/Lab2C.d 


# Each subdirectory must supply rules for building sources it contributes
lab2src/%.o: ../lab2src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


