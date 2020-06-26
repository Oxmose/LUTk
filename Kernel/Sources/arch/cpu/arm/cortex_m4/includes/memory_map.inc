/*******************************************************************************
 * @file memory_map.inc
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 24/06/2020
 *
 * @version 1.0
 *
 * @brief Cortex M4 memory layout.
 *
 * @details Cortex M4 memory layout. This module contains the addresses used to
 * access memory mapped components of the core.
 ******************************************************************************/

/*******************************************************************************
 * General control registers
 ******************************************************************************/

.equ GEN_CPACR_ADDR, 0xE000ED88

/* System control block registers */
.equ GEN_SCB_AIRCR_ADDR, 0xE000ED0C
