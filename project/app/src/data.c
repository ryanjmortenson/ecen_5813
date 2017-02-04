#include <stdint.h>
#include <stddef.h>
#include "memory.h"

// 'REMOVE!!!!!!
#include <stdio.h>

#define INVALID_PARAM 2
#define NULL_POINTER 1
#define SUCCESS 0
#define ASCII_NUM_OFFSET 48
#define ASCII_ALPHA_OFFSET 55

/*
 * \brief Function used to convert and integer into a string
 *
 * \param str pointer to array holding converted string
 * \param dst data to convert
 * \param length base used to conver
 * \return pointer to
 *
 */
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base)
{
  int32_t counter = 0;
  int8_t *start = str;
  int8_t revStart = 0;

  //
  if(str == NULL)
    return (uint8_t*) NULL_POINTER;

  if(!(base != 16 || base != 10 || base != 8 || base != 2))
    return (uint8_t*) INVALID_PARAM;

  if(data < 0)
  {
    *str = '-';
    counter++;
    revStart = 1;
    data *= -1;
  }

  while(data > 0)
  {
    int32_t mod = data % base;
    *(str + counter) = mod + (mod >= 10 ? ASCII_ALPHA_OFFSET : ASCII_NUM_OFFSET);
    data /= base;
    counter++;
  }

  my_reverse((str + revStart), counter - revStart);
  *(str + counter) = '\0';

  return start;
}

/*
 * \brief Function used to convert and integer into a string
 *
 * \param str pointer to array holding converted string
 * \param dst data to convert
 * \param length base used to conver
 * \return pointer to
 *
 */
int32_t my_atoi(int8_t * str)
{
  uint32_t counter = 0;
  uint8_t current = 0;
  uint32_t value = 0;
  uint32_t magnitude = 1;
  uint8_t negative = 0;

  if(str == NULL)
    return 0;

  if(*str == '-')
  {
    negative = 1;
    counter = 1;
  }

  while(*(str + counter + 1))
  {
    magnitude *= 10;
    counter++;
  }

  counter = negative;

  while(current = *(str + counter))
  {
    if(current < 48 && current > 57)
      return 0;
    value += magnitude * (current - 48);
    magnitude /= 10;
    counter++;
  }
  return (negative) ? value*-1 : value;
}

int8_t big_to_little32(uint32_t * data, uint32_t length)
{
  if(data== NULL)
    return 0;

  for(int i = 0; i < length; i++)
  {
    uint32_t value = *(data + i);
    *(data + i) = ((value & 0xff000000) >> 24 |
                   (value & 0x00ff0000) >> 8  |
                   (value & 0x0000ff00) << 8  |
                   (value & 0x000000ff) << 24);
  }
}

int8_t little_to_big32(uint32_t * data, uint32_t length)
{
  return big_to_little32(data, length);
}

void print_memory(uint8_t * start, uint32_t length)
{
  for(int i = 0; i < length; i++)
  {
    printf("0x%02x ", *(start + i));
  }
  printf("\n");
}
