/*******************************************************************************
 * @file flash.c
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

#include "error_types.h"
#include "stdint.h"
#include "flash.h"
#include "cpu_api.h"

/*******************************************************************************
 * Private functions
 ******************************************************************************/


/*******************************************************************************
 * Public functions
 ******************************************************************************/

void flash_enable_cache(void)
{
	volatile uint32_t* flash_reg;
	flash_reg = (volatile uint32_t*)FLASH_ACR_ADDRESS;

	*flash_reg = *flash_reg | FLASH_ACR_DCACHE_EN | FLASH_ACR_ICACHE_EN;	
}

void flash_disable_cache(void)
{
	volatile uint32_t* flash_reg;
	flash_reg = (volatile uint32_t*)FLASH_ACR_ADDRESS;

	*flash_reg = *flash_reg & ~(FLASH_ACR_DCACHE_EN | FLASH_ACR_ICACHE_EN);	
}

void flash_enable_prefetch(void)
{
	volatile uint32_t* flash_reg;
	flash_reg = (volatile uint32_t*)FLASH_ACR_ADDRESS;

	*flash_reg = *flash_reg & ~FLASH_ACR_PRFT_EN;	
}

void flash_disable_prefetch(void)
{
	volatile uint32_t* flash_reg;
	flash_reg = (volatile uint32_t*)FLASH_ACR_ADDRESS;

	*flash_reg = *flash_reg & ~FLASH_ACR_PRFT_EN;	
}

ERROR_CODE_E flash_set_latency(const uint8_t wait_states)
{
	volatile uint32_t* flash_reg;
	flash_reg = (volatile uint32_t*)FLASH_ACR_ADDRESS;

	/* Check correct latency */
	if(wait_states > FLASH_ACR_LATENCY_MASK)
	{
		return ERROR_INVALID_PARAM;
	}

	/* Set the number of wait state */
	*flash_reg = (*flash_reg & ~FLASH_ACR_LATENCY_MASK) | (wait_states & FLASH_ACR_LATENCY_MASK);

	/* Wait for validation */
	while((*flash_reg & FLASH_ACR_LATENCY_MASK) != (wait_states & FLASH_ACR_LATENCY_MASK));

	return NO_ERROR;
}