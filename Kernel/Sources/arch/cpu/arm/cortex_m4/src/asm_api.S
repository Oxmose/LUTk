/*******************************************************************************
 * @file asm_api.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 24/06/2020
 *
 * @version 1.0
 *
 * @brief Cortex M4 assembly API implementation.
 *
 * @details Cortex M4 assembly API implementation. This module implements the
 * API defined in the global CPU module.
 ******************************************************************************/
.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

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
.global cpu_mem_barrier
.global disable_interrupt
.global enable_interrupt

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .text,"ax",%progbits


/**
 * @brief Full memory barrier.
 * 
 * @details Full memory barrier, both intended to synchronize for data and 
 * instructions barrier.
 */
.type cpu_mem_barrier, %function
cpu_mem_barrier:
    dsb
    isb
    bx lr
/*----------------------------------------------------------------------------*/

/**
 * @brief Disables interrupts and return the interrupt mask in R0.
 * 
 * @details Disables interrupts and return the interrupt mask in R0.
 *
 * @return The interrupt mask is returned in R0
 */
.type disable_interrupt, %function
disable_interrupt:
    mrs r1, PRIMASK
    mov r0, r1
    and r0, 1
    bic r1, 1
    msr PRIMASK, r1
    bx  lr
/*----------------------------------------------------------------------------*/

/**
 * @brief Enables interrupts.
 * 
 * @details Enables interrupts.
 */
.type enable_interrupt, %function
enable_interrupt:
    mrs r1, PRIMASK
    orr r1, r1, 1
    msr PRIMASK, r1 
    bx  lr
/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
