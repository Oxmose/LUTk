/*******************************************************************************
 * @file cpu_api.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 25/06/2020
 *
 * @version 1.0
 *
 * @brief CPU API definitions.
 *
 * @details CPU API definitions. This module contains the routines used by the 
 * kernel to access the CPU and use its features.
 ******************************************************************************/

#ifndef __CPU_CPU_API_H__
#define __CPU_CPU_API_H__

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

/**
 * @brief Full memory barrier.
 * 
 * @details Full memory barrier, both intended to synchronize for data and 
 * instructions barrier.
 */
void cpu_mem_barrier(void);

#endif /* #ifndef __CPU_CPU_API_H__ */