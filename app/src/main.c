#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "memory.h"

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
}
