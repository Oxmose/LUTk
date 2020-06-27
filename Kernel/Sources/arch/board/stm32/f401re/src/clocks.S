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
.equ RCC_CR_ADDRESS,      0x40023800
.equ RCC_PLLCFGR_ADDRESS, 0x40023804 
.equ RCC_CFGR_ADDRESS,    0x40023808
.equ RCC_APB1ENR_ADDRESS, 0x40023840
.equ RCC_APB2ENR_ADDRESS, 0x40023844

/* RCC register values */
.equ RCC_APB2ENR_SYSCFGEN, 0x00004000

.equ RCC_APB1ENR_PWREN,    0x10000000

.equ RCC_CR_PLLI2SRDY,     0x08000000
.equ RCC_CR_PLLI2SON,      0x04000000
.equ RCC_CR_PLLRDY,        0x02000000
.equ RCC_CR_PLLON,         0x01000000
.equ RCC_CR_HSITRIM_BASE,  0x00000080
.equ RCC_CR_HSION,         0x00000001
.equ RCC_CR_HSIRDY,        0x00000002

.equ RCC_CFGR_SW_PLL,      0x00000002
.equ RCC_CFGR_SWS_PLL,     0x00000008
.equ RCC_CFGR_HRPE_DIV1,   0x00000000
.equ RCC_CFGR_PPRE1_DIV2,  0x00001000
.equ RCC_CFGR_PPRE2_DIV1,  0x00000000

/* RCC registers masks and offsets */
.equ RCC_PLLCFGR_PLLM_MASK,     0x0000003F
.equ RCC_PLLCFGR_PLLN_MASK,     0x00007FC0
.equ RCC_PLLCFGR_PLLP_MASK,     0x00030000
.equ RCC_PLLCFGR_PLLQ_MASK,     0x0F000000
.equ RCC_PLLCFGR_PLLSRC_MASK,   0x00400000

.equ RCC_CFGR_SW_MASK,    0x00000003
.equ RCC_CFGR_SWS_MASK,   0x0000000C
.equ RCC_CFGR_HRPE_MASK,  0x000000F0
.equ RCC_CFGR_PPRE1_MASK, 0x00001C00
.equ RCC_CFGR_PPRE2_MASK, 0x0000E000

.equ RCC_PLLCFGR_PLLM_OFFSET, 0
.equ RCC_PLLCFGR_PLLN_OFFSET, 6
.equ RCC_PLLCFGR_PLLP_OFFSET, 16
.equ RCC_PLLCFGR_PLLQ_OFFSET, 24

.equ RCC_PLLCFGR_PLLSRC_OFFSET, 22

/* PLL settings for 84MHz system clock with HSI input */
.equ RCC_PLLM_VALUE, 16  
.equ RCC_PLLN_VALUE, 336 
.equ RCC_PLLP_VALUE, 1 /* 4 */
.equ RCC_PLLQ_VALUE, 8

.equ RCC_PLLSRC_VALUE, 0

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
.extern __bsp_flash_set_latency

/*******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/
.global __bsp_sysclk_init

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .text

/**
 * @brief Initializes system clocks.
 *
 * @details Initializes system clocks. The HSI is enabled and its calibration
 * value.
 */
__bsp_clocks_init:
    /* At this point the SYSCLOCK should be HSI, adjust the calibration value */
    ldr r0, =RCC_CR_ADDRESS
    ldr r1, =RCC_CR_HSITRIM_BASE
    ldr r2, =RCC_CR_HSION
    orr r2, r2, r1 
    ldr r1, [r0]
    orr r2, r2, r1 
    str r2, [r0]

    /* Wait for HSI to be ready */
    ldr r1, =RCC_CR_HSIRDY
wait_hsi:
    ldr r2, [r0]
    and r2, r2, r1 
    cmp r2, r1
    bne wait_hsi

    bx lr
/*----------------------------------------------------------------------------*/

/**
 * @brief Initializes system PLL clocks.
 *
 * @details Initializes system PLL clocks. The PLL are set for a system clock
 * of 84MHz and bus to 48MHz.
 */
