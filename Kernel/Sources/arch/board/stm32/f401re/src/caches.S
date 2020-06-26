/*******************************************************************************
 * @file caches.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief STM32 F401RE BSP cache management.
 *
 * @details STM32 F401RE BSP cache management. This module contains the 
 * routines used to manage the BSP caches and prefetch unit.
 ******************************************************************************/
.syntax unified

/*******************************************************************************
 * DEFINES
 ******************************************************************************/
/* Flash registers map */
.equ FLASH_ACR_ADDRESS, 0x40023C00

/* Flash registers values */
.equ FLASH_ACR_DCACHE_EN,   0x00000400
.equ FLASH_ACR_ICACHE_EN,   0x00000200
.equ FLASH_ACR_PREFETCH_EN, 0x00000100

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
.global __bsp_icache_enable
.global __bsp_dcache_enable
.global __bsp_prefetch_enable

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .text

/**
­ * @brief Enables flash instruction cache.
 * 
 * @details Enables flash instruction cache.
 */
__bsp_icache_enable:
    ldr r0, =FLASH_ACR_ADDRESS
    ldr r1, [r0]
    orr r1, r1, #FLASH_ACR_ICACHE_EN
    str r1, [r0]
    dsb 
    isb
    bx lr
/*----------------------------------------------------------------------------*/

/**
­ * @brief Enables flash data cache.
 * 
 * @details Enables flash data cache.
 */
__bsp_dcache_enable:
    ldr r0, =FLASH_ACR_ADDRESS
    ldr r1, [r0]
    orr r1, r1, #FLASH_ACR_DCACHE_EN
    str r1, [r0]
    dsb 
    isb
    bx lr
/*----------------------------------------------------------------------------*/

/**
­ * @brief Enables flash prefetch unit.
 * 
 * @details Enables flash prefetch unit.
 */
__bsp_prefetch_enable:
    ldr r0, =FLASH_ACR_ADDRESS
    ldr r1, [r0]
    orr r1, r1, #FLASH_ACR_PREFETCH_EN
    str r1, [r0]
    dsb 
    isb
    bx lr
/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
