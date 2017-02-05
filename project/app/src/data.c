#include <stdint.h>
#include <stddef.h>
#include "memory.h"
#include "project_defs.h"

// REMOVE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include <stdio.h>

#define ASCII_NUM_OFFSET 48
#define ASCII_NUM_END 57
#define ASCII_ALPHA_OFFSET 55
#define MINUS_SIGN 45
#define BASE_10 10

/*
 * Function definitions see data.h for documentation
 */

int8_t * my_itoa(int8_t * str, int32_t data, int32_t base)
{
  int32_t counter = 0;
  int8_t *start = str;
  int8_t rev_start = 0;

  // Pointer is null return pointer to str
  if(str == NULL)
    return start;

  // Base is incorrect return pointer to str
  if(!(base != 16 || base != BASE_10 || base != 8 || base != 2))
    return start;

  // If data is negative then the MINUS_SIGN must be the first element of the
  // string.  The converted string will be backwards and must be reversed so
  // rev_start will be set to the first element and negate the data for
  // conversion.
  if(data < 0)
  {
    *str = MINUS_SIGN;
    counter++;
    rev_start = 1;
    data *= -1;
  }

  // Loop over data getting the mod base then divide by base.  The ASCII
  // character is mod + ASCII_NUM_OFFSET. Anything over BASE_10 in base 16 must
  // use the ASCII_ALPHA_OFFSET to get the correct character.
  do
  {
    int32_t mod = data % base;
    *(str + counter) = mod + (mod >= BASE_10 ? ASCII_ALPHA_OFFSET : ASCII_NUM_OFFSET);
    data /= base;
    counter++;
  } while(data > 0);

  // As stated before the string will be backwards so reverse
  my_reverse((uint8_t *)(str + rev_start), counter - rev_start);

  // Add a null terminator at the end of the string
  *(str + counter) = 0;

  return start;
} // my_itoa()

int32_t my_atoi(int8_t * str)
{
  uint32_t counter = 0;
  uint8_t current = 0;
  uint32_t value = 0;
  uint32_t magnitude = 1;
  uint8_t negative = 0;

  // String is NULL the only option for failure in atoi is NULL
  CHECK_NULL(str);

  // If this is a negative number set negative flag and increment
  // counter to start converting the integer
  if(*str == MINUS_SIGN)
  {
    negative++;
    counter++;
  }

  // Figure out the order of magnitude needed for conversion
  while(*(str + counter + 1))
  {
    magnitude *= BASE_10;
    counter++;
  }

  // Reset the counter to negative which is either 0 or 1
  counter = negative;

  // Loop over string converting ASCII characters to their
  // integer representation
  while((current = *(str + counter)))
  {
    if(current < ASCII_NUM_OFFSET && current > ASCII_NUM_END)
      return 0;
    value += magnitude * (current - ASCII_NUM_OFFSET);
    magnitude /= BASE_10;
    counter++;
  }

  // If the number is negative multiply by -1 before return
  return (negative) ? value*-1 : value;
} // my_atoi()

int8_t big_to_little32(uint32_t * data, uint32_t length)
{
  // Fail for null pointer
  CHECK_NULL(data);

  // Loop over data swapping bytes
  for(int i = 0; i < length; i++)
  {
    uint32_t value = *(data + i);
    *(data + i) = ((value & 0xff000000) >> 24 |
                   (value & 0x00ff0000) >> 8  |
                   (value & 0x0000ff00) << 8  |
                   (value & 0x000000ff) << 24);
  }

  return SUCCESS;
} // big_to_little32()

int8_t little_to_big32(uint32_t * data, uint32_t length)
{
  // Swapping little to big is the same as swapping big to little
  return big_to_little32(data, length);
} // little_to_big32()

void print_memory(uint8_t * start, uint32_t length)
{
  if (start == NULL)
  {
    printf("Passed in a NULL pointer");
  }
  else
  {
    // Loop over memory printing hex output
    for(int i = 0; i < length; i++)
    {
      printf("0x%02x ", *(start + i));
    }
    printf("\n");
  }
}
