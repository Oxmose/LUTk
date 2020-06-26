################################################################################
# LUTk Makefile
# 
# Created: 23/05/2020
#
# Author: Alexy Torres Aurora Dugo
#
# Architecture module makefile. This makefile is used to compile the arch module
# for the desired target.
################################################################################

CPU_ARCH_LIST=cortex_m4
BOARD_ARCH_LIST=stm32_f401re

BUILD_DIR  = ./build
BIN_DIR    = ./bin

.PHONY: all
all: init build_modules

init: 

	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

build_cpu:
################################################################################
# Build the CPU target arch module
ifeq ($(target_cpu), cortex_m4)
	@$(MAKE) -C ./cpu/arm/cortex_m4
else
	@echo "\e[1m\e[31m\n=== ERROR: Unknown CPU architecture $(target_cpu)\e[22m\e[39m"
	@echo "Available architectures: $(CPU_ARCH_LIST)\n"
	@exit 1
endif 

build_board:
################################################################################
# Build the board target arch module
ifeq ($(target_board), stm32_f401re)
	@$(MAKE) -C ./board/stm32/f401re
else
	@echo "\e[1m\e[31m\n=== ERROR: Unknown board architecture $(target_board)\e[22m\e[39m"
	@echo "Available architectures: $(BOARD_ARCH_LIST)\n"
	@exit 1
endif 

build_modules: build_cpu build_board
# Merge the two modules
	@ar r $(BIN_DIR)/libarch.a $(BUILD_DIR)/* 
	@$(RM) -rf $(BUILD_DIR)
	@echo "\e[1m\e[92m\n=> Generated ARCH module\e[22m\e[39m"
	@echo "\e[1m\e[92m--------------------------------------------------------------------------------\n\e[22m\e[39m"

clean:
################################################################################
# Clean the CPU target arch module
ifeq ($(target_cpu), cortex_m4)
	@$(MAKE) -C ./cpu/arm/cortex_m4 clean
else
	@echo "\e[1m\e[31m\n=== ERROR: Unknown CPU architecture $(target_cpu)\e[22m\e[39m"
	@echo "Available architectures: $(CPU_ARCH_LIST)\n"
	@exit 1
endif 

################################################################################
# Clean the board target arch module
ifeq ($(target_board), stm32_f401re)
	@$(MAKE) -C ./board/stm32/f401re clean
else
	@echo "\e[1m\e[31m\n=== ERROR: Unknown board architecture $(target_board)\e[22m\e[39m"
	@echo "Available architectures: $(BOARD_ARCH_LIST)\n"
	@exit 1
endif 

	$(RM) -rf $(BUILD_DIR) $(BIN_DIR)

	@echo "\e[1m\e[34m\n#-------------------------------------------------------------------------------\e[22m\e[39m"
	@echo "\e[1m\e[34m| Cleaned ARCH module\e[22m\e[39m"
	@echo "\e[1m\e[34m#-------------------------------------------------------------------------------\n\e[22m\e[39m"