__bsp_pll_init:
    ldr r0, =RCC_PLLCFGR_ADDRESS
    ldr r1, [r0]
    ldr r2, =(RCC_PLLCFGR_PLLM_MASK | RCC_PLLCFGR_PLLN_MASK | \
              RCC_PLLCFGR_PLLP_MASK | RCC_PLLCFGR_PLLQ_MASK | \
              RCC_PLLCFGR_PLLSRC_MASK)
    bic r1, r1, r2

    /* Set PLLM */
    mov r2, #RCC_PLLM_VALUE
    lsl r2, r2, #RCC_PLLCFGR_PLLM_OFFSET
    orr r1, r1, r2

    /* Set PLLN */
    mov r2, #RCC_PLLN_VALUE
    lsl r2, r2, #RCC_PLLCFGR_PLLN_OFFSET
    orr r1, r1, r2

    /* Set PLLP */
    mov r2, #RCC_PLLP_VALUE
    lsl r2, r2, #RCC_PLLCFGR_PLLP_OFFSET
    orr r1, r1, r2

    /* Set PLLQ */
    mov r2, #RCC_PLLQ_VALUE
    lsl r2, r2, #RCC_PLLCFGR_PLLQ_OFFSET
    orr r1, r1, r2

    /* Set PLL source as HSI */
    mov r2, #RCC_PLLSRC_VALUE
    lsl r2, r2, #RCC_PLLCFGR_PLLSRC_OFFSET
    orr r1, r1, r2

    /* Store new value */
    str r1, [r0]

    /* Enable PLLs */
    ldr r0, =RCC_CR_ADDRESS
    ldr r1, [r0]
    ldr r2, =RCC_CR_PLLON
    orr r1, r1, r2
    str r1, [r0]

    /* Wait for PLL to be ready */
    ldr r1, =RCC_CR_PLLRDY
wait_pll:
    ldr r2, [r0]
    and r2, r2, r1 
    cmp r2, r1
    bne wait_pll

    bx lr
/*----------------------------------------------------------------------------*/

/**
 * @brief Sets the system clock to be driven by PLL output.
 * 
 * @details Sets the system clock to be driven by PLL output.
 */
__bsp_sysclk_set_pll:
    push {r3}

    /* Sets the AHB prescaler divider to 1 (no division) */
    ldr r0, =RCC_CFGR_ADDRESS
    ldr r1, =RCC_CFGR_HRPE_MASK
    ldr r2, [r0]
    bic r2, r2, r1 
    ldr r1, =RCC_CFGR_HRPE_DIV1
    orr r2, r2, r1
    str r2, [r0]

    /* Sets the APB1 prescaler devider to 2 */
    ldr r1, =RCC_CFGR_PPRE1_MASK
    ldr r2, [r0]
    bic r2, r2, r1 
    ldr r1, =RCC_CFGR_PPRE1_DIV2
    orr r2, r2, r1
    str r2, [r0]

    /* Sets the APB2 prescaler devider to 1 (no division) */
    ldr r1, =RCC_CFGR_PPRE2_MASK
    ldr r2, [r0]
    bic r2, r2, r1 
    ldr r1, =RCC_CFGR_PPRE2_DIV1
    orr r2, r2, r1
    str r2, [r0]

    /* Sets the system clock to use PLL as input */
    ldr r1, =RCC_CFGR_SW_MASK
    bic r2, r2, r1 
    ldr r1, =RCC_CFGR_SW_PLL
    orr r2, r2, r1
    str r2, [r0]

    /* Wait for SWS update */
    ldr r1, =RCC_CFGR_SWS_MASK
    ldr r3, =RCC_CFGR_SWS_PLL
wait_sws:
    ldr r2, [r0]    
    and r2, r2, r1     
    cmp r3, r2 
    bne wait_sws

    pop {r3}
    bx  lr
/*----------------------------------------------------------------------------*/

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

    /* Init flash latency */
    ldr r0, =FLASH_KERNEL_LATENCY
    bl  __bsp_flash_set_latency

    /* Init clocks */
    bl  __bsp_clocks_init

    /* Init PLL */
    bl __bsp_pll_init

    /* Switch sysclk to PLL input */
    bl __bsp_sysclk_set_pll

    pop {pc}
/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
