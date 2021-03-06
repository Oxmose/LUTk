/*******************************************************************************
 * @file config.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 24/06/2020
 *
 * @version 1.0
 *
 * @brief STM32-F401RE global configuration file.
 *
 * @details STM32-F401RE global configuration file. This file contains all the
 * settings that the user can set before generating the kernel's binary.
 ******************************************************************************/

#ifndef __GLOBAL_CONFIG_H__
#define __GLOBAL_CONFIG_H__

#include "serial_settings.h"

/** Kernel's serial settings. */
#define CONFIG_UART_SETTINGS {                  \
    .baudrate    = 115200,                      \
    .word_length = 8,                           \
    .stop_bits   = SERIAL_STOP_BITS_1,          \
    .partity     = SERIAL_PARITY_NONE,          \
    .ctrl_flow   = SERIAL_CTRL_FLOW_NONE        \
}

/* Main timer tick frequency in Hz */
#define CONFIG_MAIN_TIMER_TICK_FREQ 100

/* Maximum number of interrupts lines to manage */
#define CONFIG_MAX_INTERRUPT_LINES 68

/* Kernel log level */
#define ERROR_LOG_LEVEL   3
#define WARNING_LOG_LEVEL 2
#define INFO_LOG_LEVEL    1
#define NONE_LOG_LEVEL    0

#define KERNEL_LOG_LEVEL ERROR_LOG_LEVEL

/* Architecture type */
#define ARCH_32_BITS

#endif /* #ifndef __GLOBAL_CONFIG_H__ */