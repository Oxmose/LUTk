/*******************************************************************************
 * @file bsp_usart.h
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
 * to interact with and configure the USART.
 *
 * @warning The module is developped to use the USART2.
 ******************************************************************************/

#ifndef __BOARD_STM32F401RE_BSP_USART_H__
#define __BOARD_STM32F401RE_BSP_USART_H__

#include "error_types.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/** @brief USART1 Status register address. */
#define USART1_SR_ADDRESS  0x40011000
/** @brief USART1 Data register address. */
#define USART1_DR_ADDRESS  0x40011004
/** @brief USART1 Baudrate register address. */
#define USART1_BRR_ADDRESS 0x40011008
/** @brief USART1 Control register 1 address. */
#define USART1_CR1_ADDRESS 0x4001100C
#define USART1_CR1_REGISTER ((volatile uint32_t*)USART1_CR1_ADDRESS)
/** @brief USART1 Control register 2 address. */
#define USART1_CR2_ADDRESS 0x40011010
/** @brief USART1 Control register 3 address. */
#define USART1_CR3_ADDRESS 0x40011014

/** @brief USART2 Status register address. */
#define USART2_SR_ADDRESS  0x40004400 
#define USART2_SR_REGISTER ((volatile uint32_t*)USART2_SR_ADDRESS)
/** @brief USART2 Data register address. */
#define USART2_DR_ADDRESS  0x40004404 
#define USART2_DR_REGISTER ((volatile uint32_t*)USART2_DR_ADDRESS)
/** @brief USART2 Baudrate register address. */
#define USART2_BRR_ADDRESS 0x40004408
/** @brief USART2 Control register 1 address. */
#define USART2_CR1_ADDRESS 0x4000440C 
#define USART2_CR1_REGISTER ((volatile uint32_t*)USART2_CR1_ADDRESS)
/** @brief USART2 Control register 2 address. */
#define USART2_CR2_ADDRESS 0x40004410
/** @brief USART2 Control register 3 address. */
#define USART2_CR3_ADDRESS 0x40004414

/** @brief USART6 Status register address. */
#define USART6_SR_ADDRESS  0x40011400
/** @brief USART6 Data register address. */
#define USART6_DR_ADDRESS  0x40011404
/** @brief USART6 Baudrate register address. */
#define USART6_BRR_ADDRESS 0x40011408
/** @brief USART6 Control register 1 address. */
#define USART6_CR1_ADDRESS 0x4001140C
#define USART6_CR1_REGISTER ((volatile uint32_t*)USART6_CR1_ADDRESS)
/** @brief USART6 Control register 2 address. */
#define USART6_CR2_ADDRESS 0x40011410
/** @brief USART6 Control register 3 address. */
#define USART6_CR3_ADDRESS 0x40011414

/** @brief USART status register transmission ready flag. */
#define USART_SR_TXE     0x00000080    

/** @brief USART control register 1 oversampling by 8 flag. */
#define USART_CR1_OVER8  0x00008000
/** @brief USART control register 1 usart enable flag. */
#define USART_CR1_UE     0x00002000
/** @brief USART control register 1 word length flag. */
#define USART_CR1_M      0x00001000
/** @brief USART control register 1 wakeup flag. */
#define USART_CR1_WAKE   0x00000800
/** @brief USART control register 1 parity control flag. */
#define USART_CR1_PCE    0x00000400
/** @brief USART control register 1 parity type flag. */
#define USART_CR1_PS     0x00000200
/** @brief USART control register 1 PE interrupt enable flag. */
#define USART_CR1_PEIE   0x00000100
/** @brief USART control register 1 TXE interrupt enable flag. */
#define USART_CR1_TXEIE  0x00000080
/** @brief USART control register 1 TX complete interrupt enable flag. */
#define USART_CR1_TCIE   0x00000040
/** @brief USART control register 1 RXNE interrupt enable flag. */
#define USART_CR1_RXNEIE 0x00000020
/** @brief USART control register 1 IDLE interrupt enable flag. */
#define USART_CR1_IDLEIE 0x00000010
/** @brief USART control register 1 transmiter enable flag. */
#define USART_CR1_TE     0x00000008
/** @brief USART control register 1 receiver enable flag. */
#define USART_CR1_RE     0x00000004
/** @brief USART control register 1 receiver wakeup flag. */
#define USART_CR1_RWU    0x00000002
/** @brief USART control register 1 send break flag. */
#define USART_CR1_SBK    0x00000001

