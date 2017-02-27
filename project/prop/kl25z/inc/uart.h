#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>

#define BAUD_RATE (115200)

/*
 * \brief uart_configure: configures uart for baud rate
 *
 * \param baud baud rate for uart communications
 * \return success/fail
 *
 */
int8_t uart_configure(uint32_t baud);

/*
 * \brief uart_send_byte: sends one byte through uart communication
 *
 * \param byte the byte to send
 * \return success/fail
 *
 */
int8_t uart_send_byte(uint8_t byte);

/*
 * \brief uart_send_byte_n: send n bytes through uart communication
 *
 * \param bytes array of bytes to send through uart communication
 * \param length length of bytes to send
 * \return success/fail
 *
 */
int8_t uart_send_byte_n(uint8_t * bytes, uint32_t length);

/*
 * \brief uart_receive_byte: blocking receive for one byte of data
 *
 * \return byte received
 *
 */
uint8_t uart_receive_byte();

uint8_t signal_transmit();
#endif
