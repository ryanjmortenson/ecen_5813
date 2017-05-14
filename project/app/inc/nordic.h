#ifndef __NORDIC_H__
#define __NORDIC_H__

#include <stdint.h>
#include "log.h"

#define NRF_STATUS_REG (0x07)
#define NRF_FIFO_STATUS_REG (0x17)
#define NRF_RF_CH_REG (0x05)
#define NRF_RF_SETUP_REG (0x06)
#define NRF_CONFIG_REG (0x00)
#define NRF_TX_ADDR_REG (0x10)
#define NRF_TXADDR_LEN (5)
#define NRF_POWER_UP (1)
#define NRF_POWER_DOWN (0)
#define NRF_POWER_UP_MASK (0x02)
#define NRF_NO_OP (0xff)
#define NRF_WRITE_MASK (0x20)
#define NRF_FLUSH_TX (0xe1)
#define NRF_FLUSH_RX (0xe2)
#define NRF_W_TX_PAYLOAD (0xa0)
#define NRF_R_RX_PAYLOAD (0x61)
#define NRF_RX_PW_P0 (0x11)
#define NRF_RX_PW_P1 (0x12)
#define NRF_RX_PW_P2 (0x13)
#define NRF_RX_PW_P3 (0x14)
#define NRF_RX_PW_P4 (0x15)
#define NRF_RX_PW_P5 (0x16)

// The following are bit fields for the following registers STATUS, CONFIG,
// RF_SETUP, RF_CH, FIFO_STATUS

// STATUS register bit field
typedef union {
  struct {
    uint8_t tx_ful   : 1;
    uint8_t rx_p_no  : 3;
    uint8_t max_rt   : 1;
    uint8_t tx_ds    : 1;
    uint8_t rx_dr    : 1;
    uint8_t reserved : 1;
  } status;
  uint8_t reg;
} status_reg;

// CONFIG register bit field
typedef union {
  struct {
    uint8_t prim_rx     : 1;
    uint8_t pwr_up      : 1;
    uint8_t crco        : 1;
    uint8_t en_crc      : 1;
    uint8_t mask_max_rt : 1;
    uint8_t mask_tx_ds  : 1;
    uint8_t maxk_rx_dr  : 1;
    uint8_t reserved    : 1;
  } config;
  uint8_t reg;
} config_reg;

// RF_SETUP register bit field
typedef union {
  struct {
    uint8_t lna_hcurr   : 1;
    uint8_t rf_pwr      : 2;
    uint8_t rf_dr       : 1;
    uint8_t pll_lock    : 1;
    uint8_t reserved    : 3;
  } rf_setup;
  uint8_t reg;
} rf_setup_reg;

// RF_CH register bit field
typedef union {
  struct {
    uint8_t rf_ch    : 7;
    uint8_t reserved : 1;
  } rf_ch;
  uint8_t reg;
} rf_ch_reg;

// FIFO_STATUS register bit field
typedef union {
  struct {
    uint8_t rx_empty  : 1;
    uint8_t rx_full   : 1;
    uint8_t reserved2 : 2;
    uint8_t tx_empty  : 1;
    uint8_t tx_full   : 1;
    uint8_t tx_reuse  : 1;
    uint8_t reserved  : 1;
  } fifo_status;
  uint8_t reg;
} fifo_status_reg;

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
 * \brief nrf_write_status: write the status register
 *
 * \param status: value to write to register
 *
 */
void nrf_write_status(uint8_t status);

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
 * \brief nrf_write_tx_payload: writes the tx payload on the nrf module using spi
 *
 * \param payload: a uint8_t array of elements for payload
 * \param len: a len of payload
 *
 */
void nrf_write_tx_payload(uint8_t * payload, uint8_t len);

/*
 * \brief nrf_write_rx_addr: the rx address for a certain pipe
 *
 * \param rx_addr: pointer to rx_address
 * \param pipe: data pipe you want to write the address to
 * \param addr_len: len of address (only pipe 0 and 1 are 5 bytes the rest are
 *                  1 byte)
 *
 */
void nrf_write_rx_addr(uint8_t * rx_addr, uint8_t pipe, uint8_t addr_len);

/*
 * \brief nrf_read_rx_payload: reads an rx payload
 *
 * \param rx_payload: memory location to write payload to
 * \param payload_len: length of payload to read
 *
 */
void nrf_read_rx_payload(uint8_t * rx_payload, uint8_t payload_len);

/*
 * \brief nrf_write_rx_payload_len: writes payload length to pipe
 *
 * \param pipe: pipe to write length to
 * \param payload_len: payload length
 *
 */
void nrf_write_rx_payload_len(uint8_t pipe, uint8_t payload_len);

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
