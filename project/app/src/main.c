#include "project_defs.h"

#ifdef PROJECT1
#include "project1.h"
#endif

#ifdef PROJECT2
#include "project2.h"
#endif

#ifdef PROJECT3
#include "project3.h"
#endif

#ifdef PROJECT4
#include "project4.h"
#endif

#ifdef PROJECT5
#include "project5.h"
#endif

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
  // Execute the required functions for project3
  if(project_3_setup())
  {
    return FAILURE;
  }
  project_3_profiler();
  project_3_spi();
#endif // PROJECT3

#ifdef PROJECT4
#if !defined(CIRCBUF_DMA) && !defined(UART_INTERRUPTS) && !defined(BBB)
#error Project 4 must use CIRCBUF_DMA or UART_INTERRUPTS
#endif
  // Execute the required functions for project4
  project_4_setup();
#endif // PROJECT4

#ifdef PROJECT5
#if !defined(CIRCBUF_DMA) && !defined(UART_INTERRUPTS) && !defined(BBB)
#error Project 5 must use CIRCBUF_DMA or UART_INTERRUPTS
#endif
  // Set up project 5
  project_5_setup();

  // Start wireless comms
  project_5_wireless_comms();
#endif // PROJECT5

  return 0;
}
