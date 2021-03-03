/*******************************************************************************
 * @file bsp_clocks.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief STM32 F401RE clocks and timers management.
 *
 * @details STM32 F401RE clocks and timers management. This module contains the 
 * routines used to manage the STM32 F401RE clocks and timers.
 ******************************************************************************/

#ifndef __BOARD_STM32F401RE_BSP_CLOCK_H__
#define __BOARD_STM32F401RE_BSP_CLOCK_H__

#include "error_types.h"
#include "bsp_usart.h"
#include "bsp_gpio.h"
#include "stdint.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/** @brief RCC Control Register address. */
#define RCC_CR_ADDRESS          0x40023800
#define RCC_CR_REGISTER         ((volatile uint32_t*)RCC_CR_ADDRESS)
/** @brief RCC PLL Configuration Register address. */
#define RCC_PLLCFGR_ADDRESS     0x40023804 
#define RCC_PLLCFGR_REGISTER    ((volatile uint32_t*)RCC_PLLCFGR_ADDRESS)
/** @brief RCC Configuration Register address. */
#define RCC_CFGR_ADDRESS        0x40023808
#define RCC_CFGR_REGISTER       ((volatile uint32_t*)RCC_CFGR_ADDRESS)
/** @brief RCC AHB1 peripheral clock enable register address. */
#define RCC_AHB1ENR_ADDRESS     0x40023830
#define RCC_AHB1ENR_REGISTER    ((volatile uint32_t*)RCC_AHB1ENR_ADDRESS)
/** @brief RCC APB1 peripheral clock enable register address. */
#define RCC_APB1ENR_ADDRESS     0x40023840
#define RCC_APB1ENR_REGISTER    ((volatile uint32_t*)RCC_APB1ENR_ADDRESS)
/** @brief RCC APB2 peripheral clock enable register address. */
#define RCC_APB2ENR_ADDRESS     0x40023844
#define RCC_APB2ENR_REGISTER    ((volatile uint32_t*)RCC_APB2ENR_ADDRESS)

/** @brief APB2ENR System configuration controller clock enable. */
#define RCC_APB2ENR_SYSCFGEN 0x00004000
/** @brief AHB1ENR GPIO A enable. */
#define RCC_AHB1ENR_GPIOAEN 0x00000001
/** @brief AHB1ENR GPIO B enable. */
#define RCC_AHB1ENR_GPIOBEN 0x00000002
/** @brief AHB1ENR GPIO C enable. */
#define RCC_AHB1ENR_GPIOCEN 0x00000004
/** @brief AHB1ENR GPIO D enable. */
#define RCC_AHB1ENR_GPIODEN 0x00000008
/** @brief AHB1ENR GPIO E enable. */
#define RCC_AHB1ENR_GPIOEEN 0x00000010
/** @brief AHB1ENR GPIO H enable. */
#define RCC_AHB1ENR_GPIOHEN 0x00000080
/** @brief APB1ENR Power interface clock enable. */
#define RCC_APB1ENR_PWREN    0x10000000
/** @brief APB1ENR USART2 clock enable. */
#define RCC_APB1ENR_USART2EN 0x00020000
/** @brief APB2ENR USART1 clock enable. */
#define RCC_APB2ENR_USART1EN 0x00000010
/** @brief APB2ENR USART6 clock enable. */
#define RCC_APB2ENR_USART6EN 0x00000020

/** @brief RCC_CR PLLI2S ready flag. */
#define RCC_CR_PLLI2SRDY   0x08000000
/** @brief RCC_CR PLLI2S enabled. */
#define RCC_CR_PLLI2SON    0x04000000
/** @brief RCC_CR PLL ready flag. */
#define RCC_CR_PLLRDY      0x02000000
/** @brief RCC_CR PLL enabled. */
#define RCC_CR_PLLON       0x01000000
/** @brief RCC_CR HSI clock default trimming value. */
#define RCC_CR_HSITRIM_DEF 0x00000080
/** @brief RCC_CR HSI clock enabled. */
#define RCC_CR_HSION       0x00000001
/** @brief RCC_CR HSI clock ready flag. */
#define RCC_CR_HSIRDY      0x00000002

