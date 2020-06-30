/*******************************************************************************
 * @file kernel_entry.c
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
#include "logger.h"
#include "bsp_logger.h"
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
    ERROR_CODE_E      error;
    SERIAL_SETTINGS_T ser_settings = CONFIG_UART_SETTINGS;
    LOGGER_SETTINGS_T log_settings = {bsp_logger_write_hook};
    
    error = logger_init(&log_settings);
    if(error != NO_ERROR)
    {       
        kernel_panic(error);
    }

    /* Serial init */
    error = serial_init(&ser_settings);
    if(error != NO_ERROR)
    {
        KERNEL_LOG_ERROR("Serial initialization error", 
                         (void*)&error, 
                         sizeof(error),
                         error);
       
        kernel_panic(error);
    }
    KERNEL_LOG_INFO("Serial initialized", NULL, 0, error);
    

    /* Initialize the MPU */

    KERNEL_LOG_INFO("Kernel initialized", NULL, 0, NO_ERROR);
    while(1);
}
