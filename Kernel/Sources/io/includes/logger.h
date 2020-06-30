/*******************************************************************************
 * @file logger.h
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 29/06/2020
 *
 * @version 1.0
 *
 * @brief Kernel logger module.
 *
 * @details Kernel logger module. This module is used to report info, warnings
 * and errors happening in the kernel.
 ******************************************************************************/

#ifndef __IO_LOGGER_H__
#define __IO_LOGGER_H__

#include "error_types.h"
#include "stddef.h"
#include "config.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

struct LOGGER_SETTINGS
{
    void(*logger_buffer_write)(const char* str, const size_t length);
};
typedef struct LOGGER_SETTINGS LOGGER_SETTINGS_T;

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

ERROR_CODE_E logger_init(const LOGGER_SETTINGS_T* settings);

#if KERNEL_LOG_LEVEL >= INFO_LOG_LEVEL
    /** 
     * @brief Logs an information message to the log buffer.
     * 
     * @details Logs an information message to the log buffer. The logger must 
     * be initialized before calling this function. Otherwise thins function has
     * no effect.
     * 
     * @param[in] msg The message to log.
     * @param[in] data The data to log.
     * @param[in] data_size The size of the data to log.
     * @param[in] state The state to log.
     */
    void KERNEL_LOG_INFO(const char* msg, const void* data, 
                         const size_t data_size, const ERROR_CODE_E state);
#else 
    #define KERNEL_LOG_INFO(a, b, c, d) ({(void)a; (void)b; (void)c; (void)d;})
#endif
#if KERNEL_LOG_LEVEL >= WARNING_LOG_LEVEL
    /** 
     * @brief Logs a warning message to the log buffer.
     * 
     * @details Logs an warning message to the log buffer. The logger must 
     * be initialized before calling this function. Otherwise thins function has
     * no effect.
     * 
     * @param[in] msg The message to log.
     * @param[in] data The data to log.
     * @param[in] data_size The size of the data to log.
     * @param[in] state The state to log.
     */
    void KERNEL_LOG_WARNING(const char* msg, const void* data, 
                            const size_t data_size, const ERROR_CODE_E state);
#else 
    #define KERNEL_LOG_WARNING(a, b, c, d) ({(void)a; (void)b; (void)c; (void)d;})
#endif
#if KERNEL_LOG_LEVEL >= ERROR_LOG_LEVEL
    /** 
     * @brief Logs an error message to the log buffer.
     * 
     * @details Logs an error message to the log buffer. The logger must 
     * be initialized before calling this function. Otherwise thins function has
     * no effect.
     * 
     * @param[in] msg The message to log.
     * @param[in] data The data to log.
     * @param[in] data_size The size of the data to log.
     * @param[in] state The state to log.
     */
    void KERNEL_LOG_ERROR(const char* msg, const void* data, 
                          const size_t data_size, const ERROR_CODE_E state);
#else 
    #define KERNEL_LOG_ERROR(a, b, c, d) ({(void)a; (void)b; (void)c; (void)d;})
#endif

#endif /* #ifndef __IO_LOGGER_H__ */



