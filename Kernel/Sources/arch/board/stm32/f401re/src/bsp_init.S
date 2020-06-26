/*******************************************************************************
 * @file bsp_init.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 23/06/2020
 *
 * @version 1.0
 *
 * @brief STM32 F401RE BSP initialization module.
 *
 * @details STM32 F401RE BSP initialization module. This module contains the 
 * routines used to manage the BSP initialization.
 ******************************************************************************/
.syntax unified

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
.extern __bsp_icache_enable
.extern __bsp_dcache_enable
.extern __bsp_prefetch_enable
.extern __bsp_sysclk_init
.extern __bsp_pwrclk_init

/*******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/
.global __bsp_init

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .text

/**
­ * @brief Initializes the BSP components.
 * 
 * @details Initializes the BSP components by enabling caches, setting clocks,
 * flash settings, timers GPIOs and UART.
 */
__bsp_init:
    push {lr}

    /* Enable caches */
    bl __bsp_icache_enable
    bl __bsp_dcache_enable
    bl __bsp_prefetch_enable

    /* Initialize clocks */
    bl __bsp_sysclk_init

    pop  {pc}
/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