/** @brief RCC_CFGR System clock switch to HSI value. */
#define RCC_CFGR_SW_HSI     0x00000000
/** @brief RCC_CFGR System clock switch to HSE value. */
#define RCC_CFGR_SW_HSE     0x00000001
/** @brief RCC_CFGR System clock switch to PLL value. */
#define RCC_CFGR_SW_PLL     0x00000002
/** @brief RCC_CFGR System clock switch to HSI status value. */
#define RCC_CFGR_SWS_HSI    0x00000000
/** @brief RCC_CFGR System clock switch to HSE status value. */
#define RCC_CFGR_SWS_HSE    0x00000004
/** @brief RCC_CFGR System clock switch to PLL status value. */
#define RCC_CFGR_SWS_PLL    0x00000008
/** @brief RCC_CFGR AHB prescaller enabled state. */
#define RCC_CFGR_HPRE_EN    0x00000080
/** @brief RCC_CFGR AHB prescaller value. */
#define RCC_CFGR_HRPE_DIV1  0x00000000
/** @brief RCC_CFGR APB LS prescaller enabled state. */
#define RCC_CFGR_PPRE1_EN   0x00001000
/** @brief RCC_CFGR APB LS prescaller value. */
#define RCC_CFGR_PPRE1_DIV2 0x00001000
/** @brief RCC_CFGR APB HS prescaller enabled state. */
#define RCC_CFGR_PPRE2_EN   0x00008000
/** @brief RCC_CFGR APB HS prescaller value. */
#define RCC_CFGR_PPRE2_DIV1 0x00000000

/** @brief RCC_PLLCFGR PLLM bit mask. */
#define RCC_PLLCFGR_PLLM_MASK   0x0000003F
/** @brief RCC_PLLCFGR PLLN bit mask. */
#define RCC_PLLCFGR_PLLN_MASK   0x00007FC0
/** @brief RCC_PLLCFGR PLLP bit mask. */
#define RCC_PLLCFGR_PLLP_MASK   0x00030000
/** @brief RCC_PLLCFGR PLLSRC bit mask. */
#define RCC_PLLCFGR_PLLSRC_MASK 0x00400000
/** @brief RCC_PLLCFGR PLLQ bit mask. */
#define RCC_PLLCFGR_PLLQ_MASK   0x0F000000

/** @brief RCC_CFGR SW bit mask. */
#define RCC_CFGR_SW_MASK        0x00000003
/** @brief RCC_CFGR SWS bit mask. */
#define RCC_CFGR_SWS_MASK       0x0000000C
/** @brief RCC_CFGR HRPE bit mask. */
#define RCC_CFGR_HRPE_MASK      0x000000F0
/** @brief RCC_CFGR HRPE value bit mask. */
#define RCC_CFGR_HPRE_VAL_MASK  0x00000070
/** @brief RCC_CFGR PPRE1 bit mask. */
#define RCC_CFGR_PPRE1_MASK     0x00001C00
/** @brief RCC_CFGR PPRE1 value bit mask. */
#define RCC_CFGR_PPRE1_VAL_MASK 0x00000C00
/** @brief RCC_CFGR PPRE2 bit mask. */
#define RCC_CFGR_PPRE2_MASK     0x0000E000
/** @brief RCC_CFGR PPRE2 value bit mask. */
#define RCC_CFGR_PPRE2_VAL_MASK 0x00006000

/** @brief HSI clock trimming field mask. */
#define RCC_CR_HSITRIM_MASK 0x000000F8

/** @brief RCC_PLLCFGR PLLM bit field offset. */
#define RCC_PLLCFGR_PLLM_OFFSET   0
/** @brief RCC_PLLCFGR PLLN bit field offset. */
#define RCC_PLLCFGR_PLLN_OFFSET   6
/** @brief RCC_PLLCFGR PLLP bit field offset. */
#define RCC_PLLCFGR_PLLP_OFFSET   16
/** @brief RCC_PLLCFGR PLLSRC bit field offset. */
#define RCC_PLLCFGR_PLLSRC_OFFSET 22
/** @brief RCC_PLLCFGR PLLQ bit field offset. */
#define RCC_PLLCFGR_PLLQ_OFFSET   24

