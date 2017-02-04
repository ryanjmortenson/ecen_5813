#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>

// Function prototypes
int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length);
int8_t my_memset(uint8_t * src, uint32_t length, uint8_t value);
int8_t my_memzero(uint8_t * src, uint32_t length);
int8_t my_reverse(uint8_t * src, uint32_t length);

#endif
