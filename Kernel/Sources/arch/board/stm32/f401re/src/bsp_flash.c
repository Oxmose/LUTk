/*******************************************************************************
 * @file bsp_flash.c
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief STM32 F401RE BSP flash management.
 *
 * @details STM32 F401RE BSP flash management. This module contains the 
 * routines used to manage the BSP flash, cache and prefetch unit.
 ******************************************************************************/

#include "error_types.h"
#include "bsp_flash.h"
#include "cpu_api.h"
#include "stdint.h"
#include "config.h"

/*******************************************************************************
 * Private Data
 ******************************************************************************/

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/*******************************************************************************
 * Public functions
 ******************************************************************************/

void bsp_flash_cache_enable(void)
{
    *FLASH_ACR_REGISTER = *FLASH_ACR_REGISTER  | 
                           FLASH_ACR_ICACHE_EN | 
                           FLASH_ACR_DCACHE_EN;
    cpu_mem_barrier();
}

void bsp_flash_prefetch_enable(void)
{
    *FLASH_ACR_REGISTER = *FLASH_ACR_REGISTER  |  FLASH_ACR_PREFETCH_EN;
    cpu_mem_barrier();
}

ERROR_CODE_E bsp_flash_set_latency(const FLASH_LATENCY_WS_E latency)
{
    /* Sets the flash latency value, we don't apply mask verification because 
     * the FLASH_LATENCY_WS_E enumeration should already contain the right 
     * values.
     */
    *FLASH_ACR_REGISTER = (*FLASH_ACR_REGISTER & ~FLASH_ACR_LATENCY_MASK) | 
                          latency;

    /* Delay to ensure bit update */
    while((*FLASH_ACR_REGISTER & FLASH_ACR_LATENCY_MASK) != latency);

#if KERNEL_LOG_LEVEL >= INFO_LOG_LEVEL
    KERNEL_LOG_INFO("Flash lantency changed", 
                    latency, 
                    sizeof(latency), 
                    NO_ERROR);
#endif

    return NO_ERROR;
}