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
 * to interact with and configure the USART. 
 * 
 * @warning The module is developped to use the USART2.
 ******************************************************************************/

#include "error_types.h"
#include "bsp_usart.h"
#include "bsp_clocks.h"
#include "serial.h"
#include "config.h"
#include "stddef.h"
#include "logger.h"

/*******************************************************************************
 * Private Data
 ******************************************************************************/

/** @brief Current usart initialization state. */
uint8_t usart_init_state = 0;

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/**
 * @brief Checks the baudrate setting conformity.
 * 
 * @details This macro will return from the function it is used in if an error
 * is detected. An error message will be logged and an invalid parameter error
 * is returned.
 * 
 * @param[in] baudrate The baudrate settings for the serial line.
 */
#define CHECK_BAUDRATE(baudrate)                            \
({                                                          \
    switch(baudrate)                                        \
    {                                                       \
        case 1200:                                          \
        case 2400:                                          \
        case 9600:                                          \
        case 19200:                                         \
        case 38400:                                         \
        case 57600:                                         \
        case 115200:                                        \
        case 256000:                                        \
        case 460800:                                        \
        case 921600:                                        \
        case 1843200:                                       \
            break;                                          \
        default:                                            \
            if(KERNEL_LOG_LEVEL == ERROR_LOG_LEVEL)         \
            {                                               \
                KERNEL_LOG_ERROR("Invalid USART baudrate",  \
                                 (void*)&baudrate,          \
                                 sizeof(baudrate),          \
                                 ERROR_INVALID_PARAM);      \
            }                                               \
                                                            \
            return ERROR_INVALID_PARAM;                     \
                                                            \
    }                                                       \
})

/**
 * @brief Checks the word length setting conformity.
 * 
 * @details This macro will return from the function it is used in if an error
 * is detected. An error message will be logged and an invalid parameter error
 * is returned.
 * 
 * @param[in] wdlength The word length settings for the serial line.
 */
#define CHECK_WDLENGTH(wdlength)                               \
({                                                             \
    switch(wdlength)                                           \
    {                                                          \
        case 8:                                                \
        case 9:                                                \
            break;                                             \
        default:                                               \
            if(KERNEL_LOG_LEVEL == ERROR_LOG_LEVEL)            \
            {                                                  \
                KERNEL_LOG_ERROR("Invalid USART word length",  \
                                 (void*)&wdlength,             \
                                 sizeof(wdlength),             \
                                 ERROR_INVALID_PARAM);         \
            }                                                  \
                                                               \
            return ERROR_INVALID_PARAM;                        \
                                                               \
    }                                                          \
})

/**
 * @brief Checks the stop bits setting conformity.
 * 
 * @details This macro will return from the function it is used in if an error
 * is detected. An error message will be logged and an invalid parameter error
 * is returned.
 * 
 * @param[in] stpbits The stop bits settings for the serial line.
 */
#define CHECK_STOPBITS(stpbits)                                \
({                                                             \
    switch(stpbits)                                            \
    {                                                          \
        case SERIAL_STOP_BITS_05:                              \
        case SERIAL_STOP_BITS_1:                               \
        case SERIAL_STOP_BITS_15:                              \
        case SERIAL_STOP_BITS_2:                               \
            break;                                             \
        default:                                               \
            if(KERNEL_LOG_LEVEL == ERROR_LOG_LEVEL)            \
            {                                                  \
                KERNEL_LOG_ERROR("Invalid USART stop bits",    \
                                 (void*)&stpbits,              \
                                 sizeof(stpbits),              \
                                 ERROR_INVALID_PARAM);         \
            }                                                  \
                                                               \
            return ERROR_INVALID_PARAM;                        \
                                                               \
    }                                                          \
})

/**
 * @brief Checks the parity setting conformity.
 * 
 * @details This macro will return from the function it is used in if an error
 * is detected. An error message will be logged and an invalid parameter error
 * is returned.
 * 
 * @param[in] parity The parity settings for the serial line.
 */
