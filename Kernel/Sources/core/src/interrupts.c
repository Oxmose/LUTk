#include "stddef.h"
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

#include "stdint.h"
#include "config.h"
#include "interrupts.h"
#include "panic.h"
#include "error_types.h"
#include "logger.h"

/*******************************************************************************
 * Private data
 ******************************************************************************/

static KERNEL_INT_HANDLER_T handlers[CONFIG_MAX_INTERRUPT_LINES] = {{NULL}};

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/*******************************************************************************
 * Public functions
 ******************************************************************************/

void kernel_global_interrupt_handler(const INTERRUPT_ID_T int_number, 
                                     const uintptr_t stack, 
                                     const uintptr_t cpu_state)
{
    (void)stack;
    (void)cpu_state;

    if(int_number > CONFIG_MAX_INTERRUPT_LINES ||
       handlers[int_number].handler == NULL)
    {
        KERNEL_LOG_ERROR("Unkown interrupt ID", 
                         (void*)(uint32_t)int_number, 
                         sizeof(int_number),
                         ERROR_UNKNOWN_INT);
        kernel_panic(ERROR_UNKNOWN_INT);
    }

}
