/*******************************************************************************
 * @file cpu_timer.c
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

#include "error_types.h"
#include "stdint.h"
#include "stddef.h"
#include "cpu_timer.h"
#include "cpu_timer_def.h"
#include "clocks.h"
#include "logger.h"

/*******************************************************************************
 * Private data
 ******************************************************************************/

/** @brief Stores the currently used tick frequency of the CPU timer. */
static uint32_t tick_freq = 0;

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/*******************************************************************************
 * Public functions
 ******************************************************************************/

ERROR_CODE_E cpu_timer_enable(const uint8_t int_enable)
{
    /* Sets the clock source selection as processor clock and enable timer */
    *STK_CTRL_REGISTER = *STK_CTRL_REGISTER  | 
                         STK_CTRL_CLKSRC_AHB | 
                         STK_CTRL_EN         | 
                         ((int_enable != 0) ? STK_CTRL_TICKINT : 0);

    return NO_ERROR;
}

ERROR_CODE_E cpu_timer_disable(void)
{
    /* Disables the interrupts and timer */
    *STK_CTRL_REGISTER = *STK_CTRL_REGISTER & ~(STK_CTRL_EN | STK_CTRL_TICKINT);

    return NO_ERROR;
}

ERROR_CODE_E cpu_timer_set_frequency(const uint32_t freq)
{
    uint32_t     tmp_val;
    ERROR_CODE_E error;

    /* Check boundaries */
    if(freq < 6 || freq > 10000)
    {
        KERNEL_LOG_ERROR("Requested CPU timer frequency out of bound", 
                         NULL, 
                         0, 
                         ERROR_INVALID_PARAM);
        return ERROR_INVALID_PARAM;
    }

    /* Get CPU freq */
    error = bsp_get_cpu_freq(&tmp_val); 
    if(error != NO_ERROR)
    {
        return error;
    }

    /* Compute the number of clock ticks required */
    tmp_val = tmp_val / freq;

    /* Sets the register */
    *STK_LOAD_REGISTER = tmp_val;

    tick_freq = freq;

    return NO_ERROR;
}

ERROR_CODE_E cpu_timer_get_frequency(uint32_t* freq)
{
    if(freq == NULL)
    {
        return ERROR_NULL_POINTER;
    }

    *freq = tick_freq;

    return NO_ERROR;
}
