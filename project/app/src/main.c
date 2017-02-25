#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "project1.h"
#include "project_defs.h"
#include "circbuf.h"

#ifdef UNITTEST
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

  return 0;
}
