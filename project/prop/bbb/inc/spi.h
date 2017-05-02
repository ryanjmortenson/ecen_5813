#ifndef __SPI_H__
#define __SPI_H__

#define GPIO_NRF_CSN_DISABLE spi_csn_disable();
#define GPIO_NRF_CSN_ENABLE spi_csn_enable();

#include <stdint.h>

/*
 * \brief spi_configure: configures spi for baud rate
 *
 * \param baud baud rate for spi communications
 *
 */
int spi_init();

/*
 * \brief spi_send_byte: sends one byte through spi communication
 *
 * \param byte the byte to send
 *
 */
void spi_send_byte(uint8_t byte);

/*
 * \brief spi_send_byte_n: send n bytes through spi communication
 *
 * \param bytes array of bytes to send through spi communication
 * \param length length of bytes to send
 *
 */
void spi_send_byte_n(uint8_t * bytes, uint32_t length);

/*
 * \brief spi_receive_byte: blocking receive for one byte of data
 *
 * \return byte received
 *
 */
uint8_t spi_receive_byte();

/*
 * \brief spi_shutdown: clean up file decriptors for BBB
 *
 */
void spi_shutdown();

/*
 * \brief spi_csn_enable: set the csn pin low
 *
 */
void spi_csn_enable();

/*
 * \brief spi_csn_disable: set the csn pin high
 *
 */
void spi_csn_disable();

#endif
