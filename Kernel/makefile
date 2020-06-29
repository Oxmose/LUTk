################################################################################
# LUTk Makefile
# 
# Created: 23/05/2020
#
# Author: Alexy Torres Aurora Dugo
#
# Main makefile. This makefile will proceed to compile all required modules
# and configurations.
# Once compiled it will produce the final binary file for the desired 
# architecture
################################################################################

CPU_ARCH_LIST= cortex_m4
TARGET_LIST= stm32_f401re
SOURCE_DIR= ./Sources
CONFIG_DIR= ./Config

BUILD_DIR = build

MODULES= -larch

KERNEL = lutk

.PHONY: all
all: init build_modules build_kernel

init: 
	@mkdir -p $(BUILD_DIR)

ifeq ($(target), stm32_f401re)
	@cp $(CONFIG_DIR)/arch/stm32_f401re/settings.mk .
	@cp $(CONFIG_DIR)/arch/stm32_f401re/config.h .
else 
	@echo "\e[1m\e[31m\n=== ERROR: Unknown target $(target)\e[22m\e[39m"
	@echo "Available targets: $(TARGET_LIST)\n"
	@exit 1
endif

build_modules:

# Build the architecture module
ifeq ($(target), stm32_f401re)
	@make -C $(SOURCE_DIR)/arch target_board=stm32_f401re target_cpu=cortex_m4
else 
	@echo "\e[1m\e[31m\n=== ERROR: Unknown target $(target)\e[22m\e[39m"
	@echo "Available targets: $(TARGET_LIST)\n"
	@exit 1
endif

# Build the user module 
	@make -C $(SOURCE_DIR)/user
# Build the io module 
	@make -C $(SOURCE_DIR)/io
# Build the core module 
	@make -C $(SOURCE_DIR)/core
build_kernel:
	@echo "\e[1m\e[34m\n#-------------------------------------------------------------------------------\e[22m\e[39m"
	@echo "\e[1m\e[34m| Building kernel for target $(target)\e[22m\e[39m"
	@echo "\e[1m\e[34m#-------------------------------------------------------------------------------\n\e[22m\e[39m"

	@make -C $(SOURCE_DIR)/global KERNEL_NAME=$(KERNEL)

	@cp -r $(SOURCE_DIR)/global/build/* $(BUILD_DIR)

	@echo "\e[1m\e[34m#-------------------------------------------------------------------------------\e[22m\e[39m"
	@echo "\e[1m\e[34m| Generated kernel for target $(target)\e[22m\e[39m"
	@echo "\e[1m\e[34m#-------------------------------------------------------------------------------\n\e[22m\e[39m"

clean:
# Clean the architecture module
ifeq ($(target), stm32_f401re)
	@make -C $(SOURCE_DIR)/arch target_board=stm32_f401re target_cpu=cortex_m4 clean
else 
	@make -C $(SOURCE_DIR)/arch target_board=stm32_f401re target_cpu=cortex_m4 clean
endif

# Clean general modules
	@make -C $(SOURCE_DIR)/user clean
	@make -C $(SOURCE_DIR)/global clean

# Clean kernel build directory
	rm -rf  $(BUILD_DIR)

	@echo "\e[1m\e[34m\n#-------------------------------------------------------------------------------\e[22m\e[39m"
	@echo "\e[1m\e[34m| Cleaned kernel \e[22m\e[39m"
	@echo "\e[1m\e[34m#-------------------------------------------------------------------------------\n\e[22m\e[39m"
	