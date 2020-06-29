/*******************************************************************************
 * @file bsp_flash.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief STM32 F401RE flash management.
 *
 * @details STM32 F401RE flash management. This module contains the 
 * routines used to manage the STM32 F401RE flash.
 ******************************************************************************/

#ifndef __BOARD_STM32F401RE_BSP_FLASH_H__
#define __BOARD_STM32F401RE_BSP_FLASH_H__

#include "error_types.h"
#include "stdint.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/** @brief Flash Access Control Register address */
#define FLASH_ACR_ADDRESS  0x40023C00
#define FLASH_ACR_REGISTER ((volatile uint32_t*)FLASH_ACR_ADDRESS)

/** @brief Flash data cache enable bit. */
#define FLASH_ACR_DCACHE_EN   0x00000400
/** @brief Flash instruction cache enable bit. */
#define FLASH_ACR_ICACHE_EN   0x00000200
/** @brief Flash prefetch enable bit. */
#define FLASH_ACR_PREFETCH_EN 0x00000100

/** @brief Flash ACR latency mask. */
#define FLASH_ACR_LATENCY_MASK 0x0000000F

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/** @brief Power scaling modes available on the STM32F401RE. */
enum FLASH_LATENCY_WS
{
    /** @brief Flash wait states: 0 */
    FLASH_LATENCY_WS_0  = 0x00000000,
    /** @brief Flash wait states: 1 */
    FLASH_LATENCY_WS_1  = 0x00000001,
    /** @brief Flash wait states: 2 */
    FLASH_LATENCY_WS_2  = 0x00000002,
    /** @brief Flash wait states: 3 */
    FLASH_LATENCY_WS_3  = 0x00000003,
    /** @brief Flash wait states: 4 */
    FLASH_LATENCY_WS_4  = 0x00000004,
    /** @brief Flash wait states: 5 */
    FLASH_LATENCY_WS_5  = 0x00000005,
    /** @brief Flash wait states: 6 */
    FLASH_LATENCY_WS_6  = 0x00000006,
    /** @brief Flash wait states: 7 */
    FLASH_LATENCY_WS_7  = 0x00000007,
    /** @brief Flash wait states: 8 */
    FLASH_LATENCY_WS_8  = 0x00000008,
    /** @brief Flash wait states: 9 */
    FLASH_LATENCY_WS_9  = 0x00000009,
    /** @brief Flash wait states: 10 */
    FLASH_LATENCY_WS_10 = 0x00000010,
    /** @brief Flash wait states: 11 */
    FLASH_LATENCY_WS_11 = 0x00000011,
    /** @brief Flash wait states: 12 */
    FLASH_LATENCY_WS_12 = 0x00000012,
    /** @brief Flash wait states: 13 */
    FLASH_LATENCY_WS_13 = 0x00000013,
    /** @brief Flash wait states: 14 */
    FLASH_LATENCY_WS_14 = 0x00000014,
    /** @brief Flash wait states: 15 */
    FLASH_LATENCY_WS_15 = 0x00000015,
};

/** @brief Short hand for enum FLASH_LATENCY_WS. */
typedef enum FLASH_LATENCY_WS FLASH_LATENCY_WS_E;

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

/**
­ * @brief Enables flash instruction and data cache.
 * 
 * @details Enables flash instruction and data cache.
 */
void bsp_flash_cache_enable(void);

/**
­ * @brief Enables flash prefetech unit.
 * 
 * @details Enables flash prefetech unit.
 */
void bsp_flash_prefetch_enable(void);

/**
­ * @brief Sets the flash latency.
 * 
 * @details  Sets the flash latency based on the latency given as parameter.
 *
 * @param[in] latency The latency to set.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E bsp_flash_set_latency(const FLASH_LATENCY_WS_E latency);

#endif /* #ifndef __BOARD_STM32F401RE_BSP_FLASH_H__ */