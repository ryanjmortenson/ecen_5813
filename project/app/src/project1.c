#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "data.h"
#include "memory.h"
#include "project1.h"

#define ARRAY_SIZE 32

uint8_t set_1[ARRAY_SIZE];
uint8_t set_2[ARRAY_SIZE];
uint8_t set_3[ARRAY_SIZE];

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

  // Create an array of characters abcdefghijklmnopqrstuvwxyzABCDEF
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
} // project_1_report()

void test_data1()
{
  // Print the memory before byte swap
  printf("Before big_to_little32\n");
  print_memory(set_1, ARRAY_SIZE);
  big_to_little32((int32_t *)set_1, 8);

  // Print the memory after byte swap
  printf("After big_to_little32\n");
  print_memory(set_1, ARRAY_SIZE);
  little_to_big32((int32_t *)set_1, 8);

  // Print the memory after second byte swap
  printf("After little_to_big32\n");
  print_memory(set_1, ARRAY_SIZE);
} // test_data1()

void test_data2()
{
  uint8_t buffer[100];
  uint32_t buffer2[ARRAY_SIZE];
  my_memset(buffer, 0, 100);

  // Convert all integers in buffer to ASCII characters
  printf("Converting integers into ASCII characters\n");
  for(int i = 0; i < ARRAY_SIZE; i++)
  {
    my_itoa(buffer, *(set_2 + i), 10);
    print_memory(buffer, 10);
    printf("%s \n", buffer);
  }

  // Convert all ASCII characters in buffer to integers
  printf("Converting ASCII characters into integers\n");
  for(int i = 0; i < ARRAY_SIZE; i++)
  {
    *(buffer + i) = my_atoi(&*(set_3 + i));
    print_memory((uint8_t *)buffer, 4);
  }
} // test_data2()

void test_memory()
{
  // Show memory before
  printf("Memory before manipulation\n");
  print_memory(set_2, ARRAY_SIZE);

  // Execute memory manipulation requested
  my_reverse(set_2, 12);
  my_memset((set_2 + 16), 3, 0xEE);
  my_memmove((set_2 + 25), (set_2 + 20), 6);
  my_memzero((set_2 + 11), 3);
  my_memmove(set_2, (set_2 + 8), 8);


  // Show memory after
  printf("Memory after manipulation\n");
  print_memory(set_2, ARRAY_SIZE);
} // test_memory()
