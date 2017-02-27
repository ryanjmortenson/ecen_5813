#include <stdint.h>
#include "circbuf.h"
#include "project1.h"
#include "log.h"
#include "log_item.h"
#ifdef FRDM
#include "uart.h"
#endif // FRDM

extern circbuf_t * receive;
extern circbuf_t * transmit;

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

  uint8_t byte = 0;

  circbuf_init(&receive, 100);
  circbuf_init(&transmit, 100);

  // Initialize uart
  uart_configure(BAUD_RATE);

  log_item_t * item;
  create_log_item(&item, LOG_ID_ERROR, (uint8_t *)"test", 5);
  log_item(item);
  destroy_log_item(item);

  while(1)
  {
    if(circbuf_empty(receive) != CB_ENUM_NO_ERROR)
    {
      circbuf_remove_item(receive, &byte);
      if (byte == 'q')
      {
        break;
      }
      circbuf_add_item(transmit, byte);
      signal_transmit();
    }
  }

  circbuf_destroy(receive);
  circbuf_destroy(transmit);
#endif // FRDM
#endif // PROJECT2
  return 0;
}
