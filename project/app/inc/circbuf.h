#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

#include <stdint.h>

// Status enum for circular buffer functions
typedef enum CB_Enum
{
  CB_ENUM_NO_ERROR,
  CB_ENUM_FULL,
  CB_ENUM_EMPTY,
  CB_ENUM_NULL_POINTER,
  CB_ENUM_NO_LENGTH,
  CB_ENUM_ALLOC_FAILURE,
} CB_Enum_t;

// Circular buffer structure
typedef struct CircBuf
{
  uint8_t * buffer;
  uint8_t * head;
  uint8_t * tail;
  uint8_t length;
  uint8_t count;

} CircBuf_t;

CB_Enum_t CircBufInitialize(CircBuf_t ** buf, uint8_t length);
CB_Enum_t CircBufDestroy(CircBuf_t * buf);
CB_Enum_t CircBufAddItem(CircBuf_t * buf, uint8_t payload);
CB_Enum_t CircBufRemoveItem(CircBuf_t * buf, uint8_t * payload);
CB_Enum_t CircBufBufferFull(CircBuf_t * buf);
CB_Enum_t CircBufEmpty(CircBuf_t * buf);
CB_Enum_t CircBufPeak(CircBuf_t * buf);

#define CB_CHECK_NULL(x) if (x == NULL) return CB_ENUM_NULL_POINTER;

#endif // __CIRCBUF_H__
