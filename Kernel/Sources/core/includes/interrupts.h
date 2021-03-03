/*******************************************************************************
 * @file interrupts.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 06/07/2020
 *
 * @version 1.0
 *
 * @brief Interrupts module definition.
 *
 * @details Interrupts module definition. This moduels defines the different
 * routines and structures used to manage interrupts and exceptions in the
 * kernel.
 ******************************************************************************/

#ifndef __CORE_INTERRRUPTS_H__
#define __CORE_INTERRRUPTS_H__

#include "stdint.h"
#include "error_types.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/**
 * @brief Defines the different interrupt indentifiers available in the kernel.
 * 
 * @warning The interrupts IDs should be the same as defined in the 
 * interrupt.inc file.
 */
enum INTERRUPT_ID
{
    INT_SYS_CALL_ID = 0,
    INT_SYS_TICK_ID = 1
};

/** @brief Short hand for enum INTERRUPT_ID */
typedef enum INTERRUPT_ID INTERRUPT_ID_T;

/** @brief Defines the handler structure used to manage interrupts routines. */
struct KERNEL_INT_HANDLER
{
    void (*handler)(const INTERRUPT_ID_T int_number, 
                    const uintptr_t stack, 
                    const uintptr_t cpu_state);
};

/** @brief Short hand for struct KERNEL_INT_HANDLER */
typedef struct KERNEL_INT_HANDLER KERNEL_INT_HANDLER_T;

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

/**
 * @brief Kernel's global interrupt handler.
 * 
 * @details Kernel's global interrupt handler. This function should be called
 * to handle an interrupt. The global handler is in charge of routing the 
 * interrupt to the custom handlers that have been registered.
 * 
 * @param[in] int_number The interrupt number.
 * @param[in] stack The pointer to the interrupt stack.
 * @param[in] cpu_state The pointer to the cpu state memory area (can be a 
 * structure).
 */
void kernel_global_interrupt_handler(const INTERRUPT_ID_T int_number, 
                                     const uintptr_t stack, 
                                     const uintptr_t cpu_state);

/**
 * @brief Registers an interrupt handler.
 * 
 * @details Registers a custom interrupt handler to be executed. The interrupt 
 * line must be greater or equal to the minimal authorized custom interrupt line
 * and less than the maximal one.
 * 
 * @param[in] handler The handler to be attached to the desired interrupt.
 * @param[in] int_id The identifier of the interrupt to attach the handler with.
 *
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E interrupt_register_handler(const KERNEL_INT_HANDLER_T* handler,
                                        const INTERRUPT_ID_T int_id);

/**
 * @brief Unregisters an interrupt handler.
 * 
 * @details Unregisters a custom interrupt handler to be executed. The interrupt 
 * line must be greater or equal to the minimal authorized custom interrupt line
 * and less than the maximal one.
 * 
 * @param[in] int_id The identifier of the interrupt to detach the handler from.
 *
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E interrupt_clear_handler(const INTERRUPT_ID_T int_id);

#endif /* #ifndef __CORE_INTERRRUPTS_H__ */