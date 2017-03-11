#ifdef PROJECT1
#include "project1.h"
#endif

#ifdef PROJECT2
#include "project2.h"
#endif

#ifdef FRDM
#include "spi.h"
#endif // FRDM

int main()
{

#ifdef PROJECT1
  // Execute the required functions for project1
  project_1_report();
  test_data1();
  test_data2();
  test_memory();
#endif // PROJECT1

#ifdef PROJECT2
  // Execute the required functions for project2
  project_2_data_analysis();
#endif // PROJECT2

#ifdef PROJECT3
#ifdef FRDM
  spi_configure();
#endif // FRDM
#endif // PROJECT3
  return 0;
}
