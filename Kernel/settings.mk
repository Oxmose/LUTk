################################################################################
# LUTk Makefile
# 
# Created: 23/05/2020
#
# Author: Alexy Torres Aurora Dugo
#
# Settings makefile, contains the shared variables used by the different
# makefiles.
################################################################################

CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

LINKER_FILE = ../../Config/arch/stm32_f401re/linker.ld

DEBUG_FLAGS = -O0 -g3
EXTRA_FLAGS = -O2

CFLAGS = -std=c11 -nostdinc -fno-builtin -nostdlib -fno-stack-protector      \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -fno-pie      \
		 -no-pie -ffreestanding -mcpu=cortex-m4 \
		 --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb 
		 
ifeq ($(DEBUG), TRUE)
CFLAGS += $(DEBUG_FLAGS)
else
CFLAGS += $(EXTRA_FLAGS)
endif

ASFLAGS = -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb
LDFLAGS = -T $(LINKER_FILE) --whole-archive