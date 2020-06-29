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

#ifndef __BOARD_STM32F401RE_BSP_GPIO_H__
#define __BOARD_STM32F401RE_BSP_GPIO_H__

#include "error_types.h"
#include "stdint.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/** @brief GPIO registers base address */
#define GPIO_X_BASE_ADDRESS 0x40020000
/** @brief GPIO mode register offset */
#define GPIO_MODER_OFFSET   0x00
/** @brief GPIO output type register offset */
#define GPIO_OTYPER_OFFSET  0x04
/** @brief GPIO output speed register offset */
#define GPIO_OSPEEDR_OFFSET 0x08
/** @brief GPIO pull type registers offset */
#define GPIO_PUDR_OFFSET    0x0C
/** @brief GPIO alternate function low registers offset */
#define GPIO_AFRL_OFFSET    0x20
/** @brief GPIO alternate function high registers offset */
#define GPIO_AFRH_OFFSET    0x24

/** @brief GPIO mode: input IO */
#define GPIO_MODE_INPUT  0x00
/** @brief GPIO mode: output IO */
#define GPIO_MODE_OUTPUT 0x01
/** @brief GPIO mode: alternate function IO */
#define GPIO_MODE_ALTFUN 0x02
/** @brief GPIO mode: analog */
#define GPIO_MODE_ANALOG 0x03

/** @brief GPIO push/pull mode: push/pull */
#define GPIO_TYPE_PUSHPULL  0x00
/** @brief GPIO push/pull mode: open drain */
#define GPIO_TYPE_OPENDRAIN 0x04

/** @brief GPIO output speed: slow */
#define GPIO_SPEED_SLOW      0x00
/** @brief GPIO output speed: medium */
#define GPIO_SPEED_MEDIUM    0x01
/** @brief GPIO output speed: high */
#define GPIO_SPEED_HIGH      0x02
/** @brief GPIO output speed: very high */
#define GPIO_SPEED_VERY_HIGH 0x03

/** @brief GPIO pull mode: none */
#define GPIO_PUPD_NONE 0x00
/** @brief GPIO pull mode: up */
#define GPIO_PUPD_PU   0x08
/** @brief GPIO pull mode: down */
#define GPIO_PUPD_PD   0x10

/** @brief GPIO alternate function 0 */
#define GPIO_ALFUNC_0  0
/** @brief GPIO alternate function 1 */
#define GPIO_ALFUNC_1  1
/** @brief GPIO alternate function 2 */
#define GPIO_ALFUNC_2  2
/** @brief GPIO alternate function 3 */
#define GPIO_ALFUNC_3  3
/** @brief GPIO alternate function 4 */
#define GPIO_ALFUNC_4  4
/** @brief GPIO alternate function 5 */
#define GPIO_ALFUNC_5  5
/** @brief GPIO alternate function 6 */
#define GPIO_ALFUNC_6  6
/** @brief GPIO alternate function 7 */
#define GPIO_ALFUNC_7  7
/** @brief GPIO alternate function 8 */
#define GPIO_ALFUNC_8  8
/** @brief GPIO alternate function 9 */
#define GPIO_ALFUNC_9  9
/** @brief GPIO alternate function 10 */
#define GPIO_ALFUNC_10 10
/** @brief GPIO alternate function 11 */
#define GPIO_ALFUNC_11 11
/** @brief GPIO alternate function 12 */
#define GPIO_ALFUNC_12 12
/** @brief GPIO alternate function 13 */
#define GPIO_ALFUNC_13 13
/** @brief GPIO alternate function 14 */
#define GPIO_ALFUNC_14 14
/** @brief GPIO alternate function 15 */
#define GPIO_ALFUNC_15 15

/** @brief GPIO settings mode field mask */
#define GPIO_MODE_MASK   0x3
/** @brief GPIO settings mode field offset */
#define GPIO_MODE_OFFSET 0

/** @brief GPIO settings type field mask */
#define GPIO_TYPE_MASK   0x04
/** @brief GPIO settings type field offset */
#define GPIO_TYPE_OFFSET 2

