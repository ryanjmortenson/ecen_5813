#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include "MKL25Z4.h"

#define BAUD_RATE (230400)

#define TRANSMIT_READY (UART0_C2 |= UART_C2_TIE_MASK)
#define TRANSMIT_DMA(x) DMA_DSR_BCR2 += x; UART0_C5 |= UART0_C5_TDMAE_MASK;
#define TRANSMIT_DONE (UART0_C2 &= ~UART_C2_TIE_MASK)
#define START_CRITICAL NVIC_DisableIRQ(RTC_Seconds_IRQn);
#define END_CRITICAL NVIC_EnableIRQ(RTC_Seconds_IRQn);

/*
 * \brief uart_configure: configures uart for baud rate
 *
 * \param baud baud rate for uart communications
 *
 */
void uart_configure(uint32_t baud);

/*
 * \brief uart_send_byte: sends one byte through uart communication
 *
 * \param byte the byte to send
 *
 */
void uart_send_byte(uint8_t byte);

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

#endif
