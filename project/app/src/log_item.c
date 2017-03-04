#include <stdint.h>
#include <stdlib.h>
#include "memory.h"
#include "log.h"
#include "log_item.h"
#include "project_defs.h"

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
	"LOG_ID_DATA_ANALYSIS_COMPLETED"
};
#endif // VERBOSE

uint8_t create_log_item(log_item_t ** item, log_id_t log_id, uint8_t * payload)
{
  uint8_t length = 0;
  uint8_t * start = payload;

  // Check for null pointers
  CHECK_NULL(item);

  if (payload != NULL)
  {
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

