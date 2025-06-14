################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/balance.cpp \
../Core/Src/battery_check.cpp \
../Core/Src/bluetooth.cpp \
../Core/Src/command_parser.cpp \
../Core/Src/fsm1.cpp \
../Core/Src/fsm2.cpp \
../Core/Src/heading.cpp \
../Core/Src/main.cpp \
../Core/Src/motor_task.cpp 

C_SRCS += \
../Core/Src/BNO055.c \
../Core/Src/bno055_init.c \
../Core/Src/encoder.c \
../Core/Src/motor_driver.c \
../Core/Src/printf_retarget.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/time_utils.c \
../Core/Src/uart_dma_idle.c 

C_DEPS += \
./Core/Src/BNO055.d \
./Core/Src/bno055_init.d \
./Core/Src/encoder.d \
./Core/Src/motor_driver.d \
./Core/Src/printf_retarget.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/time_utils.d \
./Core/Src/uart_dma_idle.d 

OBJS += \
./Core/Src/BNO055.o \
./Core/Src/balance.o \
./Core/Src/battery_check.o \
./Core/Src/bluetooth.o \
./Core/Src/bno055_init.o \
./Core/Src/command_parser.o \
./Core/Src/encoder.o \
./Core/Src/fsm1.o \
./Core/Src/fsm2.o \
./Core/Src/heading.o \
./Core/Src/main.o \
./Core/Src/motor_driver.o \
./Core/Src/motor_task.o \
./Core/Src/printf_retarget.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/time_utils.o \
./Core/Src/uart_dma_idle.o 

CPP_DEPS += \
./Core/Src/balance.d \
./Core/Src/battery_check.d \
./Core/Src/bluetooth.d \
./Core/Src/command_parser.d \
./Core/Src/fsm1.d \
./Core/Src/fsm2.d \
./Core/Src/heading.d \
./Core/Src/main.d \
./Core/Src/motor_task.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/BNO055.cyclo ./Core/Src/BNO055.d ./Core/Src/BNO055.o ./Core/Src/BNO055.su ./Core/Src/balance.cyclo ./Core/Src/balance.d ./Core/Src/balance.o ./Core/Src/balance.su ./Core/Src/battery_check.cyclo ./Core/Src/battery_check.d ./Core/Src/battery_check.o ./Core/Src/battery_check.su ./Core/Src/bluetooth.cyclo ./Core/Src/bluetooth.d ./Core/Src/bluetooth.o ./Core/Src/bluetooth.su ./Core/Src/bno055_init.cyclo ./Core/Src/bno055_init.d ./Core/Src/bno055_init.o ./Core/Src/bno055_init.su ./Core/Src/command_parser.cyclo ./Core/Src/command_parser.d ./Core/Src/command_parser.o ./Core/Src/command_parser.su ./Core/Src/encoder.cyclo ./Core/Src/encoder.d ./Core/Src/encoder.o ./Core/Src/encoder.su ./Core/Src/fsm1.cyclo ./Core/Src/fsm1.d ./Core/Src/fsm1.o ./Core/Src/fsm1.su ./Core/Src/fsm2.cyclo ./Core/Src/fsm2.d ./Core/Src/fsm2.o ./Core/Src/fsm2.su ./Core/Src/heading.cyclo ./Core/Src/heading.d ./Core/Src/heading.o ./Core/Src/heading.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motor_driver.cyclo ./Core/Src/motor_driver.d ./Core/Src/motor_driver.o ./Core/Src/motor_driver.su ./Core/Src/motor_task.cyclo ./Core/Src/motor_task.d ./Core/Src/motor_task.o ./Core/Src/motor_task.su ./Core/Src/printf_retarget.cyclo ./Core/Src/printf_retarget.d ./Core/Src/printf_retarget.o ./Core/Src/printf_retarget.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/time_utils.cyclo ./Core/Src/time_utils.d ./Core/Src/time_utils.o ./Core/Src/time_utils.su ./Core/Src/uart_dma_idle.cyclo ./Core/Src/uart_dma_idle.d ./Core/Src/uart_dma_idle.o ./Core/Src/uart_dma_idle.su

.PHONY: clean-Core-2f-Src

