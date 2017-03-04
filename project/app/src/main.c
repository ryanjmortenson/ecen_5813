#include <stddef.h>
#include <stdint.h>
#include "circbuf.h"
#include "data.h"
#include "project1.h"
#include "project_defs.h"
#include "log.h"
#include "log_item.h"

#ifdef FRDM
#include "uart.h"
#else
#include "memory.h"
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

// Execute the required functions for project2
#ifdef PROJECT2
#define NUM_ANALYSIS (16)
#define ITOA_SIZE (16)
  uint8_t recv_buffer[NUM_ANALYSIS + 1] = {0};
  int8_t itoa_buffer[ITOA_SIZE] = {0};

  analysis_t result;
  log_item_t * item;

  // Init log and bail out if a failure occurs
  if (log_init())
  {
    return FAILURE;
  }

  // Send log system initialized
  LOG_ITEM(item, LOG_ID_LOGGER_INITIALIZED, NULL);
  LOG_ITEM(item, LOG_ID_SYSTEM_INITIALIZED, NULL);

  // Loop forever receiving NUM_ANALYSIS bytes at a time and analyzing
  while(1)
  {

    uint8_t byte;
#ifndef FRDM
#define SCANF_SIZE (100)
    // Emulate uart putting characters into the receive buffer by using scanf
    uint8_t input[SCANF_SIZE];
    // See if there are NUM_ANALYSIS characters in the receive buffer
    if (circbuf_peak(receive, NUM_ANALYSIS, &byte) == CB_ENUM_BAD_INDEX)
    {
      scanf("%s", input);
      for (uint8_t i = 0; i < SCANF_SIZE; i++)
      {
        if (input[i] == 0)
        {
          break;
        }
        circbuf_add_item(receive, input[i]);
      }
    }
    my_memzero(input, SCANF_SIZE);
#endif // FRDM

    // See if there are NUM_ANALYSIS characters in the receive buffer
    if (circbuf_peak(receive, NUM_ANALYSIS, &byte) == CB_ENUM_NO_ERROR)
    {
      // Empty out circular buffer into a recv buffer for processing
      for (uint8_t i = 0; i < NUM_ANALYSIS; i++)
      {
        if (circbuf_remove_item(receive, (recv_buffer + i)) != CB_ENUM_NO_ERROR)
        {
          LOG_ITEM(item, LOG_ID_ERROR, "Circbuf remove failure");
        }
      }

      // Return received buffer
      LOG_ITEM(item, LOG_ID_DATA_RECEIVED, recv_buffer);

      // Add a null terminator to the end of the receive buffer for retransmit
      recv_buffer[NUM_ANALYSIS + 1] = 0;

      // Indicate analysis has started
      LOG_ITEM(item, LOG_ID_DATA_ANALYSIS_STARTED, NULL);

      // Do analysis
      if (analyze_bytes(recv_buffer, &result, NUM_ANALYSIS) != SUCCESS)
      {
        LOG_ITEM(item, LOG_ID_ERROR, "Analyze bytes failure");
        break;
      }

      // Convert alpha, num, punc, and mis values to report over log
      my_itoa(itoa_buffer, result.alpha, BASE_10);
      LOG_ITEM(item, LOG_ID_DATA_ALPHA_COUNT, itoa_buffer);
      my_itoa(itoa_buffer, result.num, BASE_10);
      LOG_ITEM(item, LOG_ID_DATA_NUMERIC_COUNT, itoa_buffer);
      my_itoa(itoa_buffer, result.punc, BASE_10);
      LOG_ITEM(item, LOG_ID_DATA_PUNCTUATION_COUNT, itoa_buffer);
      my_itoa(itoa_buffer, result.misc, BASE_10);
      LOG_ITEM(item, LOG_ID_DATA_MISC_COUNT, itoa_buffer);

      // Indicate analysis is complete
      LOG_ITEM(item, LOG_ID_DATA_ANALYSIS_COMPLETED, NULL);
    }
  }

  // System Halted
  LOG_ITEM(item, LOG_ID_SYSTEM_HALTED, NULL);

  // Destroy logs
  log_destroy();

#endif // PROJECT2
  return 0;
}