/** @brief GPIO pull type field mask */
#define GPIO_PUPD_MASK   0x18
/** @brief GPIO pull type field offset */
#define GPIO_PUPD_OFFSET 3

/** @brief Maximum number of pins in one GPIO bank */
#define GPIO_PIN_COUNT 15

/** @brief GPIO bitfield: GPIO 0 */
#define GPIO_PIN_0  0x0001
/** @brief GPIO bitfield: GPIO 1 */
#define GPIO_PIN_1  0x0002
/** @brief GPIO bitfield: GPIO 2 */
#define GPIO_PIN_2  0x0004
/** @brief GPIO bitfield: GPIO 3 */
#define GPIO_PIN_3  0x0008
/** @brief GPIO bitfield: GPIO 4 */
#define GPIO_PIN_4  0x0010
/** @brief GPIO bitfield: GPIO 5 */
#define GPIO_PIN_5  0x0020
/** @brief GPIO bitfield: GPIO 6 */
#define GPIO_PIN_6  0x0040
/** @brief GPIO bitfield: GPIO 7 */
#define GPIO_PIN_7  0x0080
/** @brief GPIO bitfield: GPIO 8 */
#define GPIO_PIN_8  0x0100
/** @brief GPIO bitfield: GPIO 9 */
#define GPIO_PIN_9  0x0200
/** @brief GPIO bitfield: GPIO 10 */
#define GPIO_PIN_10 0x0400
/** @brief GPIO bitfield: GPIO 11 */
#define GPIO_PIN_11 0x0800
/** @brief GPIO bitfield: GPIO 12 */
#define GPIO_PIN_12 0x1000
/** @brief GPIO bitfield: GPIO 13 */
#define GPIO_PIN_13 0x2000
/** @brief GPIO bitfield: GPIO 14 */
#define GPIO_PIN_14 0x4000
/** @brief GPIO bitfield: GPIO 15 */
#define GPIO_PIN_15 0x8000

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/** @brief GPIO identifier used to differenciated the GPIOs present on the 
 * STM32F401RE board.
 */
enum GPIO_IDENTIFIER
{
    /** @brief GPIO identifier: bank A. */
    GPIO_ID_A = 0,
    /** @brief GPIO identifier: bank B. */
    GPIO_ID_B = 1,
    /** @brief GPIO identifier: bank C. */
    GPIO_ID_C = 2,
    /** @brief GPIO identifier: bank D. */
    GPIO_ID_D = 3,
    /** @brief GPIO identifier: bank E. */
    GPIO_ID_E = 4,
    /** @brief GPIO identifier: bank H. */
    GPIO_ID_H = 5,
};

/** @brief Short hand for enum GPIO_IDENTIFIER. */
typedef enum GPIO_IDENTIFIER GPIO_IDENTIFIER_E;

/** @brief GPIO settings structure. Stores the GPIO settings for a given 
 * GPIO bank. */
struct GPIO_SETTINGS
{
    /** @brief Bitfield of the enabled pins for the GPIO. */
    uint16_t io_pin;
    /** @brief Mode, type and PUPD type. */
    uint8_t  io_modetype;
    /** @brief IO output speed. */
    uint8_t  io_speed;
    /** @brief IO alternate function. */
    uint8_t  io_altfunc;
};

/** @brief Short hand for struct GPIO_SETTINGS. */ 
typedef struct GPIO_SETTINGS GPIO_SETTINGS_T;

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

/** 
 * @brief Initializes a given GPIO bank.
 * 
 * @brief Initializes a given GPIO bank based on the GPIO identifier and the 
 * GPIO settings given as parameters. 
 * 
 * @param[in] gpio_id The identifier of the GPIO to configure.
 * @param[in] settings The settings structure containing the parameters to 
 * apply to the GPIO.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E bsp_gpio_init(const GPIO_IDENTIFIER_E gpio_id, 
                           const GPIO_SETTINGS_T* settings);

#endif /* #ifndef __BOARD_STM32F401RE_BSP_GPIO_H__ */