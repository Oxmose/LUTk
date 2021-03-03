/*******************************************************************************
 * @file bsp_clocks.c
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief STM32 F401RE clocks and timers management.
 *
 * @details STM32 F401RE clocks and timers  management. This module contains the 
 * routines used to manage the STM32 F401RE and timers clocks.
 ******************************************************************************/

#include "error_types.h"
#include "bsp_clocks.h"
#include "bsp_flash.h"
#include "bsp_power.h"
#include "stdint.h"
#include "config.h"
#include "logger.h"

/*******************************************************************************
 * Private Data
 ******************************************************************************/

/** @brief Stores the system clock init state. */
static uint8_t bsp_clk_init = 0;

/** @brief HRPE AHB prescaler factors lookup table. */
static const uint16_t bsp_hpre_factor_lookup[8] = {2, 4, 8, 16, 64, 128, 256, 512};

/** @brief PPRE prescaler factors lookup table. */
static const uint8_t bsp_ppre_factor_lookup[4] = {2, 4, 8, 16};

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/**
 * @brief Initializes system clocks.
 *
 * @details Initializes system clocks. The HSI is enabled and its calibration
 * value.
 */
void bsp_clk_base_sys_init(void)
{
    *RCC_CR_REGISTER = (*RCC_CR_REGISTER & ~RCC_CR_HSITRIM_MASK) | 
                       (RCC_CR_HSION | RCC_CR_HSITRIM_DEF);
    while((*RCC_CR_REGISTER & RCC_CR_HSIRDY) == 0);
}

/**
 * @brief Initializes system PLL clocks.
 *
 * @details Initializes system PLL clocks. The PLL are set for a system clock
 * of 84MHz and bus to 48MHz.
 */
void bsp_clk_pll_init(void)
{
    /* PLL should be disabled at that point */
    *RCC_PLLCFGR_REGISTER = *RCC_PLLCFGR_REGISTER & 
                            ~(RCC_PLLCFGR_PLLM_MASK | RCC_PLLCFGR_PLLN_MASK | 
                              RCC_PLLCFGR_PLLP_MASK | RCC_PLLCFGR_PLLQ_MASK | 
                              RCC_PLLCFGR_PLLSRC_MASK);

    /* Set the PLL values */
    *RCC_PLLCFGR_REGISTER = *RCC_PLLCFGR_REGISTER |
                            (RCC_PLLM_VALUE << RCC_PLLCFGR_PLLM_OFFSET) |
                            (RCC_PLLN_VALUE << RCC_PLLCFGR_PLLN_OFFSET) |
                            (RCC_PLLP_VALUE << RCC_PLLCFGR_PLLP_OFFSET) |
                            (RCC_PLLQ_VALUE << RCC_PLLCFGR_PLLQ_OFFSET) |
                            (RCC_PLLSRC_VALUE << RCC_PLLCFGR_PLLSRC_OFFSET);

    /* Enable PLLs */
    *RCC_CR_REGISTER = *RCC_CR_REGISTER | RCC_CR_PLLON;
    
    /* Wait for PLL lock */
    while((*RCC_CR_REGISTER & RCC_CR_PLLRDY) == 0);
}

/**
 * @brief Sets the system clock to be driven by PLL output.
 * 
 * @details Sets the system clock to be driven by PLL output.
 */
void bsp_clk_switch_to_pll(void)
{
    /* Set AHB, APB1 and APB2 prescaler values */
    *RCC_CFGR_REGISTER = *RCC_CFGR_REGISTER & 
                        ~(RCC_CFGR_HRPE_MASK  |
                          RCC_CFGR_PPRE1_MASK |
                          RCC_CFGR_PPRE2_MASK);
    *RCC_CFGR_REGISTER = *RCC_CFGR_REGISTER   | RCC_CFGR_HRPE_DIV1 | 
                          RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1;

    /* Set the system clock to use PLL as input */
    *RCC_CFGR_REGISTER = (*RCC_CFGR_REGISTER & ~RCC_CFGR_SW_MASK) | 
                        RCC_CFGR_SW_PLL;
    
    /* Wait for update */
    while((*RCC_CFGR_REGISTER & RCC_CFGR_SWS_MASK) != RCC_CFGR_SWS_PLL);
}

/**
 * @brief Get the PLL output frequency in MHz.
 * 
 * @details Reads the PLL registers and compute the current PLL output 
 * frequency. The frequency returned is expressed in MHz.
 * 
 * @return The PLL output frequency in MHz.
 */
