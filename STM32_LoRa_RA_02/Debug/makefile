################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
LoRa_RA_02_TEST.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
LoRa_RA_02_TEST.list \

OBJCOPY_BIN += \
LoRa_RA_02_TEST.bin \


# All Target
all: LoRa_RA_02_TEST.elf secondary-outputs

# Tool invocations
LoRa_RA_02_TEST.elf: $(OBJS) $(USER_OBJS) P:\EMBEDDED_PROJECTS\STM32_PROJECTS\CUBE_IDE_PROJECTS\LoRa_RA_02_TEST\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "LoRa_RA_02_TEST.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"P:\EMBEDDED_PROJECTS\STM32_PROJECTS\CUBE_IDE_PROJECTS\LoRa_RA_02_TEST\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="LoRa_RA_02_TEST.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

LoRa_RA_02_TEST.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "LoRa_RA_02_TEST.list"
	@echo 'Finished building: $@'
	@echo ' '

LoRa_RA_02_TEST.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "LoRa_RA_02_TEST.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
