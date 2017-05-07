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
#include "timer.h"
#include "rtc.h"
#include "uart.h"
#include "log.h"
#include "gpio.h"
#else
#include "timer_linux.h"
#endif // FRDM

/*
 * Function definitions see project3.h for documentation
 */

#ifdef FRDM
extern void DefaultISR()
{
  for(volatile uint8_t i = 0; i < 255; i++);
}
#endif

// Size of buffer for memory copies
#define BUFFER_SIZE (10)

#ifdef VERBOSE
  // No need for a log item if not verbose
  static log_item_t * item;
#endif // VERBOSE

/*
 * \brief log_time: helper for logging profile times
 *
 * \param id: log id for log message
 * \param time: time to log
 *
 */
static inline void log_time(log_id_t id, uint32_t time)
{
#ifdef BINARY_LOGGER
  CREATE_ITEM_DATA(item, id, &time, sizeof(time));
#else
  int8_t itoa_buffer[16] = {0};
  my_itoa(itoa_buffer, time, BASE_10);
  CREATE_ITEM_STRING(item, id, itoa_buffer);
#endif // BINARY_LOGGER
  LOG_ITEM(item);
}

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

uint8_t project_3_setup()
{
#ifdef FRDM
  // Setup the rtc for logging timestamps
  rtc_init();

  // Setup dma
  dma_init();

  // Setup profiler for kl25z
  profiler_init();

  // Setup the nrf gpio pins for executing chip select
  gpio_nrf_init();

#ifdef CIRCBUF_DMA
  // Setup uart dma
  dma_uart_init();
#endif // CIRCBUF_DMA

#else
  // Setup timer for BBB and linux workstation
  profiler_init_linux();
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

  // Indicate logger initialized
  CREATE_ITEM_DATA(item, LOG_ID_SYSTEM_INITIALIZED, NULL, 0);
  LOG_ITEM(item);

  return SUCCESS;
}

void project_3_profiler()
{
  // Make some buffers to transfer
  uint8_t src[BUFFER_SIZE] = {0xff};
  uint8_t dst[BUFFER_SIZE] = {0x00};

  // Memset the buffers to different values so you can see the memmcpy occured
  my_memset(src, BUFFER_SIZE, 0xff);
  my_memset(dst, BUFFER_SIZE, 0x0);

  // Profile library memmove
  START_TIMER;
  memmove(dst, src, BUFFER_SIZE);
  STOP_TIMER;
  volatile uint32_t time = GET_TIME;
  RESET_TIMER;
  log_time(LOG_ID_PROFILE_MEMMOVE_TIME, time);

#ifdef FRDM
  // Profile memmove_dma
  START_TIMER;
  memmove_dma(src, dst, BUFFER_SIZE);
  STOP_TIMER;
  time = GET_TIME;
  RESET_TIMER;
  log_time(LOG_ID_PROFILE_MEMMOVE_DMA_TIME, time);
#endif // FRDM

  // Profile my_memmove
  START_TIMER;
  my_memmove(src, dst, BUFFER_SIZE);
  STOP_TIMER;
  time = GET_TIME;
  RESET_TIMER;
  log_time(LOG_ID_PROFILE_MY_MEMMOVE_TIME, time);

  // Profile library memset
  START_TIMER;
  memset(dst, 0xaa, BUFFER_SIZE);
  STOP_TIMER;
  time = GET_TIME;
  RESET_TIMER;
  log_time(LOG_ID_PROFILE_MEMSET_TIME, time);

#ifdef FRDM
  // Profile memset_dma
  START_TIMER;
  memset_dma(dst, BUFFER_SIZE, 0x55);
  STOP_TIMER;
  time = GET_TIME;
  RESET_TIMER;
  log_time(LOG_ID_PROFILE_MEMSET_DMA_TIME, time);
#endif // FRDM

  // Profile my_memset
  START_TIMER;
  my_memset(src, BUFFER_SIZE, 0xa5);
  STOP_TIMER;
  time = GET_TIME;
  RESET_TIMER;
  log_time(LOG_ID_PROFILE_MY_MEMSET_TIME, time);
} // project_3_profiler()

