#include <stdint.h>
#include <stdlib.h>
#include "data.h"
#include "memory.h"
#include "log.h"
#include "log_item.h"
#include "project_defs.h"

#ifdef FRDM
#include "uart.h"
#endif // FRDM

#ifdef VERBOSE
char * log_id_str[] =
{
	"LOG_ID_LOGGER_INITIALIZED",
	"LOG_ID_GPIO_INITIALZED",
	"LOG_ID_SYSTEM_INITIALIZED",
	"LOG_ID_SYSTEM_HALTED",
	"LOG_ID_INFO",
	"LOG_ID_WARNING",
	"LOG_ID_ERROR",
	"LOG_ID_DATA_RECEIVED",
	"LOG_ID_DATA_ANALYSIS_STARTED",
	"LOG_ID_DATA_ALPHA_COUNT",
	"LOG_ID_DATA_NUMERIC_COUNT",
	"LOG_ID_DATA_PUNCTUATION_COUNT",
	"LOG_ID_DATA_MISC_COUNT",
	"LOG_ID_DATA_ANALYSIS_COMPLETED",
	"LOG_ID_PROFILE_MEMMOVE_TIME",
	"LOG_ID_PROFILE_MEMMOVE_DMA_TIME",
	"LOG_ID_PROFILE_MY_MEMMOVE_TIME",
	"LOG_ID_HEARTBEAT"
};
#endif // VERBOSE

uint8_t create_log_item(log_item_t ** item, log_id_t log_id, uint8_t * payload, int16_t length)
{
  uint8_t * start = payload;

  // Check for null pointers
  // The payload isn't checked for null because it indicates no payload
  CHECK_NULL(item);

  // Check to make sure length isn't less than -1 which indicates calculate
  // the length of a c string
  if (length < LOG_ITEM_STRING)
  {
    return FAILURE;
  }

  // If a string is passed in the length should be -1 to calculate the
  // length
  if (payload != NULL && length == LOG_ITEM_STRING)
  {
    // Set length to zero
    length = 0;

    // Find the length of the string
    while(*(start))
    {
      start++;
      length++;
    }
  }

  // Allocate the new circular buffer
  if ((*item = malloc(sizeof(log_item_t))) == NULL)
  {
    return FAILURE;
  }

  // Allocate the internal buffer to size requested
  if (((*item)->payload = malloc(sizeof(uint8_t)*length)) == NULL)
  {
    return FAILURE;
  }

  // Fill our structure
  (*item)->log_length = length;
  (*item)->log_id     = log_id;
  my_memmove(payload, (*item)->payload, length);

  return SUCCESS;
} // create_log_item()

uint8_t destroy_log_item(log_item_t * item)
{

  // Check for null pointers
  CHECK_NULL(item);
  CHECK_NULL(item->payload);

  // Free the buffer
  free(item->payload);

  // Free the circular buffer structure
  free(item);

  // Return success
  return FAILURE;
} // destroy_log_item()

// TODO: Remove all ifdef for loggin because it is really messy
uint8_t log_item(log_item_t * item)
{
  if (item == NULL)
  {
    LOG_RAW_STRING("\nLog Item is null");
    return FAILURE;
  }

#ifdef BINARY_LOGGER
  LOG_RAW_DATA(&item->log_length, sizeof(item->log_length));
  LOG_RAW_DATA(&item->log_id, sizeof(item->log_id));
  LOG_RAW_DATA(item->payload, item->log_length);
#else
#ifdef VERBOSE
  // Remove this when not verbose because it will be unused
  int8_t itoa_buffer[10];
#endif // VERBOSE
  // Place the length on the line
  LOG_RAW_STRING("\nLog Payload Length: ");
  LOG_RAW_STRING(my_itoa(itoa_buffer, item->log_length, 10));
  LOG_RAW_STRING("\nLog ID: ");
  LOG_RAW_STRING(log_id_str[item->log_id]);
  LOG_RAW_STRING("\nLog Payload: ");
  LOG_RAW_DATA(item->payload, item->log_length);
  LOG_RAW_STRING("\n");
#endif // BINARY_LOGGER

  // Start tranmission and wait for the circular buffer to empty
#ifdef FRDM
#ifdef UART_INTERRUPTS
  TRANSMIT_READY;
#endif // UART_INTERRUPTS
#endif // FRDM
  LOG_RAW_FLUSH();

  return SUCCESS;
} // log_item()
