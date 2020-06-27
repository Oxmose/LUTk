/*******************************************************************************
 * @file flash.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief STM32 F401RE BSP flash management.
 *
 * @details STM32 F401RE BSP flash management. This module contains the 
 * routines used to manage the BSP flash, cache and prefetch unit.
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

/* Flash registers masks */
.equ FLASH_ACR_LATENCY_MASK, 0x0000000F

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
.global __bsp_flash_set_latency

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

/**
­ * @brief Sets the flash latency.
 * 
 * @details  Sets the flash latency based on the latency given as parameter.
 * If the latency is bigger than the accepted one, only the low 4 bits are kept.
 *
 * @param r0 contains the latency. If the latency is bigger than the accepted 
 * one, only the low 4 bits are kept.
 */
__bsp_flash_set_latency:
    and r0, r0, #FLASH_ACR_LATENCY_MASK
    ldr r1, =FLASH_ACR_ADDRESS
    ldr r2, [r1]
    bic r2, r2, #FLASH_ACR_LATENCY_MASK
    orr r2, r2, r0
    str r2, [r1]

wait_flash_latency:
    ldr r2, [r1]
    and r2, r2, #FLASH_ACR_LATENCY_MASK
    cmp r2, r0 
    bne wait_flash_latency

    bx lr
/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