void project_3_spi()
{
#if defined(BBB) || defined(FRDM)
  status_reg status;
  config_reg config;
  fifo_status_reg fifo_status;

  // Do some reading and writing of config register
  config.reg = nrf_read_config();
  log_reg(LOG_ID_NRF_READ_CONFIG, config.reg);
  config.config.pwr_up = 1;
  config.config.prim_rx = 1;
  // config.config.en_crc = 0;
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
  rf_ch.rf_ch.rf_ch = 0x9;
  nrf_write_rf_ch(rf_ch.reg);
  rf_ch.reg = nrf_read_rf_ch();
  log_reg(LOG_ID_NRF_READ_RF_CH, rf_ch.reg);

  // Do some reading and writing of the rf_setup register
  rf_setup_reg rf_setup;
  rf_setup.reg = nrf_read_rf_setup();
  log_reg(LOG_ID_NRF_READ_RF_SETUP, rf_setup.reg);
  rf_setup.rf_setup.rf_dr = 1;
  rf_setup.rf_setup.rf_pwr = 0;
  nrf_write_rf_setup(rf_setup.reg);
  rf_setup.reg = nrf_read_rf_setup();
  log_reg(LOG_ID_NRF_READ_RF_SETUP, rf_setup.reg);
#if 0
  // Do some reading and writing of the tx_addr register
  uint8_t tx_addr[5] = {0};
  nrf_read_tx_addr(tx_addr);
  for(uint8_t i = 0; i < 5; i++)
  {
    log_reg(LOG_ID_NRF_READ_TX_ADDR, tx_addr[i]);
  }
  my_memset(tx_addr, 5, 0xaa);
  nrf_write_tx_addr(tx_addr);
  my_memset(tx_addr, 5, 0);
  nrf_read_tx_addr(tx_addr);
  for(uint8_t i = 0; i < 5; i++)
  {
    log_reg(LOG_ID_NRF_READ_TX_ADDR, tx_addr[i]);
  }

  // Do some reading of fifo_status register
  nrf_write_register(2, 0x3f);
  fifo_status.reg = nrf_read_fifo_status();
  log_reg(LOG_ID_NRF_READ_FIFO_STATUS, fifo_status.reg);

  uint8_t rx_addr[] = {0xc2, 0xc2, 0xc2, 0xc2, 0xc2};

  nrf_write_rx_addr(rx_addr, 0x0b);
#endif

  //nrf_write_register(1, 0);
  //nrf_write_register(4, 0);
  nrf_write_register(0x10, 32);
  nrf_write_register(0x11, 32);
  nrf_write_register(0x12, 32);
  nrf_write_register(0x13, 32);
  nrf_write_register(0x14, 32);
  nrf_write_register(0x15, 32);

  // Start a transmission
  GPIO_NRF_CE_ENABLE;

  // Loop for a bit
  while(!status.status.rx_dr)
  {
    status.reg = nrf_read_status();
    log_reg(LOG_ID_NRF_READ_STATUS, status.reg);
  }

  // Turn off transmitter
  GPIO_NRF_CE_DISABLE;

  fifo_status.reg = nrf_read_fifo_status();
  log_reg(LOG_ID_NRF_READ_FIFO_STATUS, fifo_status.reg);

  uint8_t payload[32];
  nrf_read_rx_payload(payload);

  status.status.rx_dr = 1;
  nrf_write_status(status.reg);

  fifo_status.reg = nrf_read_fifo_status();
  log_reg(LOG_ID_NRF_READ_FIFO_STATUS, fifo_status.reg);


#ifdef BBB
  uint8_t payload[] = {0x03, 0x07, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06};

  const uint8_t len = 11;
  for (volatile uint8_t i = 0; i < 255; i++)
  {
    nrf_flush_tx_fifo();
    nrf_write_tx_payload(payload, len);

    // Do some reading of fifo_status register
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

    status.status.max_rt = 1;
    nrf_write_status(status.reg);
    log_reg(LOG_ID_NRF_READ_STATUS, payload_width);


  }
  spi_shutdown();
#endif // BBB

#endif // FRDM || BBB
} // project_3_spi()
