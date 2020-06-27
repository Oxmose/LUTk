/*******************************************************************************
 * @file kickstart.c
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 23/06/2020
 *
 * @version 1.0
 *
 * @brief Cortex M4 implementation of the kickstart process.
 *
 * @details Cortex M4 implementation of the kickstart process. This module
 * provides routine to setup the processor and bootstrap the kernel.
 ******************************************************************************/

#include "error_types.h"

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/*******************************************************************************
 * Public functions
 ******************************************************************************/

/**
 * @brief Kernel kickstart routine. 
 * 
 * @details Kernel kickstart routine. This function calls the different 
 * initialization modules required before starting the kernel core.
 * 
 * @warning This function should never return.
 */
void kernel_kickstart(void)
{
    ERROR_CODE_E error;
    (void) error;
#if 0
    if(error != NO_ERROR)
    {
        KERNEL_LOG_ERROR("Clocks initialization error", error, 1);
    }
    KERNEL_LOG_INFO("Clocks initialized", error);
#endif

#if 0
    if(error != NO_ERROR)
    {
        KERNEL_LOG_ERROR("FPU initialization error", error, 1);
    }
    KERNEL_LOG_INFO("FPU initialized", error);
#endif
    

    /* Initialize the NVIC */

    /* Initialize the MPU */
}
