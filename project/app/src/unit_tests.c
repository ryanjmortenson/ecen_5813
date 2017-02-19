#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "memory.h"
#include "project1.h"
#include "project_defs.h"

#define STR_LEN (10)

void memory_unit()
{
  uint8_t *str = (uint8_t *)"1234567890";
  uint8_t src[STR_LEN + 1] = {0};
  uint32_t res = 0;

  /**********************************************
  * The following tests my_memmove functionality
  * ********************************************/
  PRINTF("Testing my_memmove\n");

  // Test a normal copy with no overlap
  if((res = my_memmove(str, src, STR_LEN)) != SUCCESS)
  {
    PRINTF("my_memmove failed copying str with error %d\n", res);
  }
  PRINTF("%s\n", src);

  // Verify the strings match
  if ((res = strncmp((char *)src, (char *)str, STR_LEN)))
  {
    PRINTF("my_memmove(str, src, STR_LEN) doesn't match expected: error %d\n", res);
  }

  // Test an overlap where dst starts inside of src
  my_memmove((src + 2), (src + 5), 4);
  PRINTF("%s\n", src);
  if ((res = strncmp((char *)src, "1234534560", STR_LEN)))
  {
    PRINTF("my_memmove((src + 2), (src + 5), 4) doesn't match expected: strncmp error %d\n", res);
  }

  // Copy original string back into src
  if((res = my_memmove(str, src, STR_LEN)) != SUCCESS)
  {
    PRINTF("my_memmove failed copying str with error %d\n", res);
  }

  // Test an overlap where dst ends inside of src
  my_memmove((src + 5), (src + 1), 4);
  PRINTF("%s\n", src);
  if ((res = strncmp((char *)src, "1678967890", STR_LEN)))
  {
    PRINTF("my_memmove((src + 2), (src + 5), 4) doesn't match expected: strncmp error %d\n", res);
  }

  // Test src null pointer
  if ((res = my_memmove((uint8_t *)NULL, src, 4)) != NULL_POINTER)
  {
    PRINTF("my_memmove src failed NULL_POINTER check\n");
  }

  // Test dst null pointer
  if ((res = my_memmove(src, (uint8_t *)NULL, 4)) != NULL_POINTER)
  {
    PRINTF("my_memmove src failed NULL_POINTER check\n");
  }

  /**********************************************
  * The following tests my_memset functionality
  * ********************************************/
  PRINTF("Testing my_memset\n");

  // Test a normal memset
  if ((res = my_memset(src, STR_LEN, 'A')) != SUCCESS)
  {
    PRINTF("my_memset(src, STR_LEN, 'A') failed with res %d", res);
  }
  PRINTF("%s\n", src);

  // Validate src
  if ((res = strncmp((char *)src, "AAAAAAAAAA", STR_LEN)))
  {
    PRINTF("my_memset(src, STR_LEN, 'A') doesn't match expected: strncmp error %d\n", res);
  }

  // Test src null pointer
  if ((res = my_memset((uint8_t *)NULL, STR_LEN, 'A')) != NULL_POINTER)
  {
    PRINTF("my_memset src failed NULL_POINTER check\n");
  }

  /**********************************************
  * The following tests my_memzero functionality
  * ********************************************/
  PRINTF("Testing my_memzero\n");

  // Test a normal memset
  if ((res = my_memzero(src, STR_LEN)) != SUCCESS)
  {
    PRINTF("my_memzero(src, STR_LEN) failed with res %d", res);
  }
  PRINTF("%s\n", src);

  // Validate memory set to 0
  if ((res = strncmp((char *)src, "\0\0\0\0\0\0\0\0\0\0\0", STR_LEN)))
  {
    PRINTF("my_memzero(src, STR_LEN) didn't zero memory");
  }

  // Test src null pointer
  if ((res = my_memzero((uint8_t *)NULL, STR_LEN)) != NULL_POINTER)
  {
    PRINTF("my_memero src failed NULL_POINTER check\n");
  }

  /**********************************************
  * The following tests my_reverse functionality
  * ********************************************/
  PRINTF("Testing my_reverse\n");

  // Copy original string into src
  if((res = my_memmove(str, src, STR_LEN)) != SUCCESS)
  {
    PRINTF("my_memmove failed copying str with error %d\n", res);
  }
  PRINTF("%s\n", src);

  // Test an even reverse
  if ((res = my_reverse(src, STR_LEN)) != SUCCESS)
  {
    PRINTF("my_reverse(src, STR_LEN) failed with res %d", res);
  }
  PRINTF("%s\n", src);

  // Validate reverse
  if ((res = strncmp((char *)src, "0987654321", STR_LEN)))
  {
    PRINTF("my_reverse(src, STR_LEN) doesn't match expected: strncmp error %d\n", res);
  }

  // Place a single character string into src but copy the null terminator
  // to be able to print using PRINTF
  my_memmove((uint8_t *)"a", src, 2);

  // Test a single character reverse
  if ((res = my_reverse(src, 1)) != SUCCESS)
  {
    PRINTF("my_reverse(src, STR_LEN) failed with res %d", res);
  }
  PRINTF("%s\n", src);

  // Validate reverse
  if ((res = strncmp((char *)src, "a", STR_LEN)))
  {
    PRINTF("my_reverse(src, STR_LEN) doesn't match expected: strncmp error %d\n", res);
  }

  // Copy original string into src
  if((res = my_memmove(str, src, STR_LEN - 1)) != SUCCESS)
  {
    PRINTF("my_memmove failed copying str with error %d\n", res);
  }

  // Add null terminator so PRINTF displays correctly
  *(src + STR_LEN - 1) = 0;
  PRINTF("%s\n", src);

  // Test an odd reverse
  if ((res = my_reverse(src, STR_LEN - 1)) != SUCCESS)
  {
    PRINTF("my_reverse(src, STR_LEN) failed with res %d", res);
  }
  PRINTF("%s\n", src);

  // Validate reverse
  if ((res = strncmp((char *)src, "987654321", STR_LEN - 1)))
  {
    PRINTF("my_reverse(src, STR_LEN) doesn't match expected: strncmp error %d\n", res);
  }

  // Test src null pointer
  if ((res = my_reverse((uint8_t *)NULL, STR_LEN)) != NULL_POINTER)
  {
    PRINTF("my_reverse src failed NULL_POINTER check\n");
  }
}

