#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "memory.h"
#include "data.h"
#include "project1.h"

int main()
{
#ifdef TESTING

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

}
