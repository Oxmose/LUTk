/*******************************************************************************
 * @file stm_clocks.h
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

#ifndef __BOARD_STM32F401RE_CLOCKS_H__
#define __BOARD_STM32F401RE_CLOCKS_H__

#include "error_types.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/* RCC registers map */
#define CLOCK_RCC_BASE_ADDRESS        0x40023800
#define CLOCK_RCC_CR_ADDRESS          (CLOCK_RCC_BASE_ADDRESS)
#define CLOCK_RCC_PLLCFGR_ADDRESS     (CLOCK_RCC_BASE_ADDRESS + 0x04)
#define CLOCK_RCC_CFGR_ADDRESS        (CLOCK_RCC_BASE_ADDRESS + 0x08)
#define CLOCK_RCC_CIR_ADDRESS         (CLOCK_RCC_BASE_ADDRESS + 0x0C)
#define CLOCK_RCC_AHB1RSTR_ADDRESS    (CLOCK_RCC_BASE_ADDRESS + 0x10)
#define CLOCK_RCC_AHB2RSTR_ADDRESS    (CLOCK_RCC_BASE_ADDRESS + 0x14)
#define CLOCK_RCC_APB1RSTR_ADDRESS    (CLOCK_RCC_BASE_ADDRESS + 0x20)
#define CLOCK_RCC_APB2RSTR_ADDRESS    (CLOCK_RCC_BASE_ADDRESS + 0x24)
#define CLOCK_RCC_AHB1ENR_ADDRESS     (CLOCK_RCC_BASE_ADDRESS + 0x30)
#define CLOCK_RCC_AHB2ENR_ADDRESS     (CLOCK_RCC_BASE_ADDRESS + 0x34)
#define CLOCK_RCC_APB1ENR_ADDRESS     (CLOCK_RCC_BASE_ADDRESS + 0x40)
#define CLOCK_RCC_APB2ENR_ADDRESS     (CLOCK_RCC_BASE_ADDRESS + 0x44)
#define CLOCK_RCC_AHB1LPENR_ADDRESS   (CLOCK_RCC_BASE_ADDRESS + 0x50)
#define CLOCK_RCC_AHB2LPENR_ADDRESS   (CLOCK_RCC_BASE_ADDRESS + 0x54)
#define CLOCK_RCC_APB1LPENR_ADDRESS   (CLOCK_RCC_BASE_ADDRESS + 0x60)
#define CLOCK_RCC_APB2LPENR_ADDRESS   (CLOCK_RCC_BASE_ADDRESS + 0x64)
#define CLOCK_RCC_BDCR_ADDRESS        (CLOCK_RCC_BASE_ADDRESS + 0x70)
#define CLOCK_RCC_CSR_ADDRESS         (CLOCK_RCC_BASE_ADDRESS + 0x74)
#define CLOCK_RCC_SSCGR_ADDRESS       (CLOCK_RCC_BASE_ADDRESS + 0x80)
#define CLOCK_RCC_PLLI2S_CFGR_ADDRESS (CLOCK_RCC_BASE_ADDRESS + 0x84)
#define CLOCK_RCC_DCKCFGR_ADDRESS     (CLOCK_RCC_BASE_ADDRESS + 0x8C)

/* Registers masks and offsets */
#define CLOCK_RCC_PLLCFGR_PLLM_MASK   0x0000003F
#define CLOCK_RCC_PLLCFGR_PLLN_MASK   0x00007FC0
#define CLOCK_RCC_PLLCFGR_PLLP_MASK   0x00030000
#define CLOCK_RCC_PLLCFGR_PLLQ_MASK   0x0F000000

#define CLOCK_RCC_PLLCFGR_PLLSRC_MASK   0x00400000

#define CLOCK_RCC_PLLCFGR_PLLM_OFFSET 0
#define CLOCK_RCC_PLLCFGR_PLLN_OFFSET 6
#define CLOCK_RCC_PLLCFGR_PLLP_OFFSET 16
#define CLOCK_RCC_PLLCFGR_PLLQ_OFFSET 24

#define CLOCK_RCC_PLLCFGR_PLLSRC_OFFSET 22

/* Clocks settings */
#define CLOCK_MHZ       1000000
#define HSI_CLOCK_FREQ  16000000
#define APB1_CLOCK_FREQ 42000000
#define APB2_CLOCK_FREQ 84000000
#define SYS_CLOCK_FREQ  84000000

/* RCC control settings */
#define RCC_CR_PLLI2SRDY 0x08000000
#define RCC_CR_PLLI2SON  0x04000000
#define RCC_CR_PLLRDY    0x02000000
#define RCC_CR_PLLON     0x01000000
#define RCC_CR_HSIRDY    0x00000002
#define RCC_CR_HSION     0x00000001

#define RCC_CFGR_SW_MASK  0x00000003
#define RCC_CFGR_SWS_MASK 0x0000000C

#define RCC_CFGR_SW_PLL  0x00000002
#define RCC_CFGR_SWS_PLL 0x00000008

/* PLL settings for 84MHz system clock */
#define PLLM_VALUE (HSI_CLOCK_FREQ / CLOCK_MHZ)  
#define PLLN_VALUE 336 
#define PLLP_VALUE 4
#define PLLQ_VALUE 8

#define PLLSRC_VALUE 0

/* Flash latency for 84MHz system clock */
#define CLOCK_FLASH_WAIT_STATE_COUNT 2

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

#endif /* #ifndef __BOARD_STM32F401RE_CLOCKS_H__ */