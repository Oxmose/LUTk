/*******************************************************************************
 * @file bsp_power.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief STM32 F401RE power management.
 *
 * @details STM32 F401RE power management. This module contains the 
 * routines used to manage the STM32 F401RE power.
 ******************************************************************************/

#ifndef __BOARD_STM32F401RE_BSP_POWER_H__
#define __BOARD_STM32F401RE_BSP_POWER_H__

#include "error_types.h"
#include "stdint.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/** @brief Power Control Register base address */
#define PWR_CR_BASE_ADDRESS 0x40007000
#define PWR_CR_REGISTER     ((volatile uint32_t*)PWR_CR_BASE_ADDRESS)

/** @brief Power Control Register VOS mask. */
#define PWR_CR_VOS_MASK 0x0000C000

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/** @brief Power scaling modes available on the STM32F401RE. */
enum POWER_SCALING
{
    /** @brief Power scaling mode 2. */
    POWER_SCALING_MODE_2 = 0x00008000,
    /** @brief Power scaling mode 3. */
    POWER_SCALING_MODE_3 = 0x00004000
};

/** @brief Short hand for enum POWER_SCALING. */
typedef enum POWER_SCALING POWER_SCALING_E;

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

/**
 * @brief Sets the power scaling.
 *
 * @details Sets the power scaling based on the values passed in paramter. 
 * The scaling conforms to the values defined by the reference manual. If the 
 * value does not conform, the function has no effect and returns an error code.
 *
 * @param pwr_scaling The scaling factor configuration.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E bsp_pwr_set_scaling(const POWER_SCALING_E pwr_scaling);

#endif /* #ifndef __BOARD_STM32F401RE_BSP_POWER_H__ */