#define CHECK_PARITYVA(parity)                                 \
({                                                             \
    switch(parity)                                             \
    {                                                          \
        case SERIAL_PARITY_NONE:                               \
        case SERIAL_PARITY_EVEN:                               \
        case SERIAL_PARITY_ODD:                                \
            break;                                             \
        default:                                               \
            if(KERNEL_LOG_LEVEL == ERROR_LOG_LEVEL)            \
            {                                                  \
                KERNEL_LOG_ERROR("Invalid USART partity mode", \
                                 (void*)&parity,               \
                                 sizeof(parity),               \
                                 ERROR_INVALID_PARAM);         \
            }                                                  \
                                                               \
            return ERROR_INVALID_PARAM;                        \
                                                               \
    }                                                          \
})

/**
 * @brief Checks the flow control setting conformity.
 * 
 * @details This macro will return from the function it is used in if an error
 * is detected. An error message will be logged and an invalid parameter error
 * is returned.
 * 
 * @param[in] ctrlflow The flow control for the serial line.
 */
#define CHECK_CTRLFLOW(ctrlflow)                               \
({                                                             \
    switch(ctrlflow)                                           \
    {                                                          \
        case SERIAL_CTRL_FLOW_NONE:                            \
        case SERIAL_CTRL_FLOW_CTS:                             \
        case SERIAL_CTRL_FLOW_RTS:                             \
        case SERIAL_CTRL_FLOW_CTS_RTS:                         \
            break;                                             \
        default:                                               \
            if(KERNEL_LOG_LEVEL == ERROR_LOG_LEVEL)            \
            {                                                  \
                KERNEL_LOG_ERROR("Invalid USART control flow", \
                                 (void*)&ctrlflow,             \
                                 sizeof(ctrlflow),             \
                                 ERROR_INVALID_PARAM);         \
            }                                                  \
                                                               \
            return ERROR_INVALID_PARAM;                        \
                                                               \
    }                                                          \
})

/** 
 * @brief Compute the BRR bivider mantissa for a 16 bit oversampling.
 * 
 * @param[in] f The serial input clock frequency.
 * @param[in] b The required baudrate for the serial line.
 * 
 * @return The BRR mantissa is returned.
 */ 
#define USART_GET_BRR_DIV_MANT_16(f, b)                           \
        ((uint64_t)f / ((uint64_t)16 * (uint64_t)b))

/** 
 * @brief Compute the BRR bivider fraction for a 16 bit oversampling.
 * 
 * @param[in] f The serial input clock frequency.
 * @param[in] b The required baudrate for the serial line.
 * 
 * @return The BRR fraction is returned.
 */     
#define USART_GET_BRR_DIV_FRAQ_16(f, b)                           \
        (((((uint64_t)f * 100 / ((uint64_t)16 * (uint64_t)b)) -   \
        (USART_GET_BRR_DIV_MANT_16(f, b) * 100)) * 16 + 50) / 100)

/**
 * @brief Initializes the USART as UART.
 * 
 * @details Initializes the USART as UART with the corresponding settings
 * given as parameter.
 * 
 * @param[in] usart_id The identifier of the USART to initialize.
 * @param[in] settings The settings structure to use to initialize the UART.
 */
