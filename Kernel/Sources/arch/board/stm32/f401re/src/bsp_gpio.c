/*******************************************************************************
 * @file bsp_gpio.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief STM32 F401RE BSP GPIO management.
 *
 * @details STM32 F401RE BSP GPIO management. This module contains the 
 * routines used to manage the GPIO present on the board
 ******************************************************************************/

#include "error_types.h"
#include "bsp_gpio.h"
#include "stdint.h"
#include "config.h"
#include "stddef.h"
#include "logger.h"

/*******************************************************************************
 * Private Data
 ******************************************************************************/

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/**
 * @brief Checks the mode and type field conformity.
 * 
 * @details This macro will return from the function it is used in if an error
 * is detected. An error message will be logged and an invalid parameter error
 * is returned.
 * 
 * @param[in] modetype The mode and type of the GPIO settings.
 */
#define CHECK_MODETYPE(modetype)                                                \
({                                                                              \
    uint32_t value = modetype & GPIO_MODE_MASK;                                 \
    if(value != GPIO_MODE_ANALOG && value != GPIO_MODE_ALTFUN &&                \
       value != GPIO_MODE_OUTPUT && value != GPIO_MODE_INPUT)                   \
    {                                                                           \
        if(KERNEL_LOG_LEVEL == ERROR_LOG_LEVEL)                                 \
        {                                                                       \
            KERNEL_LOG_ERROR("Invalid GPIO mode/type",                          \
                             (void*)&modetype,                                  \
                             sizeof(modetype),                                  \
                             ERROR_INVALID_PARAM);                              \
        }                                                                       \
                                                                                \
        return ERROR_INVALID_PARAM;                                             \
    }                                                                           \
    value = modetype & GPIO_TYPE_MASK;                                          \
    if(value != GPIO_TYPE_OPENDRAIN && value != GPIO_TYPE_PUSHPULL)             \
    {                                                                           \
        if(KERNEL_LOG_LEVEL == ERROR_LOG_LEVEL)                                 \
        {                                                                       \
            KERNEL_LOG_ERROR("Invalid GPIO mode/type",                          \
                             (void*)&modetype,                                  \
                             sizeof(modetype),                                  \
                             ERROR_INVALID_PARAM);                              \
        }                                                                       \
                                                                                \
        return ERROR_INVALID_PARAM;                                             \
    }                                                                           \
    value = modetype & GPIO_PUPD_MASK;                                          \
    if(value != GPIO_PUPD_PD && value != GPIO_PUPD_PU &&                        \
       value != GPIO_PUPD_NONE)                                                 \
    {                                                                           \
        if(KERNEL_LOG_LEVEL == ERROR_LOG_LEVEL)                                 \
        {                                                                       \
            KERNEL_LOG_ERROR("Invalid GPIO mode/type",                          \
                             (void*)&modetype,                                  \
                             sizeof(modetype),                                  \
                             ERROR_INVALID_PARAM);                              \
        }                                                                       \
                                                                                \
        return ERROR_INVALID_PARAM;                                             \
    }                                                                           \
})

/**
 * @brief Checks the speed field conformity.
 * 
 * @details This macro will return from the function it is used in if an error
 * is detected. An error message will be logged and an invalid parameter error
 * is returned.
 * 
 * @param[in] speed The speed of the GPIO settings.
 */
#define CHECK_SPEED(speed)                                                   \
({                                                                           \
    if(speed > GPIO_SPEED_VERY_HIGH)                                         \
    {                                                                        \
        if(KERNEL_LOG_LEVEL == ERROR_LOG_LEVEL)                              \
        {                                                                    \
            KERNEL_LOG_ERROR("Invalid GPIO speed",                           \
                             (void*)&speed,                                  \
                             sizeof(speed),                                  \
                             ERROR_INVALID_PARAM);                           \
        }                                                                    \
                                                                             \
        return ERROR_INVALID_PARAM;                                          \
    }                                                                        \
})

/**
 * @brief Checks the alternate function field conformity.
 * 
 * @details This macro will return from the function it is used in if an error
 * is detected. An error message will be logged and an invalid parameter error
 * is returned.
 * 
 * @param[in] altfunc The alternate function of the GPIO settings.
 */
#define CHECK_ALTFUNC(altfunc)                                               \
({                                                                           \
    if(altfunc > GPIO_ALFUNC_15)                                             \
    {                                                                        \
        if(KERNEL_LOG_LEVEL == ERROR_LOG_LEVEL)                              \
        {                                                                    \
            KERNEL_LOG_ERROR("Invalid GPIO alternative function",            \
                             (void*)&altfunc,                                \
                             sizeof(altfunc),                                \
                             ERROR_INVALID_PARAM);                           \
        }                                                                    \
                                                                             \
        return ERROR_INVALID_PARAM;                                          \
    }                                                                        \
})

/** 
 * @brief Computes the register address for a given GPIO register.
 * 
 * @param[in] gpio The identifier of the GPIO for wich we request the address.
 * @param[in] offset The GPIO register address offset.
 * 
 * @return The register absolute address is computed.
 */
