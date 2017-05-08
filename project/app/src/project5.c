#include "project_defs.h"
#include "data.h"
#include "project3.h"
#include "memory.h"
#include "log.h"
#include "string.h"
#include "log_item.h"
#include "nordic.h"

#if defined(BBB) || defined(FRDM)
#include "spi.h"
#endif // FRDM || BBB

#ifdef FRDM
#include "MKL25Z4.h"
#include "memory_dma.h"
#include "rtc.h"
#include "uart.h"
#include "log.h"
#include "gpio.h"
#endif // FRDM

#define PAYLOAD_LEN (32)
#define RF_CHANNEL (9)
#define POWER_LEVEL (0)
#define ON (1)
#define OFF (0)

/*
 * Function definitions see project5.h for documentation
 */

#ifdef VERBOSE
  // No need for a log item if not verbose
  static log_item_t * item;
#endif // VERBOSE

/*
 * \brief log_reg: helper for logging register values
 *
 * \param id: log id for log message
 * \param reg: register to log
 *
 */
static inline void log_reg(log_id_t id, uint8_t reg)
{
#ifdef BINARY_LOGGER
  CREATE_ITEM_DATA(item, id, &reg, sizeof(reg));
#else
  int8_t itoa_buffer[16] = {0};
  my_itoa(itoa_buffer, reg, 2);
  CREATE_ITEM_STRING(item, id, itoa_buffer);
#endif // BINARY_LOGGER
  LOG_ITEM(item);
}

uint8_t project_5_setup()
{
#ifdef FRDM
  // Setup the rtc for logging timestamps
  rtc_init();

  // Setup dma
  dma_init();

  // Setup the nrf gpio pins for executing chip select
  gpio_nrf_init();

#ifdef CIRCBUF_DMA
  // Setup uart dma
  dma_uart_init();
#endif // CIRCBUF_DMA

#endif // FRDM

  // Init log and bail out if a failure occurs
  if (log_init())
  {
    return FAILURE;
  }

  // Send log system initialized
  CREATE_ITEM_DATA(item, LOG_ID_LOGGER_INITIALIZED, NULL, 0);
  LOG_ITEM(item);

#if defined(BBB) || defined(FRDM)
  // Setup the spi for kl25z or BBB
  if (spi_init())
  {
     // Send SPI failed
     CREATE_ITEM_DATA(item, LOG_ID_ERROR, NULL, 0);
     LOG_ITEM(item);
     return FAILURE;
  }
#endif // BBB || FRDM

  // Indicate system initialized
  CREATE_ITEM_DATA(item, LOG_ID_SYSTEM_INITIALIZED, NULL, 0);
  LOG_ITEM(item);

  return SUCCESS;
}

void project_5_wireless_comms()
{
#if defined(BBB) || defined(FRDM)
  status_reg status;
  config_reg config;
  fifo_status_reg fifo_status;
  uint8_t payload[PAYLOAD_LEN];

  // Do some reading and writing of config register
  config.reg = nrf_read_config();
  config.config.pwr_up = 1;

#ifdef FRDM
  // Set FRDM as a receiver
  config.config.prim_rx = 1;
#endif // FRDM

  nrf_write_config(config.reg);
  config.reg = nrf_read_config();
  log_reg(LOG_ID_NRF_READ_CONFIG, config.reg);

  // Do some reading of status register
  status.reg = nrf_read_status();
  log_reg(LOG_ID_NRF_READ_STATUS, status.reg);

  // Do some reading and writing of the rf_ch register
  rf_ch_reg rf_ch;
  rf_ch.reg = nrf_read_rf_ch();
  log_reg(LOG_ID_NRF_READ_RF_CH, rf_ch.reg);
  rf_ch.rf_ch.rf_ch = RF_CHANNEL;
  nrf_write_rf_ch(rf_ch.reg);
  rf_ch.reg = nrf_read_rf_ch();
  log_reg(LOG_ID_NRF_READ_RF_CH, rf_ch.reg);

  // Do some reading and writing of the rf_setup register
  rf_setup_reg rf_setup;
  rf_setup.reg = nrf_read_rf_setup();
  log_reg(LOG_ID_NRF_READ_RF_SETUP, rf_setup.reg);
  rf_setup.rf_setup.rf_dr = ON;
  rf_setup.rf_setup.rf_pwr = POWER_LEVEL;
  nrf_write_rf_setup(rf_setup.reg);
  rf_setup.reg = nrf_read_rf_setup();
  log_reg(LOG_ID_NRF_READ_RF_SETUP, rf_setup.reg);

  // Write payload length to receive payload length
  nrf_write_register(NRF_RX_PW_P0, PAYLOAD_LEN);
  nrf_write_register(NRF_RX_PW_P1, PAYLOAD_LEN);

#ifdef FRDM
  // Start a receiving on FRDM
  GPIO_NRF_CE_ENABLE;

  // Loop for a bit
  while(!status.status.rx_dr)
  {
    status.reg = nrf_read_status();
    log_reg(LOG_ID_NRF_READ_STATUS, status.reg);
  }

  // Turn off receiver
  GPIO_NRF_CE_DISABLE;

  // Do some reading of fifo_status register
  fifo_status.reg = nrf_read_fifo_status();
  log_reg(LOG_ID_NRF_READ_FIFO_STATUS, fifo_status.reg);

  // Read the payload
  nrf_read_rx_payload(payload);

  // Clear the receive data ready
  status.status.rx_dr = ON;
  nrf_write_status(status.reg);

  // Log fifo status
  fifo_status.reg = nrf_read_fifo_status();
  log_reg(LOG_ID_NRF_READ_FIFO_STATUS, fifo_status.reg);
#endif // FRDM

#ifdef BBB
  uint8_t led_cmd[] = {0x03, 0x07, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06};
  my_memset(payload, PAYLOAD_LEN, 0xff);
  my_memmove(led_cmd, payload, 11);

  for (volatile uint8_t i = 0; i < 1; i++)
  {
    // Clear the max_rt bit
    status.status.max_rt = ON;
    nrf_write_status(status.reg);

    // Flush the tx fifo to start new
    nrf_flush_tx_fifo();
    nrf_write_tx_payload(payload, PAYLOAD_LEN);

    // Read and print the fifo status register
    fifo_status.reg = nrf_read_fifo_status();
    fifo_status = fifo_status;
    log_reg(LOG_ID_NRF_READ_FIFO_STATUS, fifo_status.reg);

    // Start a transmission
    GPIO_NRF_CE_ENABLE;

    // Loop for a bit
    while(!(status.status.tx_ds))
    {
      status.reg = nrf_read_status();
    }

    // Turn off transmitter
    GPIO_NRF_CE_DISABLE;

    // Do some reading of fifo_status register
    fifo_status.reg = nrf_read_fifo_status();
    fifo_status = fifo_status;
    log_reg(LOG_ID_NRF_READ_FIFO_STATUS, fifo_status.reg);

    // Do some reading of status register
    status.reg = nrf_read_status();
    log_reg(LOG_ID_NRF_READ_STATUS, status.reg);

    // Do some reading of status register
    status.reg = nrf_read_status();
    log_reg(LOG_ID_NRF_READ_STATUS, status.reg);
  }
  spi_shutdown();
#endif // BBB

#endif // FRDM || BBB
} // project_3_spi()
