#include <stdio.h>
#include <string.h>

#define INVALID_PARAM 2
#define NULL_POINTER 1
#define SUCCESS 0

/*
 * \brief Function used to reverse and array
 *
 * \param str pointer to array
 * \param length length of pointer
 * \return pass/fail results
 *
 */
char reverse(char *str, int length)
{
  char temp;
  int middle = length >> 1;
  int end = length - 1;

  // Check to make sure the pointer isn't 0
  if (str == 0)
    return NULL_POINTER;

  // An array can only have postive length
  if (length < 0)
    return INVALID_PARAM;

  // Reverse array by swapping elements around a center point
  for (int i = 0; i < middle; i++)
  {
    temp = *(str + end - i);
    *(str + end - i) = *(str + i);
    *(str + i) = temp;
  }

  return SUCCESS;
}

/*
 * \brief Wrapper function used to test reverse
 *
 * \param str pointer to array
 * \param comp array to compare against for pass/fail
 * \param length length of pointer
 * \return pass/fail results
 *
 */
void reverseWrapper(char *str, char *comp, int length)
{
  // Reverse string and check reults of function call
  int res = reverse(str, length);
  if (res == SUCCESS)
  {
    // Compare reversed string to expected result
    if (!strncmp(str, comp, length))
    {
      printf("Passed reverse\n");
    }
    else
    {
      printf("Failed reverse, reversed message isn't correct\n");
    }
  }
  // Function returned a NULL_POINTER failure
  else if (res == NULL_POINTER)
  {
    printf("Fail reverse, function returned NULL_POINTER\n");
  }
  // Function returned an INVALID_PARAM failure
  else if (res == INVALID_PARAM)
  {
    printf("Fail reverse, function returned INVALID_PARAM\n");
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
  char strings[][25] = {{"abcd"}, {"abcde"}, {"a"}};

  // Test an even number elements
  reverseWrapper(strings[0], "dcba", 4);

  // Test an odd number elements
  reverseWrapper(strings[1], "edcba", 5);

  // Test a single elements
  reverseWrapper(strings[2], "a", 1);

  // Test a NULL pointer
  reverseWrapper((char *) 0, "", 10);

  // Test an invalid length
  reverseWrapper("abc", "cba", -10);
}
