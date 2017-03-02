#include <stdint.h>
#include "circbuf.h"
#include "data.h"
#include "project1.h"
#include "log.h"
#include "log_item.h"
#ifdef FRDM
#include "uart.h"
#endif // FRDM

extern circbuf_t * receive;
extern circbuf_t * transmit;
extern circbuf_t * receive_16;

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
#define NUM_ANALYSIS (16)
#if FRDM

  circbuf_init(&receive, 1024);
  circbuf_init(&transmit, 1024);
  analysis_t result;

  // Initialize uart
  uart_configure(BAUD_RATE);

  log_item_t * item;
  create_log_item(&item, LOG_ID_ERROR, (uint8_t *)"test", 5);
  log_item(item);
  destroy_log_item(item);

  while(1)
  {
    uint8_t byte;
    if (circbuf_peak(receive, NUM_ANALYSIS, &byte) == CB_ENUM_NO_ERROR)
    {
      analyze_bytes(receive, &result, NUM_ANALYSIS);
      LOG_RAW_STRING("\nAlpha chars: ");
      LOG_RAW_INT(result.alpha);
      LOG_RAW_STRING("\nNum chars: ");
      LOG_RAW_INT(result.num);
      LOG_RAW_STRING("\nPunc chars: ");
      LOG_RAW_INT(result.punc);
      LOG_RAW_STRING("\nMisc chars: ");
      LOG_RAW_INT(result.misc);
      LOG_RAW_STRING("\n");
      TRANSMIT_READY;
      LOG_RAW_FLUSH();
    }
  }

  circbuf_destroy(receive);
  circbuf_destroy(transmit);
#endif // FRDM
#endif // PROJECT2
  return 0;
}