/** @brief USART control register 2 LIN mode enable flag. */
#define USART_CR2_LINEN   0x00004000
/** @brief USART control register 2 0.5 stop bit field. */
#define USART_CR2_STOP_05 0x00001000
/** @brief USART control register 2 1 stop bit field. */
#define USART_CR2_STOP_1  0x00000000
/** @brief USART control register 2 1.5 stop bits field. */
#define USART_CR2_STOP_15 0x00003000    
/** @brief USART control register 2 2 stop bits field. */
#define USART_CR2_STOP_2  0x00002000
/** @brief USART control register 2 clock enable flag. */
#define USART_CR2_CLKEN   0x00000800
/** @brief USART control register 2 clock polarity flag. */
#define USART_CR2_CPOL    0x00000400
/** @brief USART control register 2 clock phase flag. */
#define USART_CR2_CPHA    0x00000200
/** @brief USART control register 2 last bit clock pulse flag. */
#define USART_CR2_LBCL    0x00000100   
/** @brief USART control register 2 LIN break detect interrupt enable flag. */
#define USART_CR2_LBIE    0x00000040  
/** @brief USART control register 2 LIN break detect length flag. */
#define USART_CR2_LBL     0x00000020

/** @brief USART control register 2 stop bits field mask. */
#define USART_CR2_STOP_MASK 0x00003000
/** @brief USART control register 2 address field mask. */
#define USART_CR2_ADDR_MASK 0x0000000F

/** @brief USART control register 3 one sample bit method enable flag. */
#define USART_CR3_ONEBIT 0x00000800
/** @brief USART control register 3 CTS interrupt enable flag. */
#define USART_CR3_CTSIE  0x00000400
/** @brief USART control register 3 CTS enable flag. */
#define USART_CR3_CTSE   0x00000200
/** @brief USART control register 3 RTS enable flag. */
#define USART_CR3_RTSE   0x00000100
/** @brief USART control register 3 DMA transmitter enable flag. */
#define USART_CR3_DMAT   0x00000080
/** @brief USART control register 3 DMA receiver enable flag. */
#define USART_CR3_DMAR   0x00000040
/** @brief USART control register 3 smartcard mode enable flag. */
#define USART_CR3_SCEN   0x00000020
/** @brief USART control register 3 smartcard NACK enable flag. */
#define USART_CR3_NACK   0x00000010
/** @brief USART control register 3 half duplex selection flag. */
#define USART_CR3_HDSEL  0x00000008
/** @brief USART control register 3 IrDA low power flag. */
#define USART_CR3_IRLP   0x00000004
/** @brief USART control register 3 IrDA enable flag. */
#define USART_CR3_IREN   0x00000002
/** @brief USART control register 3 error interrupt enable flag. */
#define USART_CR3_EIE    0x00000001

/** @brief BRR divider mantissa field offset. */
#define USART_BRR_DIV_MANT_OFFSET 4

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/
/** @brief USART identifier used to differenciated the USARTs present on the 
 * STM32F401RE board.
 */
enum USART_IDENTIFIER
{
    /** @brief USART 1 identifier. */
    USART_ID_1 = 0,
    /** @brief USART 2 identifier. */
    USART_ID_2 = 1,
    /** @brief USART 6 identifier. */
    USART_ID_6 = 3,
};

/** @brief Short hand for enum USART_IDENTIFIER. */
typedef enum USART_IDENTIFIER USART_IDENTIFIER_E;

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

#endif /* #ifndef __BOARD_STM32F401RE_BSP_USART_H__ */