void bsp_uart_init(const USART_IDENTIFIER_E usart_id, 
                    const SERIAL_SETTINGS_T* settings)
{
    volatile uint32_t* cr1;
    volatile uint32_t* cr2;
    volatile uint32_t* cr3;
    volatile uint32_t* brr;

    uint32_t freq;

    switch(usart_id)
    {
        case USART_ID_1:
            cr1 = (volatile uint32_t*)USART1_CR1_ADDRESS;
            cr2 = (volatile uint32_t*)USART1_CR2_ADDRESS;
            cr3 = (volatile uint32_t*)USART1_CR3_ADDRESS;
            brr = (volatile uint32_t*)USART1_BRR_ADDRESS;
            break;
        case USART_ID_2:
            cr1 = (volatile uint32_t*)USART2_CR1_ADDRESS;
            cr2 = (volatile uint32_t*)USART2_CR2_ADDRESS;
            cr3 = (volatile uint32_t*)USART2_CR3_ADDRESS;
            brr = (volatile uint32_t*)USART2_BRR_ADDRESS;
            break;
        case USART_ID_6:
            cr1 = (volatile uint32_t*)USART6_CR1_ADDRESS;
            cr2 = (volatile uint32_t*)USART6_CR2_ADDRESS;
            cr3 = (volatile uint32_t*)USART6_CR3_ADDRESS;
            brr = (volatile uint32_t*)USART6_BRR_ADDRESS;
            break;
        default:
            return;
    }

    /* Set CR1 register */
    *cr1 = *cr1 & ~(USART_CR1_OVER8  | USART_CR1_M      | 
                    USART_CR1_WAKE   | USART_CR1_PCE    |
                    USART_CR1_PS     | USART_CR1_PEIE   | 
                    USART_CR1_TXEIE  | USART_CR1_TCIE   | 
                    USART_CR1_RXNEIE | USART_CR1_IDLEIE | 
                    USART_CR1_TE     | USART_CR1_RE     |
                    USART_CR1_RWU    | USART_CR1_SBK);

    *cr1 = *cr1 | 
           (settings->word_length == 8 ? 0 : USART_CR1_M) |
           ((settings->partity == SERIAL_PARITY_EVEN) || 
            (settings->partity == SERIAL_PARITY_NONE) ? 0 : USART_CR1_PS) |
           (settings->partity == SERIAL_PARITY_NONE   ? 0 : USART_CR1_PCE) |
           USART_CR1_TE | USART_CR1_RE;

    /* Set CR2 register */
    *cr2 = *cr2 & ~(USART_CR2_LINEN     | USART_CR2_STOP_MASK | 
                    USART_CR2_CLKEN     | USART_CR2_CPOL      |
                    USART_CR2_CPHA      | USART_CR2_LBCL      | 
                    USART_CR2_LBIE      | USART_CR2_LBL       | 
                    USART_CR2_ADDR_MASK);

    switch(settings->stop_bits)
    {
        case SERIAL_STOP_BITS_05:
            *cr2 = *cr2 | USART_CR2_STOP_05;
            break;
        case SERIAL_STOP_BITS_15:
            *cr2 = *cr2 | USART_CR2_STOP_15;
            break;
        case SERIAL_STOP_BITS_2:
            *cr2 = *cr2 | USART_CR2_STOP_2;
            break;
        case SERIAL_STOP_BITS_1:
        default:
            break;
    }

    /* Set CR3 register */
    *cr3 = *cr3 & ~(USART_CR3_ONEBIT | USART_CR3_CTSIE | 
                    USART_CR3_CTSE   | USART_CR3_RTSE  |
                    USART_CR3_DMAT   | USART_CR3_DMAR  | 
                    USART_CR3_SCEN   | USART_CR3_NACK  | 
                    USART_CR3_HDSEL  | USART_CR3_IRLP  |
                    USART_CR3_IREN   | USART_CR3_EIE);

    switch(settings->ctrl_flow)
    {
        case SERIAL_CTRL_FLOW_CTS:
            *cr3 = *cr3 | USART_CR3_CTSE;
            break;
        case SERIAL_CTRL_FLOW_RTS:
            *cr3 = *cr3 | USART_CR3_RTSE;
            break;
        case SERIAL_CTRL_FLOW_CTS_RTS:
            *cr3 = *cr3 | USART_CR3_CTSE | USART_CR3_RTSE;
            break;
        case SERIAL_STOP_BITS_1:
        default:
            break;
    }


    /* Set BRR register */
    if(usart_id == USART_ID_1 || usart_id == USART_ID_6)
    {
        freq = bsp_clocks_get_freq(BSP_CLOCK_ID_PCLK2);
    }
    else 
    {
        freq = bsp_clocks_get_freq(BSP_CLOCK_ID_PCLK1);
    }

    uint32_t mantissa = USART_GET_BRR_DIV_MANT_16(freq, settings->baudrate);
    uint32_t fraq = USART_GET_BRR_DIV_FRAQ_16(freq, settings->baudrate);

    (void)fraq;
    (void)mantissa;

    *brr = (USART_GET_BRR_DIV_MANT_16(freq, settings->baudrate) << 
            USART_BRR_DIV_MANT_OFFSET) |
            USART_GET_BRR_DIV_FRAQ_16(freq, settings->baudrate);
}

