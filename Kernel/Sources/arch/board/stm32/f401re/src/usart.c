/*******************************************************************************
 * @file usart.c
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 24/06/2020
 *
 * @version 1.0
 *
 * @brief STM32-F401RE USART driver.
 *
 * @details STM32-F401RE USART driver. This module contains the routines used
 * to ineract with and configure the USART. 
 * 
 * @warning The module is developped to use the USART2.
 ******************************************************************************/

#include "config.h"
#include "error_types.h"
#include "stdint.h"
#include "usart.h"

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/**
 * @brief Returns the baudrate register value corresponding to the baudrate
 * given as parameter.
 * 
 * @details Returns the baudrate register value corresponding to the baudrate
 * given as parameter. The returned value is the divider register value to set
 * to obtain the desired baudrate. If the baudrate is not supported, 0 is 
 * returned. 
 * 
 * @param[in] baudrate The baudrate to get divider value of.
 *
 * @return The returned value is the divider register value to set
 * to obtain the desired baudrate. If the baudrate is not supported, 0 is 
 * returned. 
 */
static uint32_t get_baudrate(const uint32_t baudrate)
{
    return baudrate;
#if 0
    uint32_t divider;
    uint32_t clock;
    uint32_t over8;

    /* Get the oversampling configuration */
    over8 = (*((uint32_t*)(USART2_CR1_ADDRESS))) >> USART_CR1_OVER8_OFFSET;

    switch (baudrate)
    {
        case 50:
            return 0;
        case 75:
            return 0;
        case 150:
            return 0;
        case 300:
            return 0;
        case 600:
            return 0;
        case 1200:
            return 0;
        case 1800:
            return 0;
        case 2400:
            return 0;
        case 4800:
            return 0;
        case 7200:
            return 0;
        case 9600:
            return 0;
        case 14400:
            return 0;
        case 19200:
            return 0;
        case 38400:
            return 0;
        case 57600:
            return 0;
        case 115200:
            return 0;
        default:
            return 0;
    }
#endif
}

/*******************************************************************************
 * Public functions
 ******************************************************************************/

ERROR_CODE_E usart_init(void)
{
    volatile uint32_t* current_reg;
    uint32_t baudrate;

    /* Reset status register */
    current_reg = (volatile uint32_t*)USART2_SR_ADDRESS;
    *current_reg = USART_SR_RESET_VALUE;

    /* Set the CR1 register */
    current_reg = (volatile uint32_t*)USART2_CR1_ADDRESS;
    *current_reg = USART_CR1_UE | USART_CR1_TE; 

    /* Set the CR2 register */

    /* Set the baud rate */
    baudrate = get_baudrate(0x683);
    if(baudrate == 0)
    {
        /* TODO: Log error */
        return ERROR_INVALID_PARAM;
    }
    current_reg = (volatile uint32_t*)USART2_BRR_ADDRESS;
    *current_reg = baudrate;

    

    current_reg = (volatile uint32_t*)USART2_DR_ADDRESS;
    *current_reg = 'A';

    return NO_ERROR;
}