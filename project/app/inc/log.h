#ifndef __LOG_H__
#define __LOG_H__

#include <stdint.h>
#include "log_item.h"

#define INT_STRING "Integer: "
#define DATA_STRING "Data: "

#ifdef VERBOSE
#define LOG_RAW_DATA(bytes, length) log_data((uint8_t *)bytes, length)
#define LOG_RAW_STRING(str) log_string((int8_t *)str)
#define LOG_RAW_INT(integer) log_integer(integer)
#define LOG_RAW_FLUSH() log_flush()
#define LOG_ITEM(item) log_item(item)
#define CREATE_ITEM_STRING(item, log_id, buf) create_log_item(&item, \
                                                              log_id, \
                                                              (uint8_t *)buf, \
                                                              LOG_ITEM_STRING)
#define CREATE_ITEM_DATA(item, log_id, buf, len) create_log_item(&item, \
                                                                 log_id, \
                                                                 (uint8_t *)buf, \
                                                                 len)
#else // VERBOSE
#define LOG_RAW_DATA(bytes, length)
#define LOG_RAW_STRING(str)
#define LOG_RAW_INT(integer)
#define LOG_RAW_FLUSH()
#define LOG_ITEM(item)
#define CREATE_ITEM_STRING(item, log_id, buf)
#define CREATE_ITEM_DATA(item, log_id, buf, len)
#endif // VERBOSE


/*
 * \brief log_data: logs bytes in hex prepending string DATA_STRING to
 *                  output
 *
 * \param bytes array of points to print to log
 * \param length length of byte array
 * \return success/failure
 *
 */
int8_t log_data(uint8_t * bytes, uint8_t length);

/*
 * \brief log_string: logs a c-string expects a null terminator
 *
 * \param str pointer to string to be logged
 * \return success/failure
 *
 */
int8_t log_string(int8_t * str);

/*
 * \brief log_integer: logs an integer prepending INT_STRING to output
 *
 * \param integer integer to convert and print
 * \return success/failure
 *
 */
int8_t log_integer(int32_t integer);

/*
 * \brief log_flush: blocks until log is finished printing
 *
 */
void log_flush();

/*
 * \brief log_item: initialize logging system
 * \return: success/fail
 *
 */
uint8_t log_init();

/*
 * \brief log_destroy: destroy logs
 * \return: success/fail
 *
 */
void log_destroy();

#endif // __LOG_H__
