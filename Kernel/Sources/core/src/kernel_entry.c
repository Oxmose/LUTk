/*******************************************************************************
 * @file kickstart.c
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 23/06/2020
 *
 * @version 1.0
 *
 * @brief Core implementation of the kickstart process.
 *
 * @details Core implementation of the kickstart process. This module
 * provides routine to setup the processor and bootstrap the kernel.
 ******************************************************************************/

#include "error_types.h"
#include "config.h"
#include "serial.h"

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
    SERIAL_SETTINGS_T ser_settings = CONFIG_UART_SETTINGS;
    ERROR_CODE_E error;
    (void) error;

    error = serial_init(&ser_settings);
#if 0
    if(error != NO_ERROR)
    {
        KERNEL_LOG_ERROR("Clocks initialization error", error, 1);
        kernel_panic(error);
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

    serial_write("Hardware initialized, jumping to kernel\n\r", 41);
    while(1);
}
