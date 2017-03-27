#ifndef __NORDIC_H__
#define __NORDIC_H__

#include <stdint.h>
#include "log.h"

#define NRF_STATUS_REG (0x00)
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

uint8_t nrf_read_register(uint8_t reg);
void nrf_write_register(uint8_t reg, uint8_t value);
uint8_t nrf_read_status();
void nrf_write_config(uint8_t config);
uint8_t nrf_read_config();
uint8_t nrf_read_rf_setup();
void nrf_write_rf_setup(uint8_t config);
uint8_t nrf_read_rf_ch();
void nrf_write_rf_ch(uint8_t channel);
void nrf_read_tx_addr(uint8_t * tx_addr);
void nrf_write_tx_addr(uint8_t * tx_addr);
uint8_t nrf_read_fifo_status();
void nrf_flush_tx_fifo();
void nrf_flush_rx_fifo();

#endif // __NORDIC_H__
