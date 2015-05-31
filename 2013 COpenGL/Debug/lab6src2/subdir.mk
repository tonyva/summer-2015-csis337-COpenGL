################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab6src2/Lab6C2.c 

LAB62OBJS += \
./lab6src2/Lab6C2.o 

OBJS += \
./lab6src2/Lab6C2.o 

C_DEPS += \
./lab6src2/Lab6C2.d 


# Each subdirectory must supply rules for building sources it contributes
lab6src2/%.o: ../lab6src2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


