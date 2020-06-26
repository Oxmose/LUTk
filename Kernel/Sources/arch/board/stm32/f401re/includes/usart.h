/*******************************************************************************
 * @file usart.h
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

#ifndef __BOARD_STM32F401RE_USART_H__
#define __BOARD_STM32F401RE_USART_H__

#include "error_types.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

#define USART2_REG_BASE_ADDRESS 0x40004400

#define USART2_SR_ADDRESS   (USART2_REG_BASE_ADDRESS)
#define USART2_DR_ADDRESS   (USART2_REG_BASE_ADDRESS + 0x04)
#define USART2_BRR_ADDRESS  (USART2_REG_BASE_ADDRESS + 0x08)
#define USART2_CR1_ADDRESS  (USART2_REG_BASE_ADDRESS + 0x0C)
#define USART2_CR2_ADDRESS  (USART2_REG_BASE_ADDRESS + 0x10)
#define USART2_CR3_ADDRESS  (USART2_REG_BASE_ADDRESS + 0x14)
#define USART2_GTPR_ADDRESS (USART2_REG_BASE_ADDRESS + 0x18)

#define USART_SR_RESET_VALUE 0x00C00000

#define USART_CR1_UE 0x00002000
#define USART_CR1_TE 0x00000008


/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

/**
 * @brief Initializes and enables the USART.
 *
 * @details Initializes and enables the USART. The serial settings defined in
 * the global configuration file are used to set the UART.
 *
 * @return The function returns NO_ERROR on succes, otherwise kernel error code 
 * is returned.
 */
ERROR_CODE_E usart_init(void);

#endif /* #ifndef __BOARD_STM32F401RE_USART_H__ */