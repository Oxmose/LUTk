/*******************************************************************************
 * @file serial.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief Board serial management.
 *
 * @details Board serial management. This module contains the routines interface
 * used to manage the board's serial interface.
 ******************************************************************************/

#ifndef __BOARD_SERIAL_H__
#define __BOARD_SERIAL_H__

#include "stdint.h"
#include "stddef.h"
#include "error_types.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/** @brief Serial parity setting: no parity. */
#define SERIAL_PARITY_NONE 0
/** @brief Serial parity setting: odd parity. */
#define SERIAL_PARITY_ODD  1
/** @brief Serial parity setting: even parity. */
#define SERIAL_PARITY_EVEN 2

/** @brief Serial stop bits number: 0.5 bits. */
#define SERIAL_STOP_BITS_05 0
/** @brief Serial stop bits number: 1 bits. */
#define SERIAL_STOP_BITS_1  1
/** @brief Serial stop bits number: 1.5 bits. */
#define SERIAL_STOP_BITS_15 2
/** @brief Serial stop bits number: 2 bits. */
#define SERIAL_STOP_BITS_2  3

/** @brief Serial flow control method: no control. */
#define SERIAL_CTRL_FLOW_NONE    0
/** @brief Serial flow control method: XON/XOFF control. */
#define SERIAL_CTRL_FLOW_XONXOFF 1
/** @brief Serial flow control method: hardware CTS control. */
#define SERIAL_CTRL_FLOW_CTS     2
/** @brief Serial flow control method: hardware RTS control. */
#define SERIAL_CTRL_FLOW_RTS     3
/** @brief Serial flow control method: hardware CTSand RTS control. */
#define SERIAL_CTRL_FLOW_CTS_RTS 4

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/** @brief Serial settings structure that contains the parameters used to 
 * configure the serial line.
 */
struct SERIAL_SETTINGS
{
    /** @brief Serial line's baudrate. */
    uint32_t baudrate;
    /** @brief Serial word's length (usually 8 or 9). */
    uint8_t  word_length;
    /** @brief Serial number of stop bits. */
    uint8_t  stop_bits;
    /** @brief Serial line's parity control. */
    uint8_t  partity;
    /** @brief Serial line's flow control. */
    uint8_t  ctrl_flow;
};

/** @brief Sharthand for struct SERIAL_SETTINGS. */
typedef struct SERIAL_SETTINGS SERIAL_SETTINGS_T;

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

/**
 * @brief Initializes the serial line.
 * 
 * @details Initializes the system's serial line. The settings structure is 
 * used to set the line's parameter according to th user's choice.
 * 
 * @param[in] settings The settings structure used to initialize the serial
 * line.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E serial_init(const SERIAL_SETTINGS_T* settings);

/**
 * @brief Writes a string of characters to the serial line.
 * 
 * @details Writes a string of characters to the serial line. The line should 
 * have been initialized. If the serial line is not ready, this function has 
 * no effect.
 * 
 * @param[in] str The string to send to the serial line.
 * @param[in] length The length of the string to send to the serial line.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E serial_write(const char* str, const size_t length);

#endif /* #ifndef __BOARD_SERIAL_H__ */