/*******************************************************************************
 * @file bsp_defs.inc
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 24/06/2020
 *
 * @version 1.0
 *
 * @brief STM32 F401RE global value definitions.
 *
 * @details Cortex M4 memory layout. This module contains the values used by the
 * BSP to configured its components.
 ******************************************************************************/

/*******************************************************************************
 * Power related values
 ******************************************************************************/
.equ PWR_VOLTAGE_REGULATOR_SCALE2, 0x00008000

/*******************************************************************************
 * Flash related values
 ******************************************************************************/
.equ FLASH_KERNEL_LATENCY, 0x00000002
