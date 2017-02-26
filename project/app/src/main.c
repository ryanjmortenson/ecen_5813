#include "project1.h"
#ifdef FRDM
#include "uart.h"
#include "log.h"
#endif // FRDM

int main()
{

#ifdef PROJECT1
  // Execute the required functions for project1
  project_1_report();
  test_data1();
  test_data2();
  test_memory();
#endif

#ifdef PROJECT2
  // Execute the required functions for project2
#if FRDM
  uart_configure(115200);
  while(1)
    log_string((uint8_t *)"TRYING LOG\n");
#endif // FRDM
#endif

  return 0;
}
