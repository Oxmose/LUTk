/*******************************************************************************
 * @file sync.c
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 07/07/2020
 *
 * @version 1.0
 *
 * @brief CPU synchronization primitives definitions.
 *
 * @details CPU synchronization primitives definitions. This module contains the
 * routines used by the kernel to synchronize or ensure mutual exclusion.
 ******************************************************************************/

#include "sync.h"
#include "sync_def.h"
#include "stdint.h"
#include "cpu_api.h"

/*******************************************************************************
 * Private data
 ******************************************************************************/

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/*******************************************************************************
 * Public functions
 ******************************************************************************/

void enter_critical(CRITICAL_STRUCT_T* crit)
{
    crit->int_state = disable_interrupt();
}

void exit_critical(CRITICAL_STRUCT_T* crit)
{
    if(crit->int_state)
    {
        enable_interrupt();
    }
}