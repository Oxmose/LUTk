/*******************************************************************************
 * @file string.c
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

#include "string.h"
#include "stddef.h"
#include "stdint.h"
#include "config.h"

/*******************************************************************************
 * Private data
 ******************************************************************************/

/*******************************************************************************
 * Private functions
 ******************************************************************************/

/*******************************************************************************
 * Public functions
 ******************************************************************************/

#if CONFIG_USE_ARCH_LIB == 0
void* memset(void* ptr, int value, size_t num)
{
    char* addr = ptr;
    while(num--)
    {
        *addr++ = (char)value;
    }

    return ptr;
}
#endif