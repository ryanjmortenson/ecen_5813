#include <stdint.h>
#include <stdlib.h>
#include "log_item.h"
#include "memory.h"
#include "log.h"
#include "project_defs.h"

uint8_t create_log_item(log_item_t ** item, uint8_t log_id, uint8_t *payload, uint8_t length)
{
  // Check for null pointers
  CHECK_NULL(item);
  CHECK_NULL(payload);

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

