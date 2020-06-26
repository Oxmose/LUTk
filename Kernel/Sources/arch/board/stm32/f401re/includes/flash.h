/*******************************************************************************
 * @file flash.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief STM32-F401RE flash management.
 *
 * @details STM32-F401RE flash management. This module contains the routines 
 * used to configure the flash used by the board.
 ******************************************************************************/

#ifndef __BOARD_STM32F401RE_FLASH_H__
#define __BOARD_STM32F401RE_FLASH_H__

#include "stdint.h"
#include "error_types.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/* Flash registers map */
#define FLASH_REG_BASE_ADDRESS 0x40023C00
#define FLASH_ACR_ADDRESS      (FLASH_REG_BASE_ADDRESS)

/* Flash registers masks */
#define FLASH_ACR_LATENCY_MASK 0x0000000F

/* Flash registers values */
#define FLASH_ACR_DCACHE_EN 0x00000400
#define FLASH_ACR_ICACHE_EN 0x00000200
#define FLASH_ACR_PRFT_EN   0x00000100

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

void flash_enable_cache(void);
void flash_disable_cache(void);;
void flash_enable_prefetch(void);
void flash_disable_prefetch(void);

ERROR_CODE_E flash_set_latency(const uint8_t wait_states);

#endif /* #ifndef __BOARD_STM32F401RE_FLASH_H__ */