#include <stdint.h>
#include <stdlib.h>
#include "circbuf.h"

// Circular buffer structure
struct circbuf
{
  uint8_t * buffer;
  uint8_t * head;
  uint8_t * tail;
  uint8_t length;
  uint8_t count;
};

cb_enum_t circbuf_init(circbuf_t ** buf, uint8_t length)
{
  // Check for null pointers
  CB_CHECK_NULL(buf);

  // Make sure size is valid
  if (length <= 0)
  {
    return CB_ENUM_NO_LENGTH;
  }

  // Allocate the new circular buffer
  if ((*buf = malloc(sizeof(circbuf_t))) == NULL)
  {
    return CB_ENUM_ALLOC_FAILURE;
  }

  // Allocate the internal buffer to size requested
  if (((*buf)->buffer = malloc(sizeof(uint8_t)*length)) == NULL)
  {
    return CB_ENUM_ALLOC_FAILURE;
  }

  // Set the remaining elements of the circular buffer
  (*buf)->head     = (*buf)->buffer;
  (*buf)->tail     = (*buf)->buffer;
  (*buf)->length   = length;
  (*buf)->count    = 0;

  // Return success
  return CB_ENUM_NO_ERROR;
} // circbuf_init()


cb_enum_t circbuf_destroy(circbuf_t * buf)
{

  // Check for null pointers
  CB_CHECK_NULL(buf);
  CB_CHECK_NULL(buf->buffer);

  // Free the buffer
  free(buf->buffer);

  // Free the circular buffer structure
  free(buf);

  // Return success
  return CB_ENUM_NO_ERROR;
} // circbuf_destroy()

cb_enum_t circbuf_add_item(circbuf_t * buf, uint8_t payload)
{
  // Check for null pointer
  CB_CHECK_NULL(buf);
  CB_CHECK_NULL(buf->buffer);

  // Make sure there is room in the buffer
  if (buf->count == buf->length)
  {
    return CB_ENUM_FULL;
  }

  // Wrap buffer if needed
  if (buf->head - buf->buffer == buf->length - 1)
  {
    buf->head = buf->buffer;
  }
  // No wrap is necessary increment head
  else if (buf->count != 0)
  {
    buf->head++;
  }

  // Set head to payload
  *(buf->head) = payload;

  // Increment count
  buf->count++;

  // Return success
  return CB_ENUM_NO_ERROR;
} // CircBufAddItem()

cb_enum_t circbuf_remove_item(circbuf_t * buf, uint8_t * payload)
{
  // Check for null pointer
  CB_CHECK_NULL(buf);
  CB_CHECK_NULL(buf->buffer);

  // Make sure there is an item to read
  if (buf->count == 0)
  {
    return CB_ENUM_EMPTY;
  }

  // Put tail in payload
  *payload = *(buf->tail);

  // Decrement count
  buf->count--;

  // Wrap buffer if needed
  if (buf->tail - buf->buffer == buf->length - 1)
  {
    buf->tail = buf->buffer;
  }
  // No wrap is necessary increment head
  else if (buf->count != 0)
  {
    buf->tail++;
  }

  // Return success
  return CB_ENUM_NO_ERROR;
} // CircBufRemoveItem()

cb_enum_t circbuf_peak(circbuf_t * buf, uint32_t index, uint8_t * payload)
{
  // Make a variable for
  int32_t diff = 0;

  // Check for null pointer
  CB_CHECK_NULL(buf);
  CB_CHECK_NULL(buf->buffer);

  // Make sure there are enough items to have the index item
  if (index > buf->length - 1)
  {
    return CB_ENUM_BAD_INDEX;
  }

  // Wrap buffer if needed
  if ((diff = (buf->tail + index) - (buf->buffer + buf->length)) >= 0)
  {
    *payload = *(buf->buffer + diff);
  }
  // No wrap is necessary increment head
  else
  {
    *payload = *(buf->tail + index);
  }

  return CB_ENUM_NO_ERROR;
} // CircBufPeak()

cb_enum_t circbuf_full(circbuf_t * buf)
{
  // Check null pointer
  CB_CHECK_NULL(buf);

  // Buffer is full return success
  if (buf->length == buf->count)
  {
    return CB_ENUM_NO_ERROR;
  }

  // Buffer is not full return failure
  return CB_ENUM_FAILURE;
} // CircBufFull()

cb_enum_t circbuf_empty(circbuf_t * buf)
{
  // Check null pointer
  CB_CHECK_NULL(buf);

  // Buffer is full return success
  if (buf->count == 0)
  {
    return CB_ENUM_NO_ERROR;
  }

  // Buffer is not full return failure
  return CB_ENUM_FAILURE;
} // CircBufEmpty()
