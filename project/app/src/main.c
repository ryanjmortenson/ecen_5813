#include <stdint.h>
#include "project1.h"
#include "log.h"
#include "log_item.h"
#ifdef FRDM
#include "uart.h"
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
#if FRDM
  // Initialize uart
  uart_configure(BAUD_RATE);
#endif // FRDM

  log_item_t * item;
  create_log_item(&item, LOG_ID_ERROR, (uint8_t *)"test", 5);
  log_item(item);
  destroy_log_item(item);

  while(0)
  {
    LOG_RAW_STRING("TRYING LOG\n");
    LOG_RAW_INT(-7235);
    LOG_RAW_DATA("LOGGING DATA", 12);
  }

#endif // PROJECT2

  return 0;
}
