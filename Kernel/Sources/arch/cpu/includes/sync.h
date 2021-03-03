/*******************************************************************************
 * @file sync.h
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

#ifndef __CPU_SYNC_H__
#define __CPU_SYNC_H__

#include "stdint.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

struct CRITICAL_STRUCT
{
    uint8_t int_state;
};

typedef struct CRITICAL_STRUCT CRITICAL_STRUCT_T;

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

void enter_critical(CRITICAL_STRUCT_T* crit);

void exit_critical(CRITICAL_STRUCT_T* crit);

#endif /* #ifndef __CPU_SYNC_H__ */