static uint32_t bsp_clock_get_pll_freq(void)
{
    uint32_t pll_freq;

    /* Get Source clock */
    if((*RCC_PLLCFGR_REGISTER & RCC_PLLCFGR_PLLSRC_MASK) == 0)
    {
        pll_freq = RCC_HSI_BASE_FREQ;
    }
    else 
    {
        pll_freq = RCC_HSE_BASE_FREQ;
    }

    /* Get PLLM value */
    pll_freq /= (*RCC_PLLCFGR_REGISTER & RCC_PLLCFGR_PLLM_MASK) >> 
                 RCC_PLLCFGR_PLLM_OFFSET;
    /* Get PLLN value */
    pll_freq *= (*RCC_PLLCFGR_REGISTER & RCC_PLLCFGR_PLLN_MASK) >> 
                 RCC_PLLCFGR_PLLN_OFFSET;
    /* Get PLLP value */
    pll_freq /= (((*RCC_PLLCFGR_REGISTER & RCC_PLLCFGR_PLLP_MASK) >> 
                 RCC_PLLCFGR_PLLP_OFFSET) + 1) * 2;
    
    return pll_freq;
}

/*******************************************************************************
 * Public functions
 ******************************************************************************/


ERROR_CODE_E bsp_clk_gpio_enable(const GPIO_IDENTIFIER_E gpio_id)
{
    uint32_t reg_val;

    switch(gpio_id)
    {
        case GPIO_ID_A:
            reg_val = RCC_AHB1ENR_GPIOAEN;
            break;
        case GPIO_ID_B:
            reg_val = RCC_AHB1ENR_GPIOBEN;
            break;
        case GPIO_ID_C:
            reg_val = RCC_AHB1ENR_GPIOCEN;
            break;
        case GPIO_ID_D:
            reg_val = RCC_AHB1ENR_GPIODEN;
            break;
        case GPIO_ID_E:
            reg_val = RCC_AHB1ENR_GPIOEEN;
            break;
        case GPIO_ID_H:
            reg_val = RCC_AHB1ENR_GPIOHEN;
            break;
        default:
            reg_val = 0;
    }

    if(reg_val == 0)
    {
        KERNEL_LOG_ERROR("Wrong GPIO identifer", 
                         (void*)&gpio_id, 
                         sizeof(gpio_id), 
                         ERROR_INVALID_PARAM);
        return ERROR_INVALID_PARAM;
    }

    *RCC_AHB1ENR_REGISTER = *RCC_AHB1ENR_REGISTER | reg_val;
    while((*RCC_AHB1ENR_REGISTER & reg_val) == 0);

    KERNEL_LOG_INFO("GPIO clock enabled", 
                    (void*)&gpio_id, 
                    sizeof(gpio_id), 
                    NO_ERROR);

    return NO_ERROR;
}

ERROR_CODE_E bsp_clk_usart_enable(const USART_IDENTIFIER_E usart_id)
{
    ERROR_CODE_E error;

    error = NO_ERROR;

    /* Select the USART interface */
    switch(usart_id)
    {
        case USART_ID_1:
            *RCC_APB2ENR_REGISTER = *RCC_APB2ENR_REGISTER | 
                                     RCC_APB2ENR_USART1EN;
            while((*RCC_APB2ENR_REGISTER & RCC_APB2ENR_USART1EN) == 0);
            break;
        case USART_ID_2:
            *RCC_APB1ENR_REGISTER = *RCC_APB1ENR_REGISTER | 
                                     RCC_APB1ENR_USART2EN;
            while((*RCC_APB1ENR_REGISTER & RCC_APB1ENR_USART2EN) == 0);
            break;
        case USART_ID_6:
            *RCC_APB2ENR_REGISTER = *RCC_APB2ENR_REGISTER | 
                                     RCC_APB2ENR_USART6EN;
            while((*RCC_APB2ENR_REGISTER & RCC_APB2ENR_USART6EN) == 0);
            break;

        default:
            KERNEL_LOG_ERROR("Wrong USART identifer", 
                             (void*)&usart_id, 
                             sizeof(usart_id), 
                             ERROR_INVALID_PARAM);
            error = ERROR_INVALID_PARAM;
    }

    if(error == NO_ERROR)
    {
        KERNEL_LOG_INFO("USART clock enabled", 
                        (void*)&usart_id, 
                        sizeof(usart_id), 
                        NO_ERROR);
    }

    return error;
}

