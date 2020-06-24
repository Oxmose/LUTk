  
/*******************************************************************************
 * @file boot.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 23/06/2020
 *
 * @version 1.0
 *
 * @brief Kernel's main entry file.
 *
 * @details Kernel entry point and cpu initialization
 ******************************************************************************/

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

.equ MAIN_STACK_ADDRESS, 0x20001000

/*******************************************************************************
 * MACRO DEFINE
 ******************************************************************************/

/*******************************************************************************
 * EXTERN DATA
 ******************************************************************************/

/*******************************************************************************
 * EXTERN FUNCTIONS
 ******************************************************************************/
.extern kernel_kickstart

/*******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/
.global __rst_handler

/*******************************************************************************
 * CODE
 ******************************************************************************/

.section .int_vect,"a",%progbits

__rst_vector:
    .word MAIN_STACK_ADDRESS
    .word __rst_handler
    .word __exc_nmi_handler
    .word __exc_hwfault_handler
    .word __exc_mem_handler
    .word 0
    .word 0
    .word 0

.section .boot_code

__rst_handler:
    bl __cpu_init
    b  kernel_kickstart

__exc_nmi_handler:
    b __exc_nmi_handler

__exc_hwfault_handler:
    b __exc_hwfault_handler

__exc_mem_handler:
    b __exc_mem_handler


/**
 * Initializes the CPU registers at boot time.
 */

__cpu_init:
    /* Init lo registers */
    movs r0, #0
    movs r1, #1
    movs r2, #2
    movs r3, #3
    movs r4, #4
    movs r5, #5
    movs r6, #6
    movs r7, #7
    
    /* Set stack */
    ldr r0, =MAIN_STACK_ADDRESS
    mov sp, r0

    bx lr



/*******************************************************************************
; DATA
 ******************************************************************************/

/**
 * CPU Stacks
 */
main_stack: .word MAIN_STACK_ADDRESS

.section .data
