#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include "data.h"
#include "log.h"
#include "log_item.h"
#include "project_defs.h"
#include "project2.h"

#ifdef FRDM
#include "uart.h"
#else
#include "memory.h"
#endif // FRDM

// Circular buffers for logging found in log.c
extern circbuf_t * receive;
extern circbuf_t * transmit;

uint8_t project_2_data_analysis()
{
  // Make a buffer on analysis + 1 size for null terminator
  uint8_t recv_buffer[NUM_ANALYSIS + 1] = {0};
  int8_t itoa_buffer[ITOA_SIZE] = {0};

  analysis_t result;

#ifdef VERBOSE
  // No need for a log item if not verbose
  log_item_t * item;
#endif // VERBOSE

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
    // Emulate uart putting characters into the receive buffer by using scanf
    uint8_t input[SCANF_SIZE];

    // Wait for input if there are less than NUM_ANALYSIS bytes in
    // circular buffer
    if (circbuf_peek(receive, NUM_ANALYSIS, &byte) == CB_ENUM_BAD_INDEX)
    {
      scanf("%s", input);
      for (uint8_t i = 0; i < SCANF_SIZE; i++)
      {
        // Break out of a null terminator is reached before scanf size
        if (input[i] == 0)
        {
          break;
        }

        // Add each item to circular buffer
        circbuf_add_item(receive, input[i]);
      }
    }

    // Zero out input for next read
    my_memzero(input, SCANF_SIZE);
#endif // FRDM

    // See if there are NUM_ANALYSIS characters in the receive buffer
    if (circbuf_peek(receive, NUM_ANALYSIS, &byte) == CB_ENUM_NO_ERROR)
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

      // Add a null terminator to the end of the receive buffer for
      // retransmit
      recv_buffer[NUM_ANALYSIS + 1] = 0;

      // Indicate analysis has started
      LOG_ITEM(item, LOG_ID_DATA_ANALYSIS_STARTED, NULL);

      // Do analysis
      if (analyze_bytes(recv_buffer, &result, NUM_ANALYSIS) != SUCCESS)
      {
        LOG_ITEM(item, LOG_ID_ERROR, "Analyze bytes failure");
        return FAILURE;
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

  return SUCCESS;
} // project_2_data_analysis()