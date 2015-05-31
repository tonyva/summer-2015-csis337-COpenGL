################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab3src1/Lab3C01.c 

LAB31OBJS += \
./lab3src1/Lab3C01.o 

OBJS += \
./lab3src1/Lab3C01.o 

C_DEPS += \
./lab3src1/Lab3C01.d 


# Each subdirectory must supply rules for building sources it contributes
lab3src1/%.o: ../lab3src1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


