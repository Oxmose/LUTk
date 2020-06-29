/*******************************************************************************
 * @file bsp_power.c
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

#include "error_types.h"
#include "bsp_power.h"
#include "stdint.h"
#include "config.h"

/*******************************************************************************
 * Private Data
 ******************************************************************************/

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/*******************************************************************************
 * Public functions
 ******************************************************************************/

ERROR_CODE_E bsp_pwr_set_scaling(const POWER_SCALING_E pwr_scaling)
{
    /* Sets the power scaling value, we don't apply mask verification because 
     * the POWER_SCALING_E enumeration should already contain the right values.
     */
    *PWR_CR_REGISTER = (*PWR_CR_REGISTER & ~PWR_CR_VOS_MASK) | pwr_scaling;

    /* Delay to ensure bit update */
    while((*PWR_CR_REGISTER & PWR_CR_VOS_MASK) != pwr_scaling);

#if KERNEL_LOG_LEVEL >= INFO_LOG_LEVEL
    KERNEL_LOG_INFO("Power scaling mode changed", 
                    pwr_scaling, 
                    sizeof(pwr_scaling), 
                    NO_ERROR);
#endif

    return NO_ERROR;
}