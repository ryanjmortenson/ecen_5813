#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "memory.h"
#include "data.h"
#include "project1.h"
#include "unit_tests.h"

int main()
{

#ifdef PROJECT1
  // Execute the required functions for project1
  project_1_report();
  test_data1();
  test_data2();
  test_memory();
#endif

#ifdef UNIT
  // Execute unit tests for memory.c
  memory_unit();
  data_unit();
#endif

  return 0;
}
