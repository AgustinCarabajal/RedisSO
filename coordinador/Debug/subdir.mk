################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cliente.c \
../coordinador.c \
../main_coordinador.c \
../serializacion.c \
../algoritmos.c \
../servidor.c 

OBJS += \
./cliente.o \
./coordinador.o \
./main_coordinador.o \
./serializacion.o \
./algoritmos.o\
./servidor.o 

C_DEPS += \
./cliente.d \
./coordinador.d \
./main_coordinador.d \
./serializacion.d \
./algoritmos.d\
./servidor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