/**
 * @brief Disables the USART.
 * 
 * @brief Disables the USART refered by the USART identifier given as parameter.
 * 
 * @param[in] usart_id The identifier of the USART to disable.
 */
void bsp_usart_disable(const USART_IDENTIFIER_E usart_id)
{
    switch(usart_id)
    {
        case USART_ID_1:
            *USART1_CR1_REGISTER = *USART1_CR1_REGISTER & ~USART_CR1_UE;
            break;
        case USART_ID_2:
            *USART2_CR1_REGISTER = *USART2_CR1_REGISTER & ~USART_CR1_UE;
            break;
        case USART_ID_6:
            *USART6_CR1_REGISTER = *USART6_CR1_REGISTER & ~USART_CR1_UE;
            break;
        default:
            return;
    }
}

/**
 * @brief Enables the USART.
 * 
 * @brief Enables the USART refered by the USART identifier given as parameter.
 * 
 * @param[in] usart_id The identifier of the USART to enable.
 */
void bsp_usart_enable(const USART_IDENTIFIER_E usart_id)
{
    switch(usart_id)
    {
        case USART_ID_1:
            *USART1_CR1_REGISTER = *USART1_CR1_REGISTER | USART_CR1_UE;
            break;
        case USART_ID_2:
            *USART2_CR1_REGISTER = *USART2_CR1_REGISTER | USART_CR1_UE;
            break;
        case USART_ID_6:
            *USART6_CR1_REGISTER = *USART6_CR1_REGISTER | USART_CR1_UE;
            break;
        default:
            return;
    }
}

/*******************************************************************************
 * Public functions
 ******************************************************************************/

ERROR_CODE_E serial_init(const SERIAL_SETTINGS_T* settings)
{
    /**
     * This function uses USART2 as main UART output.
     */

    GPIO_SETTINGS_T gpio_settings;
    ERROR_CODE_E    error;

    if(usart_init_state != 0)
    {
        KERNEL_LOG_ERROR("Serial already initialized", 
                         NULL, 
                         0, 
                         ERROR_ALREADY_INIT);      
        return ERROR_ALREADY_INIT;
    }

    /* Check parameters */
    if(settings == NULL)
    {
        KERNEL_LOG_ERROR("Serial settings structure is NULL", 
                         NULL, 
                         0, 
                         ERROR_NULL_POINTER);
        return ERROR_NULL_POINTER;
    }
    CHECK_BAUDRATE(settings->baudrate);
    CHECK_WDLENGTH(settings->word_length);
    CHECK_STOPBITS(settings->stop_bits);
    CHECK_PARITYVA(settings->partity);
    CHECK_CTRLFLOW(settings->ctrl_flow);

    /* Init GPIO and USART clock */
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

    /* Initialize the USART2 GPIO A */
    gpio_settings.io_pin      = GPIO_PIN_2 | 
                                GPIO_PIN_3;
    gpio_settings.io_modetype = GPIO_MODE_ALTFUN   | 
                                GPIO_TYPE_PUSHPULL | 
                                GPIO_PUPD_NONE;
    gpio_settings.io_altfunc  = GPIO_ALFUNC_7;
    gpio_settings.io_speed    = GPIO_SPEED_VERY_HIGH;

    error = bsp_gpio_init(GPIO_ID_A, &gpio_settings);
    if(error != NO_ERROR)
    {
        return error;
    }

    /* Make sure USART2 is disabled */
    bsp_usart_disable(USART_ID_2);

    /* Set USART2 settings */
    bsp_uart_init(USART_ID_2, settings);

    /* Enable USART2 */
    bsp_usart_enable(USART_ID_2);

    KERNEL_LOG_INFO("USART initialized", 
                     NULL, 
                     0, 
                     NO_ERROR);

    usart_init_state = 1;
    return NO_ERROR;
}

ERROR_CODE_E serial_write(const char* str, const size_t length)
{
    size_t i;

    if(usart_init_state == 0)
    {    
        return ERROR_ALREADY_INIT;
    }

    for(i = 0; i < length; ++i)
    {
        /* Wait for serial line to be ready to transmit */
        while((*USART2_SR_REGISTER & USART_SR_TXE) == 0);

        *USART2_DR_REGISTER = *str++;
    }

    return NO_ERROR;
}