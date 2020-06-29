/*******************************************************************************
 * @file fpu.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 24/06/2020
 *
 * @version 1.0
 *
 * @brief Cortex M4 FPU driver.
 *
 * @details Cortex M4 FPU driver. This module contains the functions used to
 * enable, disable and configure the FPU.
 ******************************************************************************/
.syntax unified

#include "memory_map.inc"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/** @brief FPU FPCCR address */
.equ FPU_FPCCR_ADDR,  0xE000EF34
/** @brief FPU FPCAR address */
.equ FPU_FPCAR_ADDR,  0xE000EF38
/** @brief FPU FPDSCR address */
.equ FPU_FPDSCR_ADDR, 0xE000EF3C
/** @brief FPU _MVFR0 address */
.equ FPU_MVFR0_ADDR,  0xE000EF40
/** @brief FPU MVFR1 address */
.equ FPU_MVFR1_ADDR,  0xE000EF44

/** @brief FPU FPCCR_ASPEN flag */
.equ FPU_FPCCR_ASPEN,  0x80000000
/** @brief FPU FPCCR_LSPEN flag */
.equ FPU_FPCCR_LSPEN,  0x40000000
/** @brief FPU FPCCR_MONRDY flag */
.equ FPU_FPCCR_MONRDY, 0x00000100
/** @brief FPU FPCCR_BFRDY flag */
.equ FPU_FPCCR_BFRDY,  0x80000040
/** @brief FPU FPCCR_MMRDY flag */
.equ FPU_FPCCR_MMRDY,  0x80000020
/** @brief FPU FPCCR_HFRDY flag */
.equ FPU_FPCCR_HFRDY,  0x80000010
/** @brief FPU FPCCR_THREAD flag */
.equ FPU_FPCCR_THREAD, 0x80000008
/** @brief FPU FPCCR_USER flag */
.equ FPU_FPCCR_USER,   0x80000002
/** @brief FPU FPCCR_LSPACT flag */
.equ FPU_FPCCR_LSPACT, 0x80000001

/** @brief FPU CPACR CP10 flag */
.equ FPU_CPACR_CP10, (0x3 << 20)
/** @brief FPU CPACR CP11 flag */
.equ FPU_CPACR_CP11, (0xC << 20)

/** @brief FPU FPCCR enabling value */
.equ FPU_ENABLE_FPCCR_VALUE, (FPU_FPCCR_ASPEN | FPU_FPCCR_LSPEN)
/** @brief FPU CPACR enabling value */
.equ FPU_ENABLE_CPACR_VALUE, (FPU_CPACR_CP10 | FPU_CPACR_CP11)

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

.global __fpu_init

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .text

/**
 * @brief Initializes and enables the FPU and sets it to full compliance mode.
 *
 * @details Initializes the FPU and sets it to full compliance mode. Once 
 * enabled, any FPU instruction will set the CONTROL.FPCA bit to 1. Lazy context
 * save is enabled 
 *
 */
__fpu_init:

    /* Set FPCCR */
    ldr  r0, =FPU_ENABLE_FPCCR_VALUE
    ldr  r1, =FPU_FPCCR_ADDR
    str  r0, [r1]

    /* Set CPACR */
    ldr r1, =GEN_CPACR_ADDR
    ldr r0, [r1]
    orr r0, r0, #FPU_ENABLE_CPACR_VALUE
    str r0, [r1]

    dsb
    isb

    bx lr
/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
