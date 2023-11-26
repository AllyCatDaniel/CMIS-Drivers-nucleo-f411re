################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/FPU.c \
../Src/adc.c \
../Src/bsp.c \
../Src/circular_buffer.c \
../Src/dfplayer_lib.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/timebase.c \
../Src/uart.c 

OBJS += \
./Src/FPU.o \
./Src/adc.o \
./Src/bsp.o \
./Src/circular_buffer.o \
./Src/dfplayer_lib.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/timebase.o \
./Src/uart.o 

C_DEPS += \
./Src/FPU.d \
./Src/adc.d \
./Src/bsp.d \
./Src/circular_buffer.d \
./Src/dfplayer_lib.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/timebase.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"C:/Users/Dan's Computer/STM32CubeIDE/Sound/TEST1/chip headers/CMSIS/Include" -I"C:/Users/Dan's Computer/STM32CubeIDE/Sound/TEST1/chip headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Dan's Computer/STM32CubeIDE/Sound4/Src" -I"C:/Users/Dan's Computer/STM32CubeIDE/Sound/TEST6/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/FPU.cyclo ./Src/FPU.d ./Src/FPU.o ./Src/FPU.su ./Src/adc.cyclo ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/bsp.cyclo ./Src/bsp.d ./Src/bsp.o ./Src/bsp.su ./Src/circular_buffer.cyclo ./Src/circular_buffer.d ./Src/circular_buffer.o ./Src/circular_buffer.su ./Src/dfplayer_lib.cyclo ./Src/dfplayer_lib.d ./Src/dfplayer_lib.o ./Src/dfplayer_lib.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timebase.cyclo ./Src/timebase.d ./Src/timebase.o ./Src/timebase.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src