/** @brief RCC_CFGR HPRE bit field offset. */
#define RCC_CFGR_HRPE_OFFSET  4
/** @brief RCC_CFGR PPRE1 bit field offset. */
#define RCC_CFGR_PPRE1_OFFSET 10
/** @brief RCC_CFGR PPRE2 bit field offset. */
#define RCC_CFGR_PPRE2_OFFSET 13

/**** 
 * PLL settings for 84MHz system clock with HSI input 
 ****/

/** @brief Division factor for input clock. Divide by 16 the HSI clock. */
#define RCC_PLLM_VALUE   16  
/** @brief Multiply factor for system clock. Multiply by 336 the VCO clock. */
#define RCC_PLLN_VALUE   336 
/** @brief Division factor for system clock. Divide by 4 the VCO clock. */
#define RCC_PLLP_VALUE   1
/** @brief Division factor for USB OTG FS clock. Divide by 8 the VCO clock. */
#define RCC_PLLQ_VALUE   8
/** @brief PLL source clock set as HSI */
#define RCC_PLLSRC_VALUE 0

/****
 * Architecture values
 ****/

/** @brief HSI clock frequency */
#define RCC_HSI_BASE_FREQ 16000000
/** @brief HSE clock frequency (does not exists on STMF401RE) */
#define RCC_HSE_BASE_FREQ 0

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/** @brief Clock identifer enumeration. Stores all accessible BSP clocks. */
enum CLOCK_IDENTIFIER
{
    /** @brief System's clock identifier. */
    BSP_CLOCK_ID_SYSCLK,
    /** @brief HCLK, used by AHB bus, core, etc. */
    BSP_CLOCK_ID_HCLK,
    /** @brief FCLK sued by the cortex core. */
    BSP_CLOCK_ID_FCLK,      
    /** @brief PCLK1 used as APB1 peripheral clocks. */
    BSP_CLOCK_ID_PCLK1,
    /** @brief PCLK2 used as APB2 peripheral clocks. */
    BSP_CLOCK_ID_PCLK2,
    /** @brief PCLK1 used as APB1 timers clocks. */
    BSP_CLOCK_ID_APB1_TIMER,
    /** @brief PCLK1 used as APB2 timers clocks. */
    BSP_CLOCK_ID_APB2_TIMER,
};

/** @brief Short hand for enum CLOCK_IDENTIFIER. */
typedef enum CLOCK_IDENTIFIER CLOCK_IDENTIFIER_T;

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

/**
 * @brief Enables the USART clocks.
 *
 * @details Enables the USART clocks. This function will enable the  peripheral 
 * clock used by the USART corresponding to the identifier given as parameter.
 * If the identifier is unknown, the function has no effect.
 * 
 * @param[in] usart_id The USART identifier for which the clock should be 
 * enabled.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E bsp_clk_usart_enable(const USART_IDENTIFIER_E usart_id);

/**
 * @brief Enables the GPIO clocks.
 *
 * @details Enables the GPIO clocks. This function will enable the peripheral 
 * clock used by the GPIO corresponding to the identifier given as parameter.
 * If the identifier is unknown, the function has no effect.
 * 
 * @param[in] gpio_id The GPIO identifier for which the clock should be 
 * enabled.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E bsp_clk_gpio_enable(const GPIO_IDENTIFIER_E gpio_id);

/**
 * @brief Initializes system clocks.
 *
 * @details Initializes system clocks. The CPU, AHB and APB clocks are 
 * initialized. The function also sets the regulator output voltage needed by 
 * the clocks.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E bsp_clk_sys_init(void);

/** 
 * @brief Get the frequencies in MHz of the clocks which identifer corresponds 
 * to the identifier given as parameter.
 * 
 * @details Get the frequencies of the clocks which identifer corresponds to
 * the identifier given as parameter. The PLL parameters and other clocks
 * register are read to return the correct frequency for a given clock.
 * 
 * @param[in] clk_id The identifier of the clock.
 * 
 * @returns The frequency in MHz of the clock is returned.
 */
uint32_t bsp_clocks_get_freq(const CLOCK_IDENTIFIER_T clk_id);

#endif /* #ifndef __BOARD_STM32F401RE_BSP_CLOCK_H__ */