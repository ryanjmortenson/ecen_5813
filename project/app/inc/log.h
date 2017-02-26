#ifndef __LOG_H__
#define __LOG_H__

#include <stdint.h>

#define MAX_INT_LEN (12)
#define INT_STRING "Integer: "
#define DATA_STRING "Data: "
#define SPACE " "
#define HEX_START "0x"

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

#endif
