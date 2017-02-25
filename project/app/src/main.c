#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "memory.h"
#include "data.h"
#include "project1.h"
#include "project_defs.h"
#include "circbuf.h"

#ifdef UNITTEST
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>
#include "unit_tests.h"
#endif

int main()
{

#ifdef PROJECT1
  // Execute the required functions for project1
  project_1_report();
  test_data1();
  test_data2();
  test_memory();
#endif

#ifdef UNITTEST
  // Execute unit tests for memory.c
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_my_memmove),
    cmocka_unit_test(test_my_memmove_dst_starts_in_src),
    cmocka_unit_test(test_my_memmove_dst_ends_in_src),
    cmocka_unit_test(test_my_memmove_null_ptrs),
    cmocka_unit_test(test_my_memset),
    cmocka_unit_test(test_my_memset_null_ptr),
    cmocka_unit_test(test_my_memzero),
    cmocka_unit_test(test_my_memzero_null_ptr),
    cmocka_unit_test(test_my_reverse_odd),
    cmocka_unit_test(test_my_reverse_even),
    cmocka_unit_test(test_my_reverse_single),
    cmocka_unit_test(test_my_reverse_max),
    cmocka_unit_test(test_my_reverse_null_ptr),
    cmocka_unit_test(test_big_to_little32),
    cmocka_unit_test(test_big_to_little32_null_ptr),
    cmocka_unit_test(test_little_to_big32),
    cmocka_unit_test(test_little_to_big32_null_ptr)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
#endif

#ifdef CIRCBUF
  uint8_t read = 0;

  circbuf_t * buf = NULL;
  circ_buf_init(&buf, 10);

  PRINTF("Starting\n");
  PRINTF("CB Empty %d\n", circ_buf_empty(buf));
  PRINTF("CB Full %d\n", circ_buf_full(buf));

  for (uint8_t i = 0; i < 6; i++)
  {
    PRINTF("add result: %d\n", circ_buf_add_item(buf, i));
  }

  for (uint8_t i = 0; i < 6; i++)
  {
    PRINTF("remove result: %d\n", circ_buf_remove_item(buf, &read));
    PRINTF("read result: %d\n", read);
  }

  for (uint8_t i = 10; i < 20; i++)
  {
    PRINTF("add result: %d\n", circ_buf_add_item(buf, i));
  }

  PRINTF("CB Full %d\n", circ_buf_full(buf));

  for (uint8_t i = 0; i < 11; i++)
  {
    PRINTF("peak result: %d\n", circ_buf_peak(buf, i, &read));
    PRINTF("read result: %d\n", read);
  }

  for (uint8_t i = 0; i < 11; i++)
  {
    PRINTF("remove result: %d\n", circ_buf_remove_item(buf, &read));
    PRINTF("read result: %d\n", read);
  }

  circ_buf_destroy(buf);
#endif

  return 0;
}
