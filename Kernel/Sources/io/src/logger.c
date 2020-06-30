/*******************************************************************************
 * @file logger.c
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

#include "error_types.h"
#include "config.h"
#include "logger.h"

/*******************************************************************************
 * Private data
 ******************************************************************************/

/** @brief Stores the logger settings */
LOGGER_SETTINGS_T logger_settings;

/** @brief Hexadecimal table character */
const char hex_table[] =
     {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

/** @brief Stores the logger initialization state. */
uint8_t logger_init_state = 0;

/*******************************************************************************
 * Private functions
 ******************************************************************************/

static void byte_to_str(char* buff, const char val)
{
    buff[0] = hex_table[val & 0xF];
    buff[1] = hex_table[(val >> 8) & 0xF];
}

static void state_to_str(char* buff, const ERROR_CODE_E state)
{
    uint32_t val  = (uint32_t)(void*)state;
    uint32_t size;
    for(size = 0; size < sizeof(ERROR_CODE_E); ++size)
    {
        buff[size] = hex_table[(val >> (8 * size)) & 0xF];
    }
    for(; size < 4; ++size)
    {
        buff[size] = 0;
    }
}

#ifndef strlen
static size_t strlen(const char* str)
{
    size_t size = 0;
    while(*str++)
    {
        ++size;
    }
    return size;
}
#endif 

static void logger_log(const char* msg, const void* data, 
                       const size_t data_size, const ERROR_CODE_E state)
{
    size_t i;
    char   buf[4];

    /* Create the error message */
    logger_settings.logger_buffer_write(msg, strlen(msg));
    if(data_size > 0)
    {
        logger_settings.logger_buffer_write(" | Data: ", 9);

        for(i = 0; i < data_size; ++i)
        {
            byte_to_str(buf, *((char*)data++));
            logger_settings.logger_buffer_write(buf, 2);
        }
    }
    logger_settings.logger_buffer_write(" | 0x", 5);
    state_to_str(buf, state);
    logger_settings.logger_buffer_write(buf, strlen(buf));
    logger_settings.logger_buffer_write("\r\n", 2);
}

/*******************************************************************************
 * Public functions
 ******************************************************************************/

ERROR_CODE_E logger_init(const LOGGER_SETTINGS_T* settings)
{
    if(settings == NULL)
    {
        return ERROR_NULL_POINTER;
    }

    logger_settings = *settings;

    logger_init_state = 1;

    return NO_ERROR;
}

#if KERNEL_LOG_LEVEL >= INFO_LOG_LEVEL
void KERNEL_LOG_INFO(const char* msg, const void* data, 
                     const size_t data_size, const ERROR_CODE_E state)
{
    if(logger_init_state != 0)
    {
        /* Create the error message */
        logger_settings.logger_buffer_write("[INFO] ", 7);
        logger_log(msg, data, data_size, state);
    }
}
#endif

#if KERNEL_LOG_LEVEL >= WARNING_LOG_LEVEL
void KERNEL_LOG_WARNING(const char* msg, const void* data, 
                        const size_t data_size, const ERROR_CODE_E state)
{
    if(logger_init_state != 0)
    {
        logger_settings.logger_buffer_write("[WARN] ", 7);
        logger_log(msg, data, data_size, state);
    }
}
#endif

#if KERNEL_LOG_LEVEL >= ERROR_LOG_LEVEL
void KERNEL_LOG_ERROR(const char* msg, const void* data, 
                      const size_t data_size, const ERROR_CODE_E state)
{
    if(logger_init_state != 0)
    {
        logger_settings.logger_buffer_write("[ERROR] ", 8);
        logger_log(msg, data, data_size, state);
    }
}
#endif
