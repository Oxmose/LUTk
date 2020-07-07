/*******************************************************************************
 * @file cpu_timer_def.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 04/07/2020
 *
 * @version 1.0
 *
 * @brief ARM Cortex M4 system timer definitions.
 *
 * @details ARM Cortex M4 system timer definitions. This module contains the 
 * definitions used to control the M4 system timer.
 ******************************************************************************/

#ifndef __CPU_CPU_TIMER_ARM_CORTEX_M4_DEF_H__
#define __CPU_CPU_TIMER_ARM_CORTEX_M4_DEF_H__

#include "error_types.h"
#include "stdint.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/** @brief System Tick Control Register address */
#define STK_CTRL_ADDRESS  0xE000E010
#define STK_CTRL_REGISTER ((volatile uint32_t*)STK_CTRL_ADDRESS)

/** @brief System Tick Load Register address */
#define STK_LOAD_ADDRESS  0xE000E014
#define STK_LOAD_REGISTER ((volatile uint32_t*)STK_LOAD_ADDRESS)

/** @brief System Tick Value Register address */
#define STK_VAL_ADDRESS   0xE000E018
#define STK_VAL_REGISTER  ((volatile uint32_t*)STK_VAL_ADDRESS)

/** @brief System Tick Calibration Register address */
#define STK_CALI_ADDRESS  0xE000E01C
#define STK_CALI_REGISTER ((volatile uint32_t*)STK_CALI_ADDRESS)

/** @brief STK_CTRL CLKSOURCE flag, sets the tick source as AHB / 8. */
#define STK_CTRL_CLKSRC_AHB_8 0x00000000
/** @brief STK_CTRL CLKSOURCE flag, sets the tick source as AHB undivided. */
#define STK_CTRL_CLKSRC_AHB   0x00000004
/** @brief STK_CTRL TICKINT flag, enables the tick interrupt generation. */
#define STK_CTRL_TICKINT      0x00000002
/** @brief STK_CTRL ENABLE flag, enables the timer. */
#define STK_CTRL_EN           0x00000001

/** @brief Maximal load value for the system tick. */
#define STK_LOAD_MAX_VALUE 0x00FFFFFF


/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

#endif /* #ifndef __CPU_CPU_TIMER_ARM_CORTEX_M4_DEF_H__ */