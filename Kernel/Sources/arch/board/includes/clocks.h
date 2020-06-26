/*******************************************************************************
 * @file clocks.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 24/06/2020
 *
 * @version 1.0
 *
 * @brief Board clocks management.
 *
 * @details Board clocks management. This module contains the routines interface
 * used to configure the different clocks used by the boards.
 ******************************************************************************/

#ifndef __BOARD_CLOCKS_H__
#define __BOARD_CLOCKS_H__

#include "error_types.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

/**
 * @brief Initializes the board clocks.
 * 
 * @brief Initializes the board clocks. This function initializes the timers
 * and various clock signals of the board. If none requires initialization
 * this function just returns successfuly.
 * 
 * @return On success NO_ERROR is return. In case of error an error code is
 * returned.
 */
ERROR_CODE_E clocks_init(void);

#endif /* #ifndef __BOARD_CLOCKS_H__ */