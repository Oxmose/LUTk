/*******************************************************************************
 * @file power.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief STM32 F401RE power management.
 *
 * @details STM32 F401RE power management. This module contains the 
 * routines used to manage the STM32 F401RE power.
 ******************************************************************************/
.syntax unified

#include "bsp_defs.inc"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

 /* RCC registers */
.equ PWR_CR_ADDRESS, 0x40007000

/* RCC register values */
.equ PWR_CR_VOS_MASK, 0x0000C000
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
.global __bsp_pwr_set_scaling

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .text

/**
 * @brief Sets the power scaling.
 *
 * @details Sets the power scaling based on the values passed in R0. The scaling
 * must be conform to the values defined by the reference manual. If the value
 * is not conform, this function does nothing.
 *
 * @param r0 contains the scaling configuration.
 */
__bsp_pwr_set_scaling:

    /* Enable power interface clock */
    ldr r1, =PWR_CR_VOS_MASK
    and r1, r1, r0
    ldr r0, =PWR_CR_ADDRESS
    ldr r2, [r0]
    orr r2, r2, r1
    str r2, [r0]

    /* Delay to ensure bit update */
    dsb 
    isb 
    ldr r2, [r0]

    bx lr
/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
