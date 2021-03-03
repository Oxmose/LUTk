/*******************************************************************************
 * @file string.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 04/10/2017
 *
 * @version 1.0
 *
 * @brief Kernel's string library.
 * 
 * @details Kernel's string library.
 ******************************************************************************/

#ifndef __LIB_STRING_H__
#define __LIB_STRING_H__

#include "stddef.h"

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
 * @brief Fill block of memory.
 * 
 * @details Sets the first num bytes of the block of memory pointed by ptr to 
 * the specified value (interpreted as an unsigned char).
 * 
 * @param[out] ptr Pointer to the block of memory to fill.
 * @param[in] value Value to be set. The value is passed as an int, but the function 
 * fills the block of memory using the unsigned char conversion of this value.
 * @param[in] num Number of bytes to be set to the value.
 */
void* memset(void* ptr, int value, size_t num);

#endif /* #ifndef __LIB_STRING_H__ */