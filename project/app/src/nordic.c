#include "spi.h"
#include "gpio.h"
#include "nordic.h"

uint8_t nrf_read_register(uint8_t reg)
{
  // Enable the chip select
  GPIO_NRF_CSN_ENABLE;

  // Send the register to read
  spi_send_byte(reg);

  // Read the register value
  uint8_t value = spi_receive_byte();

  // Send the no op command to shift out register contents
  spi_send_byte(NRF_NO_OP);

  // Read the register value
  value = spi_receive_byte();

  // Disable chip select
  GPIO_NRF_CSN_DISABLE;

  // Return received byte
  return value;
} // nrf_read_register()

void nrf_write_register(uint8_t reg, uint8_t value)
{
  // Enable the chip select
  GPIO_NRF_CSN_ENABLE;

  // Send the register to write with the wrte mask
  spi_send_byte(NRF_WRITE_MASK | reg);

  // Read status byte
  spi_receive_byte();

  // Send the no op command to shift out register contents
  spi_send_byte(value);

  // Receive byte and discard
  spi_receive_byte();

  // Disable chip select
  GPIO_NRF_CSN_DISABLE;
} // nrf_write_register()

uint8_t nrf_read_status()
{
  // Send register to read
  spi_send_byte(NRF_STATUS_REG);

  // Send the no op command to shift out register contents
  spi_send_byte(NRF_NO_OP);

  // Return received byte
  return spi_receive_byte();
} // nrf_read_status()

uint8_t nrf_read_config()
{
  // Return nrf status register
  return nrf_read_register(NRF_STATUS_REG);
} // nrf_read_config()

void nrf_write_config(uint8_t config)
{
  // Write config register
  nrf_write_register(NRF_CONFIG_REG, config);
} // nrf_write_config()

uint8_t nrf_read_rf_setup()
{
  // Return nrf rf setup register
  return nrf_read_register(NRF_RF_SETUP_REG);
} // nrf_read_rf_setup()

void nrf_write_rf_setup(uint8_t config)
{
  // Write rf setup register
  nrf_write_register(NRF_RF_SETUP_REG, config);
} // nrf_write_rf_setup()

uint8_t nrf_read_rf_ch()
{
  // Return nrf rf ch register
  return nrf_read_register(NRF_RF_CH_REG);
} // nrf_read_rf_ch()

void nrf_write_rf_ch(uint8_t channel)
{
  // Write rf ch register
  nrf_write_register(NRF_RF_CH_REG, channel);
} // nrf_write_rf_ch()

void nrf_read_tx_addr(uint8_t * tx_addr)
{
  // Enable the chip select
  GPIO_NRF_CSN_ENABLE;

  // Send the register read for tx addr
  spi_send_byte(NRF_TX_ADDR_REG);

  // Read the status
  spi_receive_byte();

  // Loop over the next 5 bytes reading in the tx addr
  for(uint8_t i = 0; i < NRF_TXADDR_LEN; i++)
  {
    // Send the no op command to shift out register contents
    spi_send_byte(NRF_NO_OP);

    // Read the register value
    tx_addr[i] = spi_receive_byte();
  }

  // Disable chip select
  GPIO_NRF_CSN_DISABLE;
} // nrf_read_config()

void nrf_write_tx_addr(uint8_t * tx_addr)
{
  // Enable the chip select
  GPIO_NRF_CSN_ENABLE;

  // Send the register write for tx addr
  spi_send_byte(NRF_WRITE_MASK | NRF_TX_ADDR_REG);

  // Read the status
  spi_receive_byte();

  // Loop over the next 5 bytes writing the tx addr
  for(uint8_t i = 0; i < NRF_TXADDR_LEN; i++)
  {
    // Send the no op command to shift out register contents
    spi_send_byte(tx_addr[i]);

    // Read the register value
    spi_receive_byte();
  }

  // Disable chip select
  GPIO_NRF_CSN_DISABLE;
} // nrf_read_config()

uint8_t nrf_read_fifo_status()
{
  // Return nrf rf ch register
  return nrf_read_register(NRF_FIFO_STATUS_REG);
} // nrf_read_rf_ch()

void nrf_flush_tx_fifo()
{
  // Enable the chip select
  GPIO_NRF_CSN_ENABLE;

  // Send the flush tx command
  spi_send_byte(NRF_FLUSH_TX);

  // Read the status
  spi_receive_byte();

  // Disable chip select
  GPIO_NRF_CSN_DISABLE;
}

void nrf_flush_rx_fifo()
{
  // Enable the chip select
  GPIO_NRF_CSN_ENABLE;

  // Send the flush rx command
  spi_send_byte(NRF_FLUSH_RX);

  // Read the status
  spi_receive_byte();

  // Disable chip select
  GPIO_NRF_CSN_DISABLE;
}
