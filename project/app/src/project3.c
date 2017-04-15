#include "project_defs.h"
#include "data.h"
#include "project3.h"
#include "memory.h"
#include "log.h"
#include "string.h"
#include "log_item.h"
#include "nordic.h"

#ifdef FRDM
#include "MKL25Z4.h"
#include "spi.h"
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
#define BUFFER_SIZE (5000)

#ifdef VERBOSE
  // No need for a log item if not verbose
  static log_item_t * item;
#endif // VERBOSE

uint8_t project_3_setup()
{
#ifdef FRDM
  // Setup the rtc for logging timestamps
  rtc_init();

  // Setup dma
  dma_init();

  // Setup profiler for kl25z
  profiler_init();

  // Setup the spi for kl25z
  spi_init();

  // Setup the nrf gpio pins for executing chip select
  gpio_nrf_init();
#else
  // Setup timer for BBB and linux workstation
  profiler_init_linux();
#endif // FRDM

  // Init log and bail out if a failure occurs
  if (log_init())
  {
    return FAILURE;
  }
  // Indicate logger initialized
  CREATE_ITEM_STRING(item, LOG_ID_LOGGER_INITIALIZED, "");
  LOG_ITEM(item);

  return SUCCESS;
}

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

uint8_t project_3_profiler()
{
  // Send log system initialized
  // CREATE_ITEM_STRING(item, LOG_ID_SYSTEM_INITIALIZED, "");
  // LOG_ITEM(item);

  // Make some buffers to transfer
  uint8_t src[BUFFER_SIZE] = {0xff};
  uint8_t dst[BUFFER_SIZE] = {0x00};

  // Memset the buffers to different values so you can see the memmcpy occured
  my_memset(src, BUFFER_SIZE, 0xff);
  my_memset(dst, BUFFER_SIZE, 0x0);

  // Profile normal memmove
  START_TIMER;
  memmove(dst, src, BUFFER_SIZE);
  STOP_TIMER;
  volatile uint32_t time = GET_TIME;
  RESET_TIMER;
  log_time(LOG_ID_PROFILE_MEMMOVE_TIME, time);

#ifdef FRDM
  // Profile normal memmove_dma
  START_TIMER;
  memmove_dma(src, dst, BUFFER_SIZE);
  STOP_TIMER;
  time = GET_TIME;
  RESET_TIMER;
  log_time(LOG_ID_PROFILE_MEMMOVE_DMA_TIME, time);
#endif // FRDM

  // Profile normal memmove_dma
  START_TIMER;
  my_memmove(src, dst, BUFFER_SIZE);
  STOP_TIMER;
  time = GET_TIME;
  RESET_TIMER;
  log_time(LOG_ID_PROFILE_MY_MEMMOVE_TIME, time);

  // Profile normal memmove
  START_TIMER;
  memset(dst, 0xaa, BUFFER_SIZE);
  STOP_TIMER;
  time = GET_TIME;
  RESET_TIMER;
  log_time(LOG_ID_PROFILE_MEMSET_TIME, time);

#ifdef FRDM
  // Profile normal memmove_dma
  START_TIMER;
  memset_dma(dst, BUFFER_SIZE, 0x55);
  STOP_TIMER;
  time = GET_TIME;
  RESET_TIMER;
  log_time(LOG_ID_PROFILE_MEMSET_DMA_TIME, time);
#endif // FRDM

  // Profile normal memmove_dma
  START_TIMER;
  my_memset(src, BUFFER_SIZE, 0xaa);
  STOP_TIMER;
  time = GET_TIME;
  RESET_TIMER;
  log_time(LOG_ID_PROFILE_MY_MEMSET_TIME, time);


  return SUCCESS;
} // project_3_profiler()

uint8_t project_3_spi()
{
#ifdef FRDM
  uint8_t count = 0;
  uint8_t tx_addr[5] = {0};

  while(count < 1000)
  {
    nrf_write_register(0, 1);
    nrf_read_register(0);
    nrf_write_register(0, 4);
    nrf_read_register(0);
    nrf_read_tx_addr(tx_addr);
  }
#endif
  return SUCCESS;
} // project_3_spi()
