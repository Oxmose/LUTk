/*******************************************************************************
 * @file int_vector.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 28/06/2020
 *
 * @version 1.0
 *
 * @brief Kernel's interrupt vector handlers for the Cortex M4 CPU.
 *
 * @details Kernel's interrupt vector handlers for the Cortex M4 CPU.
 ******************************************************************************/
.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

#include "interrupts.inc"

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

.extern kernel_global_interrupt_handler

/*******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/

.global __exc_nmi_handler
.global __exc_hardfault_handler
.global __exc_mpu_handler   
.global __exc_bus_handler
.global __exc_usage_handler
.global __exc_undef_handler
.global __exc_svc_handler
.global __exc_debug_handler
.global __exc_pensv_handler
.global __sys_tick_handler

.global __extint_0
.global __extint_1
.global __extint_2
.global __extint_3
.global __extint_4
.global __extint_5
.global __extint_6
.global __extint_7
.global __extint_8
.global __extint_9
.global __extint_10
.global __extint_11
.global __extint_12
.global __extint_13
.global __extint_14
.global __extint_15
.global __extint_16
.global __extint_17
.global __extint_18
.global __extint_19
.global __extint_20
.global __extint_21
.global __extint_22
.global __extint_23
.global __extint_24
.global __extint_25
.global __extint_26
.global __extint_27
.global __extint_28
.global __extint_29
.global __extint_30
.global __extint_31
.global __extint_32
.global __extint_33
.global __extint_34
.global __extint_35
.global __extint_36
.global __extint_37
.global __extint_38
.global __extint_39
.global __extint_40
.global __extint_41
.global __extint_42
.global __extint_43
.global __extint_44
.global __extint_45
.global __extint_46
.global __extint_47
.global __extint_48
.global __extint_49
.global __extint_50
.global __extint_51
.global __extint_52
.global __extint_53
.global __extint_54
.global __extint_55
.global __extint_56
.global __extint_57
.global __extint_58
.global __extint_59
.global __extint_60
.global __extint_61
.global __extint_62
.global __extint_63
.global __extint_64
.global __extint_65
.global __extint_66
.global __extint_67
.global __extint_68
.global __extint_69
.global __extint_70
.global __extint_71
.global __extint_72
.global __extint_73
.global __extint_74
.global __extint_75
.global __extint_76
.global __extint_77
.global __extint_78
.global __extint_79
.global __extint_80
.global __extint_81
.global __extint_82
.global __extint_83


/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .text,"ax",%progbits

.type __exc_undef_handler, %function
__exc_undef_handler:
    b __exc_undef_handler

.type __global_int_entry, %function
__global_int_entry:
    /* Save non saved registers */
    push {r4-r11,lr}
    mov  r1, sp
    add  r1, r1, 36
    mov  r2, sp
    bl   kernel_global_interrupt_handler
    pop  {r4-r11,pc}

.type __exc_nmi_handler, %function
__exc_nmi_handler:    
    mov r0, #0
    b    __global_int_entry

.type __exc_hardfault_handler, %function
__exc_hardfault_handler:
    mov r0, #1
    b    __global_int_entry

.type __exc_mpu_handler, %function
__exc_mpu_handler:    
    mov r0, #2
    b    __global_int_entry

.type __exc_bus_handler, %function
__exc_bus_handler:
    mov r0, #0
    b    __global_int_entry   

.type __exc_usage_handler, %function
__exc_usage_handler:

.type __exc_svc_handler, %function
__exc_svc_handler:
    mov r0, #INT_SYS_CALL_ID
    b    __global_int_entry

.type __exc_debug_handler, %function
__exc_debug_handler:

.type __exc_pensv_handler, %function
__exc_pensv_handler:

.type __sys_tick_handler, %function
__sys_tick_handler:
    mov r0, #INT_SYS_TICK_ID
    b    __global_int_entry

__extint_0:
__extint_1:
__extint_2:
__extint_3:
__extint_4:
__extint_5:
__extint_6:
__extint_7:
__extint_8:
__extint_9:
__extint_10:
__extint_11:
__extint_12:
__extint_13:
__extint_14:
__extint_15:
__extint_16:
__extint_17:
__extint_18:
__extint_19:
__extint_20:
__extint_21:
__extint_22:
__extint_23:
__extint_24:
__extint_25:
__extint_26:
__extint_27:
__extint_28:
__extint_29:
__extint_30:
__extint_31:
__extint_32:
__extint_33:
__extint_34:
__extint_35:
__extint_36:
__extint_37:
__extint_38:
__extint_39:
__extint_40:
__extint_41:
__extint_42:
__extint_43:
__extint_44:
__extint_45:
__extint_46:
__extint_47:
__extint_48:
__extint_49:
__extint_50:
__extint_51:
__extint_52:
__extint_53:
__extint_54:
__extint_55:
__extint_56:
__extint_57:
__extint_58:
__extint_59:
__extint_60:
__extint_61:
__extint_62:
__extint_63:
__extint_64:
__extint_65:
__extint_66:
__extint_67:
__extint_68:
__extint_69:
__extint_70:
__extint_71:
__extint_72:
__extint_73:
__extint_74:
__extint_75:
__extint_76:
__extint_77:
__extint_78:
__extint_79:
__extint_80:
__extint_81:
__extint_82:
__extint_83:

__placeholder_func:
    b __placeholder_func

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
