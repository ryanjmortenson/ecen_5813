#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "data.h"
#include "memory.h"
#include "project1.h"
#include "project_defs.h"

#define ARRAY_SIZE (32)
#define MAX_ASCII_INT_CHARS (4)

uint8_t set_1[ARRAY_SIZE];
uint8_t set_2[ARRAY_SIZE];
uint8_t set_3[ARRAY_SIZE][MAX_ASCII_INT_CHARS];

void project_1_report()
{
  int counter = 0;

  // Create an array of characters 0123456789ABCDEF0123456789ABCD
  for(int i = 0; i < 2; i++)
  {
    for(int k = '0'; k <= '9'; k++)
    {
      *(set_1 + counter) = k;
      counter++;
    }

    for(int k = 'A'; k <= 'F'; k++)
    {
      *(set_1 + counter) = k;
      counter++;
    }
  }

  // Create an array of characters counting from 0 to 31
  counter = 0;
  for(int k = 0; k < ARRAY_SIZE ; k++)
  {
    *(set_2 + counter) = k;
    counter++;
  }

} // project_1_report()

void test_data1()
{

  // Get the casted array size
  const uint8_t casted_size = ARRAY_SIZE*sizeof(uint8_t)/sizeof(uint32_t);

  // Print the memory before byte swap
  PRINTF("Before big_to_little32\n");
  print_memory(set_1, ARRAY_SIZE);

  // Cast the uint8_t as uint32_t and convert
  if (big_to_little32((uint32_t *)set_1, casted_size) != SUCCESS)
  {
    PRINTF("An error occured using big_to_little32())");
  }

  // Print the memory after byte swap
  PRINTF("After big_to_little32\n");
  print_memory(set_1, ARRAY_SIZE);

  // Cast the uint8_t as uint32_t and convert
  if (little_to_big32((uint32_t *)set_1, casted_size) != SUCCESS)
  {
    PRINTF("An error occured using little_to_big32()");
  }

  // Print the memory after second byte swap
  PRINTF("After little_to_big32\n");
  print_memory(set_1, ARRAY_SIZE);
} // test_data1()

void test_data2()
{
  // Make a buffer to store returns from my_atoi()
  uint32_t buffer[ARRAY_SIZE];

  // Cast to uint8_t and memset to 0
  my_memset((uint8_t *)buffer, ARRAY_SIZE*sizeof(uint32_t)/sizeof(uint8_t), 0);

  // Convert all integers in buffer to a string of ASCII characters
  PRINTF("Converting integers into ASCII characters\n");
  for(int i = 0; i < ARRAY_SIZE; i++)
  {
    my_itoa((int8_t *)*(set_3 + i), *(set_2 + i), 10);
    print_memory(*(set_3 + i), MAX_ASCII_INT_CHARS);
  }

  // Convert all ASCII characters in buffer to integers
  PRINTF("Converting ASCII characters into integers\n");
  for(int i = 0; i < ARRAY_SIZE; i++)
  {
    // Set a pointer to the current buffer position
    uint32_t *p_buffer = (buffer + i);
    *p_buffer = my_atoi((int8_t *)*(set_3 + i));

    // If my_atoi() returned 0 it could be a failure or a valid 0
    if (*p_buffer == 0)
    {
      PRINTF("my_atoi() returned 0 which may indicate failure\n");
    }
    print_memory((uint8_t *)p_buffer, 4);
  }
} // test_data2()

void test_memory()
{
  uint32_t res = 0;

  // Show memory before
  PRINTF("Memory before manipulation\n");
  print_memory(set_2, ARRAY_SIZE);

  // Execute memory manipulation requested
  if ((res = my_reverse(set_2, 12)) != SUCCESS)
  {
    PRINTF("my_reverse() returned failure of %d\n", res);
  }

  if ((my_memset((set_2 + 16), 3, 0xEE)) != SUCCESS)
  {
    PRINTF("my_memset() returned failure of %d\n", res);
  }

  if ((res = my_memmove((set_2 + 25), (set_2 + 20), 6)) != SUCCESS)
  {
    PRINTF("my_memmove() returned failure of %d\n", res);
  }

  if ((res = my_memzero((set_2 + 11), 3)) != SUCCESS)
  {
    PRINTF("my_memzero() returned failure of %d\n", res);
  }

  if ((res = my_memmove(set_2, (set_2 + 8), 8)) != SUCCESS)
  {
    PRINTF("my_memmove() returned failure of %d\n", res);
  }

  // Show memory after
  PRINTF("Memory after manipulation\n");
  print_memory(set_2, ARRAY_SIZE);
} // test_memory()
