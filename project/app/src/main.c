#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "memory.h"
#include "data.h"
#include "project1.h"

#define INVALID_PARAM 2
#define NULL_POINTER 1
#define SUCCESS 0

/*
 * \brief Wrapper function used to test my_reverse
 *
 * \param str pointer to array
 * \param comp array to compare against for pass/fail
 * \param length length of pointer
 * \return pass/fail results
 *
 */
void my_reverseWrapper(char *str, char *comp, int length)
{
  // Reverse string and check reults of function call
  int res = my_reverse(str, length);
  if (res == SUCCESS)
  {
    // Compare my_reversed string to expected result
    if (!strncmp(str, comp, length))
    {
      printf("Passed my_reverse\n");
    }
    else
    {
      printf("Failed my_reverse, my_reversed message isn't correct\n");
    }
  }
  // Function returned a NULL_POINTER failure
  else if (res == NULL_POINTER)
  {
    printf("Fail my_reverse, function returned NULL_POINTER\n");
  }
  // Function returned an INVALID_PARAM failure
  else if (res == INVALID_PARAM)
  {
    printf("Fail my_reverse, function returned INVALID_PARAM\n");
  }
  // Function returned unknown result
  else
  {
    printf("Failed for unknown reason\n");
  }
}

void main()
{
#ifdef TESTING
  // Make a set of 3 arrays for testing
  uint8_t strings[][25] = {{"abcd"}, {"abcde"}, {"a"}};

  // Test an even number elements
  my_reverseWrapper(strings[0], "dcba", 4);

  // Test an odd number elements
  my_reverseWrapper(strings[1], "edcba", 5);

  // Test a single elements
  my_reverseWrapper(strings[2], "a", 1);

  // Test a NULL pointer
  my_reverseWrapper((char *) 0, "", 10);

  my_memset(strings[0], 4, 'o');
  my_memmove(strings[0], strings[1], 4);
  my_memzero(strings[2], 1);
  printf("%s \n", strings[0]);
  printf("%s \n", strings[1]);
  printf("%s \n", strings[2]);
  uint8_t buffer[25];

  uint8_t *result = my_itoa(buffer, -10, 10);
  result = my_itoa(buffer, -15791, 10);
  printf("%s \n", buffer);
  result = my_itoa(buffer, -15791, 16);
  printf("%s \n", buffer);
  result = my_itoa(buffer, -15791, 2);
  printf("%s \n", buffer);
  result = my_itoa(NULL, -15791, 2);
  if (result == NULL)
    printf("Result is null");

  uint32_t val[] = {1};
  printf("%d \n", my_atoi("-51234"));
  big_to_little32(val, 1);
  print_memory("1234", 4);
#endif

#ifdef PROJECT1
  project_1_report();
  test_data1();
  test_data2();
  test_memory();
#endif

#ifdef POINTERSTUFF
  unsigned char test[8] = {0};
  unsigned char *ptr = test;
  *ptr = 0xF1 & 127;
  ptr++;
  *ptr += 17;
  ptr += 2;
  *ptr = 15 % 4;
  ptr--;
  *ptr >>= 4;
  ptr = test + 5;
  *ptr = (1<<5)|(4<<2);
  *(test + 7) = 22;
  print_memory(test, 8);
#endif
}
