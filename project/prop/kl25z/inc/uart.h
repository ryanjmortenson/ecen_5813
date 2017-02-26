#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>

// TODO: FIX COMMENTS!!!!

/*
 * \brief my_itoa: used to convert an integer to a string
 *
 * \param str pointer to array to place string into
 * \param data data to be converted to string
 * \param base base of integer when converted to string (16, 10, 8, 2)
 * \return pointer to input param str
 *
 */
int8_t uart_configure(uint32_t baud);

/*
 * \brief my_atoi: used to convert an ASCII character sequence into an integer
 *
 * \param str pointer to string for conversion
 * \return fail result or pointer to converted string
 *
 */
int8_t uart_send_byte(uint8_t byte);

/*
 * \brief big_to_little32: used to convert an array from big endian to little endian
 *
 * \param data pointer to data for conversion from big endian to little endian
 * \param length length of data to convert
 * \return converted integer or failure
 *
 */
int8_t uart_send_byte_n(uint8_t * byte, uint32_t length);

/*
 * \brief little_to_big32: used to convert an array from little endian to big endian
 *
 * \param data pointer to data for conversion from little endian to big endian
 * \param length length of data to convert
 * \return pass/fail
 *
 */
uint8_t uart_receive_byte();

#endif
