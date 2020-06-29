/*******************************************************************************
 * @file panic.c
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

#include "error_types.h"
#include "panic.h"

/*******************************************************************************
 * Private data
 ******************************************************************************/

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/*******************************************************************************
 * Public functions
 ******************************************************************************/

void kernel_panic(const ERROR_CODE_E reason)
{

    (void) reason;
    
    /* We halt here, the error cannot be recovered */
    while(1);
}