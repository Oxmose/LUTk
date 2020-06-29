/*******************************************************************************
 * @file nvic.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 24/06/2020
 *
 * @version 1.0
 *
 * @brief Cortex M4 NVIC driver.
 *
 * @details Cortex M4 NVIC driver. This module contains the functions used to
 * manage the Nested Vectored Interrupt Controller.
 ******************************************************************************/
.syntax unified

#include "memory_map.inc"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/** @brief NVIC ISER0 register address */
.equ NVIC_ISER0_ADDRESS, 0xE000E100
/** @brief NVIC ISER1 register address */
.equ NVIC_ISER1_ADDRESS, 0xE000E104
/** @brief NVIC ISER2 register address */
.equ NVIC_ISER2_ADDRESS, 0xE000E108

/** @brief NVIC ICER0 register address */
.equ NVIC_ICER0_ADDRESS, 0xE000E180
/** @brief NVIC ICER1 register address */
.equ NVIC_ICER1_ADDRESS, 0xE000E184
/** @brief NVIC ICER2 register address */
.equ NVIC_ICER2_ADDRESS, 0xE000E188


/** @brief NVIC AIRCR_PRIGROUP mask */
.equ SCB_AIRCR_PRIGROUP_MASK,  0x00000700
/** @brief NVIC VECTKEYSTAT value */
.equ SCB_VECTKEYSTAT_VALUE,    0x05FA0000
/** @brief NVIC VECTKEYSTAT inverted mask */
.equ SCB_VECTKEYSTAT_INV_MASK, 0x0000FFFF


/*******************************************************************************
 * MACRO DEFINE
 ******************************************************************************/

/*******************************************************************************
 * EXTERN DATA
 ******************************************************************************/

/*******************************************************************************
 * EXTERN FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/
.global __nvic_init

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .text

/**
 * @brief Initializes the NVIC.
 *
 * @details Initializes the NVIC. Only the first 16 interrupts are enabled to 
 * deny any external interrupt.
 *
 */
__nvic_init:
    push {lr}

    /* Enable 16 first interrupts */
    ldr r0, =0x0000FFFF
    ldr r1, =NVIC_ISER0_ADDRESS
    str r1, [r0]

    /* Set 4 priority groups */
    mov r0, #4
    bl  __nvic_set_prio_group_count

    pop  {pc}
/*----------------------------------------------------------------------------*/

/**
 * @brief Sets the number of priority groups managed by the NVIC.
 *
 * @details Sets the number of priority groups managed by the NVIC. There can be
 * at most 7 groups. If the parameter contained in r0 is higher than 7, this 
 * function has no effect.
 *
 * @param r0 contains the number of groups.
 *
 */
__nvic_set_prio_group_count:
    push {r3}
    mov r1, #7
    cmp r0, r1
    bgt __nvic_set_prio_group_count_end

    /* Shift group count */
    lsl r0, r0, #8

    /* Get current value */
    ldr r1, =GEN_SCB_AIRCR_ADDR
    ldr r2, [r1]
    ldr r3, =SCB_VECTKEYSTAT_INV_MASK
    and r2, r2, r3

    /* Update new value */
    ldr r3, =SCB_VECTKEYSTAT_VALUE    
    bic r2, r2, #SCB_AIRCR_PRIGROUP_MASK
    orr r2, r2, r0
    orr r2, r2, r3
    str r2, [r1]

__nvic_set_prio_group_count_end:
    pop {r3}
    bx lr
/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
