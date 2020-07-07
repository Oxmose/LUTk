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
.extern bsp_flash_cache_enable
.extern bsp_flash_prefetch_enable
.extern bsp_clk_sys_init

/*******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/
.global __bsp_init

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .text,"ax",%progbits

/**
­ * @brief Initializes the BSP components.
 * 
 * @details Initializes the BSP components by enabling caches, setting clocks,
 * flash settings, timers GPIOs and UART.
 */
 .type __bsp_init, %function
__bsp_init:
    push {lr}

    /* Enable caches */
    bl bsp_flash_cache_enable
    bl bsp_flash_prefetch_enable

    /* Initialize clocks */
    bl bsp_clk_sys_init

    pop  {pc}
/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
