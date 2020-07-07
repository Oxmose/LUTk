/*******************************************************************************
 * @file stddef.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 04/10/2017
 *
 * @version 1.0
 *
 * @brief Standard definitions for the kernel.
 *
 * @details Standard definitions for the kernel. Contains the UTK error codes
 * definition, and some types definitions..
 ******************************************************************************/

#ifndef __TYPES_STDDEF_H__
#define __TYPES_STDDEF_H__

#include "stdint.h"
#include "config.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/** @brief Kernel's NULL definition. */
#define NULL ((void*)0)

#ifndef __SIZE_TYPE__
#error __SIZE_TYPE__ not defined
#endif

/**
 * @brief Defines size_t type as a renaming for __SIZE_TYPE__.
 */
typedef __SIZE_TYPE__ size_t;

/**
 * @brief Defines uintptr_t type as address type.
 */
#ifdef ARCH_64_BITS
typedef uint64_t uintptr_t;
#endif
#ifdef ARCH_32_BITS
typedef uint32_t uintptr_t;
#endif


/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

#endif /* #ifndef __TYPES_STDDEF_H__ */