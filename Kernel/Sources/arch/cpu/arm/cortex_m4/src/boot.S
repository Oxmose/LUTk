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
.cpu cortex-m4
.fpu softvfp
.thumb

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

.equ MAIN_STACK_ADDRESS, 0x20018000

/*******************************************************************************
 * MACRO DEFINE
 ******************************************************************************/

/*******************************************************************************
 * EXTERN DATA
 ******************************************************************************/
.extern _start_bss
.extern _end_bss
.extern _start_init_data
.extern _start_data
.extern _end_data

/*******************************************************************************
 * EXTERN FUNCTIONS
 ******************************************************************************/
.extern kernel_kickstart
.extern kernel_panic
.extern __bsp_init
.extern __fpu_init
.extern __nvic_init

.extern __extint_0
.extern __extint_1
.extern __extint_2
.extern __extint_3
.extern __extint_4
.extern __extint_5
.extern __extint_6
.extern __extint_7
.extern __extint_8
.extern __extint_9
.extern __extint_10
.extern __extint_11
.extern __extint_12
.extern __extint_13
.extern __extint_14
.extern __extint_15
.extern __extint_16
.extern __extint_17
.extern __extint_18
.extern __extint_19
.extern __extint_20
.extern __extint_21
.extern __extint_22
.extern __extint_23
.extern __extint_24
.extern __extint_25
.extern __extint_26
.extern __extint_27
.extern __extint_28
.extern __extint_29
.extern __extint_30
.extern __extint_31
.extern __extint_32
.extern __extint_33
.extern __extint_34
.extern __extint_35
.extern __extint_36
.extern __extint_37
.extern __extint_38
.extern __extint_39
.extern __extint_40
.extern __extint_41
.extern __extint_42
.extern __extint_43
.extern __extint_44
.extern __extint_45
.extern __extint_46
.extern __extint_47
.extern __extint_48
.extern __extint_49
.extern __extint_50
.extern __extint_51
.extern __extint_52
.extern __extint_53
.extern __extint_54
.extern __extint_55
.extern __extint_56
.extern __extint_57
.extern __extint_58
.extern __extint_59
.extern __extint_60
.extern __extint_61
.extern __extint_62
.extern __extint_63
.extern __extint_64
.extern __extint_65
.extern __extint_66
.extern __extint_67
.extern __extint_68
.extern __extint_69
.extern __extint_70
.extern __extint_71
.extern __extint_72
.extern __extint_73
.extern __extint_74
.extern __extint_75
.extern __extint_76
.extern __extint_77
.extern __extint_78
.extern __extint_79
.extern __extint_80
.extern __extint_81
.extern __extint_82
.extern __extint_83

/*******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/
.global __rst_handler
.global __kernel_init

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .int_vect,"a",%progbits
          
.type  __rst_vector, %object
__rst_vector:
    .word MAIN_STACK_ADDRESS     /* Reset MSP */
    .word __rst_handler          /* Reset PC */
    .word __exc_nmi_handler      
    .word __exc_hardfault_handler
    .word __exc_mpu_handler    
    .word __exc_bus_handler
    .word __exc_usage_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_svc_handler
    .word __exc_debug_handler
    .word __exc_undef_handler
    .word __exc_pensv_handler
    .word __sys_tick_handler

    .word __extint_0
    .word __extint_1
    .word __extint_2
    .word __extint_3
    .word __extint_4
    .word __extint_5
    .word __extint_6
    .word __extint_7
    .word __extint_8
    .word __extint_9
    .word __extint_10
    .word __extint_11
    .word __extint_12
    .word __extint_13
    .word __extint_14
    .word __extint_15
    .word __extint_16
    .word __extint_17
    .word __extint_18
    .word __extint_19
    .word __extint_20
    .word __extint_21
    .word __extint_22
    .word __extint_23
    .word __extint_24
    .word __extint_25
    .word __extint_26
    .word __extint_27
    .word __extint_28
    .word __extint_29
    .word __extint_30
    .word __extint_31
    .word __extint_32
    .word __extint_33
    .word __extint_34
    .word __extint_35
    .word __extint_36
    .word __extint_37
    .word __extint_38
    .word __extint_39
    .word __extint_40
    .word __extint_41
    .word __extint_42
    .word __extint_43
    .word __extint_44
    .word __extint_45
    .word __extint_46
    .word __extint_47
    .word __extint_48
    .word __extint_49
    .word __extint_50
    .word __extint_51
    .word __extint_52
    .word __extint_53
    .word __extint_54
    .word __extint_55
    .word __extint_56
    .word __extint_57
    .word __extint_58
    .word __extint_59
    .word __extint_60
    .word __extint_61
    .word __extint_62
    .word __extint_63
    .word __extint_64
    .word __extint_65
    .word __extint_66
    .word __extint_67
    .word __extint_68
    .word __extint_69
    .word __extint_70
    .word __extint_71
    .word __extint_72
    .word __extint_73
    .word __extint_74
    .word __extint_75
    .word __extint_76
    .word __extint_77
    .word __extint_78
    .word __extint_79
    .word __extint_80
    .word __extint_81
    .word __extint_82
    .word __extint_83
    
.section .boot_code,"ax",%progbits
.type __rst_handler, %function
__rst_handler:
    b __kernel_init

/**
 * Initializes the CPU registers at boot time.
 */
.type __kernel_init, %function
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
    add r0, r0, #4
    b __kernel_bss_init

__kernel_bss_init_end:

    /* Copy data from flash */
    ldr r0, =_start_data
    ldr r1, =_end_data
    ldr r2, =_start_init_data
__kernel_data_init:  
    cmp r0, r1 
    beq __kernel_data_init_end
    ldr r3, [r2]
    str r3, [r0]
    add r0, r0, #4
    add r2, r2, #4
    b __kernel_data_init
__kernel_data_init_end:

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
