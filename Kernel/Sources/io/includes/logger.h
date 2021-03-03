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

/** @brief Logger settings structure that contains all the data needed to
 * manage logging process.
 */
struct LOGGER_SETTINGS
{
    /** 
     * @brief Hook used to send logging data to the desired outout.
     * 
     * @param[in] str The string to log.
     * @param[in] length The length of the string to log.
     */
    void(*logger_buffer_write)(const char* str, const size_t length);
};

/** @brief Short hand for struct LOGGER_SETTINGS. */
typedef struct LOGGER_SETTINGS LOGGER_SETTINGS_T;

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

/** 
 * @brief Initializes the logger.
 * 
 * @details Initializes the kernel logger by setting the output hook and 
 * other settings choosen by the user.
 * 
 * @param[in] settings The settings used to initialize the logger.
 * 
 * @return NO_ERROR is returned in case of success. Otherwise an error code is
 * returned. Please refer to the list of the standard error codes.
 */
ERROR_CODE_E kernel_logger_init(const LOGGER_SETTINGS_T* settings);

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



