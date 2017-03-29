#ifndef __NORDIC_H__
#define __NORDIC_H__

#include <stdint.h>
#include "log.h"

#define NRF_STATUS_REG (0x00)
#define NRF_FIFO_STATUS_REG (0x17)
#define NRF_RF_CH_REG (0x05)
#define NRF_RF_SETUP_REG (0x06)
#define NRF_CONFIG_REG (0x07)
#define NRF_TX_ADDR_REG (0x10)
#define NRF_TXADDR_LEN (5)
#define NRF_POWER_UP (1)
#define NRF_POWER_DOWN (0)
#define NRF_POWER_UP_MASK (0x02)
#define NRF_NO_OP (0xff)
#define NRF_WRITE_MASK (0x20)
#define NRF_FLUSH_RX (0xe1)
#define NRF_FLUSH_TX (0xe2)

/*
 * \brief nrf_read_register: reads a register from the nrf module using spi
 *
 * \param reg: register to read
 *
 * \return: value from register
 *
 */
uint8_t nrf_read_register(uint8_t reg);

/*
 * \brief nrf_write_register: writes a register on the nrf module using spi
 *
 * \param reg: register to write
 * \param value: value to write
 *
 */
void nrf_write_register(uint8_t reg, uint8_t value);

/*
 * \brief nrf_read_status: reads the status register on the nrf module using spi
 *
 * \return: status value
 *
 */
uint8_t nrf_read_status();

/*
 * \brief nrf_write_config: writes the config register on the nrf module using spi
 *
 * \param config: config value to write to register
 *
 */
void nrf_write_config(uint8_t config);

/*
 * \brief nrf_read_config: reads the config register on the nrf module using spi
 *
 * \return: config value
 *
 */
uint8_t nrf_read_config();

/*
 * \brief nrf_write_rf_setup: writes the rf_setup register on the nrf module using spi
 *
 * \param value: value of rf setup register
 *
 */
void nrf_write_rf_setup(uint8_t config);

/*
 * \brief nrf_read_rf_setup: reads the rf_setup register on the nrf module using spi
 *
 * \return: rf setup value
 *
 */
uint8_t nrf_read_rf_setup();

/*
 * \brief nrf_write_rf_ch: writes the rf_ch register on the nrf module using spi
 *
 * \param rf_ch: rf_ch value to write to register
 *
 */
void nrf_write_rf_ch(uint8_t channel);

/*
 * \brief nrf_read_rf_ch: reads the rf_ch register on the nrf module using spi
 *
 * \return: value of rf_ch register
 *
 */
uint8_t nrf_read_rf_ch();

/*
 * \brief nrf_write_tx_addr: writes the tx_addr register on the nrf module using spi
 *
 * \param tx_addr: a uint8_t array of 5 elements to write to tx_addr
 *
 */
void nrf_write_tx_addr(uint8_t * tx_addr);

/*
 * \brief nrf_read_tx_addr: reads the tx_addr register on the nrf module using spi
 *
 * \param tx_addr: a uint8_t array of that can hold 5 elements from tx_addr
 *
 */
void nrf_read_tx_addr(uint8_t * tx_addr);

/*
 * \brief nrf_read_fifo_status: reads the fifo_status register on the nrf module using spi
 *
 * \return: fifo status
 *
 */
uint8_t nrf_read_fifo_status();

/*
 * \brief nrf_flush_tx_fifo: flush the tx fifo
 *
 */
void nrf_flush_tx_fifo();

/*
 * \brief nrf_flush_rx_fifo: flush the rx fifo
 *
 */
void nrf_flush_rx_fifo();

#endif // __NORDIC_H__
