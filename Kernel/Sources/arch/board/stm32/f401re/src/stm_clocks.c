/*******************************************************************************
 * @file stm_clocks.c
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 24/06/2020
 *
 * @version 1.0
 *
 * @brief STM32-F401RE clocks management.
 *
 * @details STM32-F401RE clocks management. This module contains the routines 
 * used to configure the different clocks used by the board.
 ******************************************************************************/

#include "error_types.h"
#include "stdint.h"
#include "stm_clocks.h"
#include "cpu_api.h"
#include "flash.h"

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/** 
 * @brief Initializes the PLL and select HSI as input clock
 * 
 * @details Initializes the PLL and select HSI as input clock
 */
static void pll_init(void)
{
	volatile uint32_t* rcc_reg;
	rcc_reg = (volatile uint32_t*)CLOCK_RCC_PLLCFGR_ADDRESS;

	/* Set the main PLL and audio PLL input division factor */
	*rcc_reg = (*rcc_reg & ~CLOCK_RCC_PLLCFGR_PLLM_MASK) | (PLLM_VALUE << CLOCK_RCC_PLLCFGR_PLLM_OFFSET);

	/* Set the main PLL for VCO */
	*rcc_reg = (*rcc_reg & ~CLOCK_RCC_PLLCFGR_PLLN_MASK) | (PLLN_VALUE << CLOCK_RCC_PLLCFGR_PLLN_OFFSET);

	/* Set the main PLL for the system clock */
	*rcc_reg = (*rcc_reg & ~CLOCK_RCC_PLLCFGR_PLLP_MASK) | (PLLP_VALUE << CLOCK_RCC_PLLCFGR_PLLP_OFFSET);

	/* Set the main PLL for USB OTG FS, SDIO and random gen */
	*rcc_reg = (*rcc_reg & ~CLOCK_RCC_PLLCFGR_PLLQ_MASK) | (PLLQ_VALUE << CLOCK_RCC_PLLCFGR_PLLQ_OFFSET);

	/* Set the PLL to use HSI for input clock */
	*rcc_reg = (*rcc_reg & ~CLOCK_RCC_PLLCFGR_PLLSRC_MASK) | (PLLSRC_VALUE << CLOCK_RCC_PLLCFGR_PLLSRC_OFFSET);

	/* PLLI2S is keps at its reset values to produce a 96 MHz output */

	/* Enable the PLL */
	rcc_reg = (volatile uint32_t*)CLOCK_RCC_CR_ADDRESS;
	*rcc_reg = *rcc_reg | RCC_CR_PLLI2SON | RCC_CR_PLLON;

	/* Make sure HSI is on and ready */
	if((*rcc_reg & RCC_CR_HSIRDY) == 0)
	{
		*rcc_reg = *rcc_reg | RCC_CR_HSION;
	}
	
	/* Wait for HSI and PLL locking */
	while((*rcc_reg & RCC_CR_HSIRDY) == 0);	
	while((*rcc_reg & RCC_CR_PLLI2SRDY) == 0 || (*rcc_reg & RCC_CR_PLLRDY) == 0);
}

/*******************************************************************************
 * Public functions
 ******************************************************************************/

ERROR_CODE_E clocks_init(void)
{
	ERROR_CODE_E       error;
    volatile uint32_t* rcc_reg;

	/* Init flash wait states number */
	error = flash_set_latency(CLOCK_FLASH_WAIT_STATE_COUNT);
	if(error != NO_ERROR)
	{
		return error;
	}

    /* Init PLL */
    pll_init();

    /* Set the system clock input to use PLL */
    rcc_reg = (volatile uint32_t*)CLOCK_RCC_CFGR_ADDRESS;
    *rcc_reg = (*rcc_reg & ~RCC_CFGR_SW_MASK) | RCC_CFGR_SW_PLL;

    while((*rcc_reg & RCC_CFGR_SWS_MASK) != RCC_CFGR_SWS_PLL);

    return NO_ERROR;
}
