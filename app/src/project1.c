#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "data.h"

#define ARRAY_SIZE 32

uint8_t set_1[ARRAY_SIZE];
uint8_t set_2[ARRAY_SIZE];
uint8_t set_3[ARRAY_SIZE];

void project_1_report()
{
  int counter = 0;
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

  counter = 0;
  for(int k = 0; k < ARRAY_SIZE ; k++)
  {
    *(set_2 + counter) = k;
    counter++;
  }

  counter = 0;
  for(int k = 'a'; k <= 'z'; k++)
  {
    *(set_3 + k) = k;
    counter++;
  }

  for(int k = 'A'; k <= 'F'; k++)
  {
    *(set_3 + k) = k;
    counter++;
  }
}

void test_data1()
{
  print_memory(set_1, ARRAY_SIZE);
  big_to_little32((int32_t *)set_1, 8);
  print_memory(set_1, ARRAY_SIZE);
  little_to_big32((int32_t *)set_1, 8);
  print_memory(set_1, ARRAY_SIZE);
}

void test_data2()
{
  uint8_t buffer[100];
  for(int i = 0; i < ARRAY_SIZE; i++)
  {
    my_itoa(buffer, (int32_t) *(set_2 + i), 10);
    print_memory(buffer, 4);
  }
}