#define GPIO_X_REGISTER(gpio, offset)                                      \
        ((volatile uint32_t*)(GPIO_X_BASE_ADDRESS + 0x400 * gpio + offset))

/** 
 * @brief computed the output type field mask for a given GPIO pin.
 * 
 * @param[in] pin The pin number for wich we compute the output type field mask.
 * 
 * @return The output type field mask is computed.
 */
#define GPIO_OTYPER_MASK(pin)  (1 << pin)

/** 
 * @brief computed the output speed field mask for a given GPIO pin.
 * 
 * @param[in] pin The pin number for wich we compute the output speed field mask.
 * 
 * @return The output speed field mask is computed.
 */
#define GPIO_OSPEEDR_MASK(pin) (1 << (pin << 1))
/** 
 * @brief computed the AFR field mask for a given GPIO pin.
 * 
 * @param[in] pin The pin number for wich we compute the AFR field mask.
 * 
 * @return The AFR field mask is computed.
 */
#define GPIO_AFR_MASK(pin)     (1 << (pin << 2))
/** 
 * @brief computed the mode field mask for a given GPIO pin.
 * 
 * @param[in] pin The pin number for wich we compute the mode field mask.
 * 
 * @return The mode field mask is computed.
 */
#define GPIO_MODER_MASK(pin)   (1 << (pin << 1))
/** 
 * @brief computed the PUPD field mask for a given GPIO pin.
 * 
 * @param[in] pin The pin number for wich we compute the PUPD field mask.
 * 
 * @return The PUPD field mask is computed.
 */
#define GPIO_PUPDR_MASK(pin)   (1 << (pin << 1))

/*******************************************************************************
 * Public functions
 ******************************************************************************/

ERROR_CODE_E bsp_gpio_init(const GPIO_IDENTIFIER_E gpio_id, 
                           const GPIO_SETTINGS_T* settings)
{
    volatile uint32_t* current_reg;

    uint8_t  i;

    /* Check parameters */
    if(settings == NULL)
    {
        KERNEL_LOG_ERROR("GPIO settings structure is NULL", 
                         NULL, 
                         0, 
                         ERROR_NULL_POINTER);
        return ERROR_NULL_POINTER;
    }
    CHECK_MODETYPE(settings->io_modetype);
    CHECK_SPEED(settings->io_speed);
    CHECK_ALTFUNC(settings->io_altfunc);
    
    /* Check which pin is to be configured */
    for(i = 0; i < GPIO_PIN_COUNT; ++i)
    {
        /* The pin is set to be configured */
        if(((1 << i) & settings->io_pin) != 0)
        {
            if((settings->io_modetype & GPIO_MODE_MASK) == GPIO_MODE_OUTPUT ||
               (settings->io_modetype & GPIO_MODE_MASK) == GPIO_MODE_ALTFUN)
            {
                /* Set IO output type */
                current_reg = GPIO_X_REGISTER(gpio_id, GPIO_OTYPER_OFFSET);    
                *current_reg = (*current_reg & ~GPIO_OTYPER_MASK(i)) |
                                (((settings->io_modetype & GPIO_MODE_MASK)
                                    >> GPIO_MODE_OFFSET)
                                    << i);
                /* Set IO output speed */
                current_reg = GPIO_X_REGISTER(gpio_id, GPIO_OSPEEDR_OFFSET);
                *current_reg = (*current_reg & ~GPIO_OSPEEDR_MASK(i)) |
                                (settings->io_speed << (i * 2));
            }

            if((settings->io_modetype & GPIO_MODE_MASK) == GPIO_MODE_ALTFUN)
            {
                /* Set the alternate function */
                if(i > 7)
                {
                    current_reg = GPIO_X_REGISTER(gpio_id, GPIO_AFRH_OFFSET);
                }
                else
                {
                    current_reg = GPIO_X_REGISTER(gpio_id, GPIO_AFRL_OFFSET);
                }

                *current_reg = (*current_reg & ~GPIO_AFR_MASK(i)) |
                                (settings->io_altfunc << ((i & 0x7) * 4));            
            }

            /* Set the GPIO mode */
            current_reg = GPIO_X_REGISTER(gpio_id, GPIO_MODER_OFFSET);
            *current_reg = (*current_reg & ~GPIO_MODER_MASK(i)) |
                            (settings->io_modetype << (i * 2));

            /* Set the PU/PD behavior */
            current_reg = GPIO_X_REGISTER(gpio_id, GPIO_PUDR_OFFSET);
            *current_reg = (*current_reg & ~GPIO_PUPDR_MASK(i)) |
                            (((settings->io_modetype & GPIO_PUPD_MASK) >> 
                            GPIO_PUPD_OFFSET)
                            << i * 2);
        }
    }
    KERNEL_LOG_INFO("GPIO initialized", 
                    (void*)&gpio_id, 
                    sizeof(gpio_id), 
                    NO_ERROR);

    return NO_ERROR;
}