void data_unit()
{
  int8_t str[STR_LEN] = {0};
  uint32_t res = 0;

  /**********************************************
  * The following tests my_itoa functionality
  * ********************************************/
  PRINTF("Testing my_itoa\n");

  // Test base 10 conversion with negative number
  my_itoa(str, -1589, 10);
  PRINTF("%s\n", str);

  // Validate reverse
  if ((res = strncmp((char *)str, "-1589", 5)))
  {
    PRINTF("my_itoa doesn't match expected: strncmp error %d\n", res);
  }

  // Test base 10 conversion with positive number
  my_itoa(str, 13456984, 10);
  PRINTF("%s\n", str);

  // Validate reverse
  if ((res = strncmp((char *)str, "13456984", 8)))
  {
    PRINTF("my_itoa doesn't match expected: strncmp error %d\n", res);
  }

  // Test base 16 conversion with negative number
  my_itoa(str, -65169, 16);
  PRINTF("%s\n", str);

  // Validate conversion
  if ((res = strncmp((char *)str, "-FE91", 5)))
  {
    PRINTF("my_itoa doesn't match expected: strncmp error %d\n", res);
  }

  // Test base 16 conversion with negative number
  my_itoa(str, 703588, 16);
  PRINTF("%s\n", str);

  // Validate conversion
  if ((res = strncmp((char *)str, "ABC64", 5)))
  {
    PRINTF("my_itoa doesn't match expected: strncmp error %d\n", res);
  }

  // Validate null pointer returns start
  if (my_itoa((int8_t *)NULL, 123, 10) != (int8_t *)NULL)
  {
    PRINTF("my_itoa didn't return the correct pointer for null pointer\n");
  }

  /**********************************************
  * The following tests my_atoi functionality
  * ********************************************/
  PRINTF("Testing my_atoi\n");

  // Check a positive integer
  if ((res = my_atoi((int8_t *)"123456")) != 123456)
  {
    PRINTF("my_atoi returned an incorrect value %d\n", res);
  }
  PRINTF("%d\n", res);

  // Check a negative integer
  if ((res = my_atoi((int8_t *)"-7890")) != -7890)
  {
    PRINTF("my_atoi returned an incorrect value %d\n", res);
  }
  PRINTF("%d\n", res);

  // Check a null pointer
  if ((res = my_atoi((int8_t *)NULL)) != 0)
  {
    PRINTF("my_atoi failed null pointer check\n");
  }

  // Check a invalid number
  if ((res = my_atoi((int8_t *)"13z4")) != 0)
  {
    PRINTF("my_atoi failed invalid parameter check\n");
  }

  /**********************************************
  * The following tests big_to_little32 functionality
  * ********************************************/
  PRINTF("Testing big_to_little32\n");
  uint32_t big_to_little = (0x01)  | (0x02 << 8) | (0x04 << 16) | (0x08 << 24);
  uint32_t temp = big_to_little;
  uint32_t little_to_big = (0x01 << 24)  | (0x02 << 16) | (0x04 << 8) | (0x08);

  // Execute big_to_little32
  if ((res = big_to_little32(&temp, 1)))
  {
    PRINTF("big_to_little failed with returning %d\n", res);
  }

  // Validate results
  if (temp != little_to_big)
  {
    PRINTF("big_to_little failed to get correct result %d\n", temp);
  }

  // Check a null pointer
  if ((res = big_to_little32((uint32_t *)NULL, 10)) != NULL_POINTER)
  {
    PRINTF("big_to_little32 failed null pointer check\n");
  }

  /**********************************************
  * The following tests little_to_big32 functionality
  * ********************************************/
  PRINTF("Testing little_to_big32\n");

  // Execute little_to_big32
  if ((res = little_to_big32(&temp, 1)))
  {
    PRINTF("little_to_big failed with returning %d\n", res);
  }

  // Validate results
  if (temp != big_to_little)
  {
    PRINTF("little_to_big failed to get correct result %d\n", temp);
  }

  // Check a null pointer
  if ((res = little_to_big32((uint32_t *)NULL, 10)) != NULL_POINTER)
  {
    PRINTF("little_to_big32 failed null pointer check\n");
  }
}
