/*******************************************************************************
 * @file cpu_timer.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 04/07/2020
 *
 * @version 1.0
 *
 * @brief CPU timers module definitions.
 *
 * @details CPU timers module definitions. This module contains the routines 
 * used by the kernel to manage the CPU timers. On architectures that do not
 * propose CPU timers, those functions should return an error.
 ******************************************************************************/

#ifndef __CPU_CPU_TIMER_H__
#define __CPU_CPU_TIMER_H__

#include "error_types.h"
#include "stdint.h"

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
 * @brief Enables the CPU timer.
 * 
 * @details Enables the CPU timer using the reset of last set frequency.
 * 
 * @param[in] int_enable When set to 0, the timer's ticks will not generate 
 * interrupt. If set to a non null value, each tick will raise an interrupt.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E cpu_timer_enable(const uint8_t int_enable);

/**
 * @brief Disables the CPU timer.
 * 
 * @details Disables the CPU timer.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E cpu_timer_disable(void);

/**
 * @brief Sets the CPU timer tick frequency.
 * 
 * @details Sets the CPU timer tick frequency. When interrupts are enabled, this
 * corresponds to the interrupt frequency.
 * 
 * @param[in] freq The desired timer's tick frequency in Hz.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E cpu_timer_set_frequency(const uint32_t freq);

/**
 * @brief Gets the CPU timer tick frequency.
 * 
 * @details Gets the CPU timer tick frequency. When interrupts are enabled, this
 * corresponds to the interrupt frequency.
 * 
 * @param[out] freq The pointer to store the currently set timer's tick 
 * frequency in Hz.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E cpu_timer_get_frequency(uint32_t* freq);


#endif /* #ifndef __CPU_CPU_TIMER_H__ */