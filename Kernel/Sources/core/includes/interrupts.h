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


#endif /* #ifndef __CORE_INTERRRUPTS_H__ */