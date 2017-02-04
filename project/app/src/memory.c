#include <stdint.h>
#include <stddef.h>
#include "project_defs.h"

/*
 * Function definitions see memory.h for documentation
 */

uint8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length)
{
  // Check for null pointers
  CHECK_NULL(src);
  CHECK_NULL(dst);

  // Copy src to dst
  for (int i = 0; i < length; i++)
  {
    *(dst + i) = *(src + i);
  }

  return SUCCESS;
} // my_memmove()

uint8_t my_memset(uint8_t *src, uint32_t length, uint8_t value)
{

  // Check for null pointers
  CHECK_NULL(src);

  // Copy value to src
  for (int i = 0; i < length; i++)
  {
    *(src + i) = value;
  }

  return SUCCESS;
} // my_memset()

uint8_t my_memzero(uint8_t *src, uint32_t length)
{
  // Call memset with 0 as value
  return my_memset(src, length, 0);
} // my_memzero()

uint8_t my_reverse(uint8_t *src, uint32_t length)
{
  uint8_t temp;
  uint32_t middle = length >> 1;
  uint32_t end = length - 1;

  // Check for null pointers
  CHECK_NULL(src);

  // Reverse array by swapping elements around a center point
  for (int i = 0; i < middle; i++)
  {
    temp = *(src + end - i);
    *(src + end - i) = *(src + i);
    *(src + i) = temp;
  }

  return SUCCESS;
} // my_reverse()