ERROR_CODE_E bsp_clk_sys_init(void)
{
    ERROR_CODE_E error;

    /* Check init state */
    if(bsp_clk_init != 0)
    {
        KERNEL_LOG_ERROR("System clock is already initialized", 
                         NULL, 
                         0, 
                         ERROR_ALREADY_INIT);
        return ERROR_ALREADY_INIT;
    }

    /* Enable the power interface clock and system clock controller */
    *RCC_APB1ENR_REGISTER = *RCC_APB1ENR_REGISTER | RCC_APB1ENR_PWREN;
    while((*RCC_APB1ENR_REGISTER & RCC_APB1ENR_PWREN) == 0);
    *RCC_APB2ENR_REGISTER = *RCC_APB2ENR_REGISTER | RCC_APB2ENR_SYSCFGEN;
    while((*RCC_APB2ENR_REGISTER & RCC_APB2ENR_SYSCFGEN) == 0);

    /* Update voltage scaling */
    error = bsp_pwr_set_scaling(POWER_SCALING_MODE_2);
    if(error != NO_ERROR)
    {
        return error;
    }
    
    /* Set flash latency */
    error = bsp_flash_set_latency(FLASH_LATENCY_WS_2);
    if(error != NO_ERROR)
    {
        return error;
    }

    /* Init systems clocks */
    bsp_clk_base_sys_init();
    bsp_clk_pll_init();
    bsp_clk_switch_to_pll();

    /* Init GPIO and USART clocks */
    error = bsp_clk_gpio_enable(GPIO_ID_A);
    if(error != NO_ERROR)
    {
        return error;
    }
    error = bsp_clk_usart_enable(USART_ID_2);
    if(error != NO_ERROR)
    {
        return error;
    }

    KERNEL_LOG_INFO("System clock initialized", 
                    NULL, 
                    0, 
                    NO_ERROR);

    /* Update init state */
    bsp_clk_init = 1;
    return NO_ERROR;
}

uint32_t bsp_clocks_get_freq(const CLOCK_IDENTIFIER_T clk_id)
{
    uint32_t sysclk;
    uint32_t factor;

    /* Get Source clock */
    if((*RCC_CFGR_REGISTER & RCC_CFGR_SWS_MASK) == RCC_CFGR_SWS_PLL)
    {
        sysclk = bsp_clock_get_pll_freq();
    }
    else if((*RCC_CFGR_REGISTER & RCC_CFGR_SWS_MASK) == RCC_CFGR_SWS_HSI)
    {
        sysclk = RCC_HSI_BASE_FREQ;
    }
    else if((*RCC_CFGR_REGISTER & RCC_CFGR_SWS_MASK) == RCC_CFGR_SWS_HSE)
    {
        sysclk = RCC_HSE_BASE_FREQ;
    }
    else 
    {
        /* We were  not able to detect the input clock */
        return 0;
    }

    /* Divide by AHB prescaler */
    if((*RCC_CFGR_REGISTER & RCC_CFGR_HPRE_EN) != 0)
    {
        factor = (*RCC_CFGR_REGISTER & RCC_CFGR_HPRE_VAL_MASK) >> 
                  RCC_CFGR_HRPE_OFFSET;
        sysclk /= (uint32_t)bsp_hpre_factor_lookup[factor];
    }

    if(clk_id == BSP_CLOCK_ID_HCLK || clk_id == BSP_CLOCK_ID_FCLK)
    {
        return sysclk;
    }
    else if(clk_id == BSP_CLOCK_ID_PCLK1 || clk_id == BSP_CLOCK_ID_APB1_TIMER)
    {
        /* Get the APB1 prescaler */
        if((*RCC_CFGR_REGISTER & RCC_CFGR_PPRE1_EN) != 0)
        {
            factor = (*RCC_CFGR_REGISTER & RCC_CFGR_PPRE1_VAL_MASK) >> 
                      RCC_CFGR_PPRE1_OFFSET;

            sysclk /= (uint32_t)bsp_ppre_factor_lookup[factor];

            if(clk_id == BSP_CLOCK_ID_APB1_TIMER)
            {
                sysclk *= 2;
            }
        }
    }
    else if(clk_id == BSP_CLOCK_ID_PCLK2 || clk_id == BSP_CLOCK_ID_APB2_TIMER)
    {
        /* Get the APB2 prescaler */
        if((*RCC_CFGR_REGISTER & RCC_CFGR_PPRE2_EN) != 0)
        {
            factor = (*RCC_CFGR_REGISTER & RCC_CFGR_PPRE2_VAL_MASK) >> 
                      RCC_CFGR_PPRE2_OFFSET;
            sysclk /= bsp_ppre_factor_lookup[factor];

            if(clk_id == BSP_CLOCK_ID_APB2_TIMER)
            {
                sysclk *= 2;
            }
        }
    }
    else 
    {
        sysclk = 0;
    }

    KERNEL_LOG_INFO("System clock frequency requested", 
                    (void*)&sysclk, 
                    sizeof(sysclk), 
                    NO_ERROR);
                    
    return sysclk;
}

ERROR_CODE_E bsp_get_cpu_freq(uint32_t* freq)
{
    *freq = bsp_clocks_get_freq(BSP_CLOCK_ID_HCLK);
    if(*freq == 0)
    {
        KERNEL_LOG_ERROR("System clock is not available", 
                         NULL, 
                         0, 
                         ERROR_NOT_AVAILABLE);
        return ERROR_NOT_AVAILABLE;
    }

    return NO_ERROR;
}