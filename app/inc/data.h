#ifndef __DATA_H__
#define __DATA_H__

#include <stdint.h>

// Function prototypes
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base);
int32_t my_atoi(int8_t * str);
int8_t big_to_little32(uint32_t * data, uint32_t length);
int8_t little_to_big32(uint32_t * data, uint32_t length);
void print_memory(uint8_t * start, uint32_t length);

#endif
