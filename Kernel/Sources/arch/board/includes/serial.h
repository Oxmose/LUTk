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
#include "serial_settings.h"
#include "error_types.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

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