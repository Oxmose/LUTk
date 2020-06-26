/*******************************************************************************
 * @file clocks.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief STM32 F401RE clocks management.
 *
 * @details STM32 F401RE clocks management. This module contains the 
 * routines used to manage the STM32 F401RE clocks.
 ******************************************************************************/
.syntax unified

#include "bsp_defs.inc"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/* RCC registers */
.equ RCC_APB1ENR_ADDRESS, 0x40023840
.equ RCC_APB2ENR_ADDRESS, 0x40023844

/* RCC register values */
.equ RCC_APB2ENR_SYSCFGEN, 0x00004000
.equ RCC_APB1ENR_PWREN,    0x10000000

/*******************************************************************************
 * MACRO DEFINE
 ******************************************************************************/

/*******************************************************************************
 * EXTERN DATA
 ******************************************************************************/

/*******************************************************************************
 * EXTERN FUNCTIONS
 ******************************************************************************/
.extern __bsp_pwr_set_scaling

/*******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/
.global __bsp_sysclk_init

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .text

/**
 * @brief Enables system clocks.
 *
 * @details Enables system clocks. The CPU, AHB and APB clocks are initialized.
 * The function also sets the regulator output voltage needed by the clocks
 */
__bsp_sysclk_init:
    push {lr}

    /* Enable power interface clock */
    ldr r0, =RCC_APB1ENR_ADDRESS
    ldr r1, =RCC_APB1ENR_PWREN
    ldr r2, [r0]
    orr r2, r2, r1
    str r2, [r0]

    /* Enable system clock controller */
    ldr r0, =RCC_APB2ENR_ADDRESS
    ldr r1, =RCC_APB2ENR_SYSCFGEN
    ldr r2, [r0]
    orr r2, r2, r1
    str r2, [r0]

    /* Delay to ensure bit update */
    dsb 
    isb 
    ldr r2, [r0]

    /* Configure voltage scaling */
    ldr r0, =PWR_VOLTAGE_REGULATOR_SCALE2
    bl __bsp_pwr_set_scaling

    pop {pc}
/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
