#include <stdint.h>
#include <stdlib.h>
#include "circbuf.h"
#include "project_defs.h"

CB_Enum_t CircBufInitialize(CircBuf_t ** buf, uint8_t length)
{
  // Make sure size is valid
  if (length <= 0)
  {
    return CB_ENUM_NO_LENGTH;
  }

  PRINTF("length: %d\n", length);

  // Allocate the new circular buffer
  if ((*buf = malloc(sizeof(CircBuf_t))) == NULL)
  {
    return CB_ENUM_ALLOC_FAILURE;
  }

  PRINTF("struct pointer: %p\n", (*buf));

  // Allocate the internal buffer to size requested
  if (((*buf)->buffer = malloc(sizeof(length))) == NULL)
  {
    return CB_ENUM_ALLOC_FAILURE;
  }

  PRINTF("buffer pointer: %p\n", (*buf)->buffer);

  // Set the remaining elements of the circular buffer
  (*buf)->head     = (*buf)->buffer;
  (*buf)->tail     = (*buf)->buffer;
  (*buf)->length   = length;
  (*buf)->count    = 0;

  // Return success
  return CB_ENUM_NO_ERROR;
} // CircBufInitialize()


CB_Enum_t CircBufDestroy(CircBuf_t * buf)
{
  // Free the buffer
  free(buf->buffer);

  // Free the circular buffer structure
  free(buf);

  // Return success
  return CB_ENUM_NO_ERROR;
} // CircBufDestroy()

CB_Enum_t CircBufAddItem(CircBuf_t * buf, uint8_t payload)
{
  // Check for null pointer
  CB_CHECK_NULL(buf);

  // Make sure there is room in the buffer
  if (buf->count == buf->length)
  {
    return CB_ENUM_FULL;
  }

  // Wrap buffer if needed and set
  PRINTF("length: %ld\n", buf->head - buf->buffer);
  if (buf->head - buf->buffer == buf->length - 1)
  {
    *(buf->head) = payload;
    buf->head = buf->buffer;
  }
  // No wrap is necessary increment head and set
  else
  {
    *(buf->head) = payload;
    buf->head++;
  }

  // Increment count
  buf->count++;

  // Return success
  return CB_ENUM_NO_ERROR;
} // CircBufAddItem()

CB_Enum_t CircBufRemoveItem(CircBuf_t * buf, uint8_t * payload)
{
  // Check for null pointer
  CB_CHECK_NULL(buf);

  // Make sure there is an item to read
  if (buf->count == 0)
  {
    return CB_ENUM_NO_EMPTY;
  }

  // Return success
  return CB_ENUM_NO_ERROR;
} // CircBufRemoveItem()
