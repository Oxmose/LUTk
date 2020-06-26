/*******************************************************************************
 * @file boot.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 23/06/2020
 *
 * @version 1.0
 *
 * @brief Kernel's main entry point for the Cortex M4 CPU.
 *
 * @details Kernel entry point and cpu initialization.
 ******************************************************************************/
.syntax unified

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
.extern _start_bss
.extern _end_bss

/*******************************************************************************
 * EXTERN FUNCTIONS
 ******************************************************************************/
.extern kernel_kickstart
.extern kernel_panic
.extern __bsp_init
.extern __fpu_init
.extern __nvic_init

/*******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/
.global __rst_handler

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .int_vect,"a",%progbits

__rst_vector:
    .word MAIN_STACK_ADDRESS     /* Reset MSP */
    .word __rst_handler          /* Reset PC */
    .word __exc_nmi_handler      
    .word __exc_hardfault_handler
    .word __exc_mem_handler    
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler

.section .boot_code

__rst_handler:
    b __kernel_init

__exc_nmi_handler:
    b __exc_nmi_handler

__exc_hardfault_handler:
    b __exc_hardfault_handler

__exc_mem_handler:
    b __exc_mem_handler

__exc_undef_handler:
    b __exc_undef_handler

/**
 * Initializes the CPU registers at boot time.
 */
__kernel_init:
    /* Init lo registers */
    eor r0, r0
    eor r1, r1
    eor r2, r2
    eor r3, r3
    eor r4, r4
    eor r5, r5
    eor r6, r6
    eor r7, r7
    
    /* Set stack */
    ldr r0, =MAIN_STACK_ADDRESS
    mov sp, r0

    /* Blank BSS */
    ldr r0, =_start_bss
    ldr r1, =_end_bss
    eor r2, r2
__kernel_bss_init:  
    cmp r0, r1 
    beq __kernel_bss_init_end

    str r2, [r0]
    add r2, r2, #4

__kernel_bss_init_end:
    /* Init FPU */
    bl __fpu_init

    /* Initializes NVIC */
    bl __nvic_init

    /* Call BSP initialization */
    bl __bsp_init   

    /* Call kernel kickstart entry point */    
    bl kernel_kickstart

    /* If we returned, raise a kernel panic */
    b kernel_panic


/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
