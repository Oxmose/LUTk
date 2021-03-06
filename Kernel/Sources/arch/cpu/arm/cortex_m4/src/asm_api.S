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

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
