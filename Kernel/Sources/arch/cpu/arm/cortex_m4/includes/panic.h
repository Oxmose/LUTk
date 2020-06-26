/*******************************************************************************
 * @file panic.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 23/06/2020
 *
 * @version 1.0
 *
 * @brief Cortex M4 implementation of the kernel panic routine.
 *
 * @details Cortex M4 implementation of the kernel panic routine. This module
 * provides routine to set the system state in panic mode.
 ******************************************************************************/

#ifndef __CPU_CORTEX_M4_PANIC_H__
#define __CPU_CORTEX_M4_PANIC_H__

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
 * @brief Kernel panic endpoint.
 * 
 * @details Kernel panic endpoint. This function is dedicated to handle a kernel
 * panic. It outpus the current system's state before putting it in halted mode.
 * 
 * @param[in] reason The reason of the kernel panic.
 * 
 * @warning This function should never return.
 */
void kernel_panic(const ERROR_CODE_E reason);

#endif /* #ifndef __CPU_CORTEX_M4_PANIC_H__ */