#ifndef __LOG_H__
#define __LOG_H__

#include <stdint.h>

#define MAX_INT_LEN (12)
#define INT_STRING "Integer: "
#define DATA_STRING "Data: "
#define SPACE " "
#define HEX_START "0x"

#ifdef VERBOSE
#define LOG_RAW_DATA(bytes, length) log_data((uint8_t *)bytes, length)
#define LOG_RAW_STRING(str) log_string((int8_t *)str)
#define LOG_RAW_INT(integer) log_integer(integer)
#define LOG_RAW_FLUSH() log_flush()
#define LOG_ITEM()
#else
#define LOG_RAW_DATA(bytes, length)
#define LOG_RAW_STRING(str)
#define LOG_RAW_INT(integer)
#define LOG_RAW_FLUSH()
#define LOG_ITEM()
#endif // VERBOSE

// Enum of log ids used in log item structure
typedef enum log_id
{
	LOG_ID_LOGGER_INITIALZED,
	LOG_ID_GPIO_INITIALZED,
	LOG_ID_SYSTEM_INITIALIZED,
	LOG_ID_SYSTEM_HALTED,
	LOG_ID_INFO,
	LOG_ID_WARNING,
	LOG_ID_ERROR,
	LOG_ID_DATA_RECEIVED,
	LOG_ID_DATA_ANALYSIS_STARTED,
	LOG_ID_DATA_ALPHA_COUNT,
	LOG_ID_DATA_NUMERIC_COUNT,
	LOG_ID_DATA_PUNCTUATION_COUNT,
	LOG_ID_DATA_MISC_COUNT,
	LOG_ID_DATA_ANALYSIS_COMPLETED
} log_id_t;

// An item to be logged
typedef struct log_item_struct
{
  uint8_t log_id;
  uint8_t log_length;
  uint8_t * payload;
} log_item_t;

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
 * \brief log_item: creates a log item
 * \param log_item: double pointer to log item structure to be destroyed
 * \return: success/fail
 *
 */
uint8_t log_item(log_item_t * item);

#endif // __LOG_H__
