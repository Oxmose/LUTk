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

#include "stdint.h"
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
 * @brief Gets the current CPU frequency in Hz.
 * 
 * @details Gets the current CPU frequency. If the BSP is not in charge of
 * such settings, an error is returned.
 * 
 * @param[out] freq The pointer to store the currently set CPU's frequency in 
 * Hz.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E bsp_get_cpu_freq(uint32_t* freq);

#endif /* #ifndef __BOARD_CLOCKS_H__ */