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
#include "sync.h"
#include "string.h"

/*******************************************************************************
 * Private data
 ******************************************************************************/

/** @brief Stores the current interrupt handlers */
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
    /* Checks the handler validity */
    if(int_number > CONFIG_MAX_INTERRUPT_LINES ||
       handlers[int_number].handler == NULL)
    {
        KERNEL_LOG_ERROR("Unkown interrupt ID", 
                         (void*)(uint32_t)int_number, 
                         sizeof(int_number),
                         ERROR_UNKNOWN_INT);
        kernel_panic(ERROR_UNKNOWN_INT);
    }

    /* Call the handler */
    handlers[int_number].handler(int_number, stack, cpu_state);
}

ERROR_CODE_E interrupt_register_handler(const KERNEL_INT_HANDLER_T* handler,
                                        const INTERRUPT_ID_T int_id)
{
    CRITICAL_STRUCT_T crit;

    if(handler == NULL || handler->handler == NULL)
    {
        KERNEL_LOG_ERROR("NULL handler cannot be registered", 
                         (void*)(uint32_t)handler, 
                         sizeof(handler),
                         ERROR_NULL_POINTER);

        return ERROR_NULL_POINTER;
    }

    enter_critical(&crit);

    if(int_id > CONFIG_MAX_INTERRUPT_LINES || handlers[int_id].handler != NULL)
    {
        exit_critical(&crit);

        KERNEL_LOG_ERROR("Interrupt does not exist or is already registered", 
                         (void*)(uint32_t)int_id, 
                         sizeof(int_id),
                         ERROR_NOT_AVAILABLE);
        return ERROR_NOT_AVAILABLE;
    }

    /* Register the handler */
    handlers[int_id] = *handler;

    exit_critical(&crit);

    return NO_ERROR;
}


ERROR_CODE_E interrupt_clear_handler(const INTERRUPT_ID_T int_id)
{
    CRITICAL_STRUCT_T crit;

    enter_critical(&crit);

    if(int_id > CONFIG_MAX_INTERRUPT_LINES || handlers[int_id].handler == NULL)
    {
        exit_critical(&crit);

        KERNEL_LOG_ERROR("Interrupt does not exist or is not registered", 
                         (void*)(uint32_t)int_id, 
                         sizeof(int_id),
                         ERROR_NOT_AVAILABLE);
        return ERROR_NOT_AVAILABLE;
    }

    /* Reset the handler value */
    memset(&handlers[int_id], 0, sizeof(KERNEL_INT_HANDLER_T));

    exit_critical(&crit);

    return NO_ERROR;
}