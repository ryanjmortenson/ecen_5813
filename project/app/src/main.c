#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "memory.h"
#include "data.h"
#include "project1.h"

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
