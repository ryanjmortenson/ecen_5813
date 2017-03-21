#include "project_defs.h"
#include "data.h"
#include "MKL25Z4.h"
#include "project3.h"
#include "memory.h"
#include "string.h"
#include "log.h"
#include "log_item.h"

#ifdef FRDM
#include "spi.h"
#include "memory_dma.h"
#include "timer.h"
#endif // FRDM

/*
 * Function definitions see project3.h for documentation
 */

#define BUFFER_SIZE (4096)

uint8_t project_3_memmove_dma()
{
#ifdef FRDM
  return SUCCESS;
#endif // FRDM
} // project_3_memmove_dma()

uint8_t project_3_profiler()
{

#ifdef FRDM

#ifdef VERBOSE
  // No need for a log item if not verbose
  log_item_t * item;
#endif // VERBOSE

  // Init log and bail out if a failure occurs
  if (log_init())
  {
    return FAILURE;
  }

  // Send log system initialized
  CREATE_ITEM_DATA(item, LOG_ID_LOGGER_INITIALIZED, NULL, 0);
  LOG_ITEM(item);
  CREATE_ITEM_DATA(item, LOG_ID_SYSTEM_INITIALIZED, NULL, 0);
  LOG_ITEM(item);

  // Make some buffers to transfer
  uint8_t src[BUFFER_SIZE] = {0xff};
  uint8_t dst[BUFFER_SIZE] = {0};

  // Memset the buffers to different values so you can see the memmcpy occured
  my_memset(src, BUFFER_SIZE, 0xff);
  my_memset(dst, BUFFER_SIZE, 0x0);

  // Init the dma subsystem
  dma_init();

  // Init the profiler
  profiler_init();

  // Profile normal memmove
  START_TIMER;
  memmove(src, dst, sizeof(src));
  STOP_TIMER;
  volatile uint32_t time = GET_TIME;
  RESET_TIMER;

#ifdef BINARY_LOGGER
  CREATE_ITEM_DATA(item, LOG_ID_PROFILE_MEMMOVE_TIME, &time, sizeof(time));
#else
  int8_t itoa_buffer[16] = {0};
  my_itoa(itoa_buffer, time, BASE_10);
  CREATE_ITEM_STRING(item, LOG_ID_PROFILE_MEMMOVE_TIME, itoa_buffer);
#endif // BINARY_LOGGER
  LOG_ITEM(item);

  // Profile normal memmove_dma
  START_TIMER;
  memmove_dma((uint8_t *)src, (uint8_t *)dst, BUFFER_SIZE, WORD);
  STOP_TIMER;
  time = GET_TIME;
  RESET_TIMER;

#ifdef BINARY_LOGGER
  CREATE_ITEM_DATA(item, LOG_ID_PROFILE_MEMMOVE_DMA_TIME, &time, sizeof(time));
#else
  my_itoa(itoa_buffer, time, BASE_10);
  CREATE_ITEM_STRING(item, LOG_ID_PROFILE_MEMMOVE_DMA_TIME, itoa_buffer);
#endif // BINARY_LOGGER
  LOG_ITEM(item);

  // Profile normal memmove_dma
  START_TIMER;
  my_memmove(src, dst, sizeof(src));
  STOP_TIMER;
  time = GET_TIME;
  RESET_TIMER;

#ifdef BINARY_LOGGER
  CREATE_ITEM_DATA(item, LOG_ID_PROFILE_MY_MEMMOVE_TIME, &time, sizeof(time));
#else
  my_itoa(itoa_buffer, time, BASE_10);
  CREATE_ITEM_STRING(item, LOG_ID_PROFILE_MY_MEMMOVE_TIME, itoa_buffer);
#endif // BINARY_LOGGER
  LOG_ITEM(item);

  time = time;
#endif // FRDM

  return SUCCESS;
} // project_3_profiler()


uint8_t project_3_spi()
{
  return SUCCESS;
} // project_3_spi()
