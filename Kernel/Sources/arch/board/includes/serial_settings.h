/*******************************************************************************
 * @file serial_settings.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief Board serial management.
 *
 * @details Board serial management. This module contains the values for the 
 * different serial settings.
 ******************************************************************************/

#ifndef __BOARD_SERIAL_SETTINGS_H__
#define __BOARD_SERIAL_SETTINGS_H__

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

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/


#endif /* #ifndef __BOARD_SERIAL_SETTINGS_H__ */