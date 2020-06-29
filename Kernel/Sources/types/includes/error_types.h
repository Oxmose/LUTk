/*******************************************************************************
 * @file error_types.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 24/06/2020
 *
 * @version 1.0
 *
 * @brief Kernel error types definitions.
 *
 * @details Kernel error types definitions. This modules defines the structures,
 * enumerations and macros used in case of error.
 ******************************************************************************/

#ifndef __TYPES_ERROR_TYPES_H__
#define __TYPES_ERROR_TYPES_H__

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

/**
 * @brief Enumerate the possible errors codes happening in the kernel.
 */
enum ERROR_CODE
{
    /** @brief No error. */
    NO_ERROR            = 0,
    /** @brief Invalid parameter error. */
    ERROR_INVALID_PARAM = 1,
    /** @brief Invalid component anlready initialized error. */
    ERROR_ALREADY_INIT  = 2,
    /** @brief Invalid compoment needs initialization error. */
    ERROR_NEED_INIT     = 3,
    /** @brief Invalid used NULL pointer error. */
    ERROR_NULL_POINTER  = 4,
    /** @brief Invalid divided by zero error. */
    ERROR_DIV_BY_ZERO   = 5,
};

/**
 * @brief Short name for enum ERROR_CODES.
 */
typedef enum ERROR_CODE ERROR_CODE_E;

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

#endif /* #ifndef __TYPES_ERROR_TYPES_H__ */