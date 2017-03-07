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
  CREATE_ITEM_DATA(item, LOG_ID_LOGGER_INITIALIZED, NULL, 0);
  LOG_ITEM(item);
  CREATE_ITEM_DATA(item, LOG_ID_SYSTEM_INITIALIZED, NULL, 0);
  LOG_ITEM(item);
#ifdef UART_INTERRUPTS
  // Make a buffer on analysis + 1 size for null terminator
  uint8_t recv_buffer[NUM_ANALYSIS + 1] = {0};

  // Hold results of analysis
  analysis_t result;

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
          CREATE_ITEM_STRING(item, LOG_ID_ERROR, "Circbuf remove failure");
          LOG_ITEM(item);
        }
      }

      // Return received buffer
      CREATE_ITEM_DATA(item, LOG_ID_DATA_RECEIVED, recv_buffer, NUM_ANALYSIS);
      LOG_ITEM(item);

      // Indicate analysis has started
      CREATE_ITEM_DATA(item, LOG_ID_DATA_ANALYSIS_STARTED, NULL, 0);
      LOG_ITEM(item);

      // Do analysis
      if (analyze_bytes(recv_buffer, &result, NUM_ANALYSIS) != SUCCESS)
      {
        CREATE_ITEM_STRING(item, LOG_ID_ERROR, "Analyze bytes failure");
        LOG_ITEM(item);
        return FAILURE;
      }

#ifdef BINARY_LOGGER
      // Convert alpha, num, punc, and mis values to report over log
      CREATE_ITEM_DATA(item, LOG_ID_DATA_ALPHA_COUNT, &result.alpha, sizeof(result.alpha));
      LOG_ITEM(item);

      CREATE_ITEM_DATA(item, LOG_ID_DATA_NUMERIC_COUNT, &result.num, sizeof(result.num));
      LOG_ITEM(item);

      CREATE_ITEM_DATA(item, LOG_ID_DATA_PUNCTUATION_COUNT, &result.punc, sizeof(result.punc));
      LOG_ITEM(item);

      CREATE_ITEM_DATA(item, LOG_ID_DATA_MISC_COUNT, &result.misc, sizeof(result.misc));
      LOG_ITEM(item);
#else // BINARY_LOGGER
      // Convert alpha, num, punc, and mis values to report over log
      int8_t itoa_buffer[ITOA_SIZE] = {0};
      my_itoa(itoa_buffer, result.alpha, BASE_10);
      CREATE_ITEM_STRING(item, LOG_ID_DATA_ALPHA_COUNT, itoa_buffer);
      LOG_ITEM(item);

      my_itoa(itoa_buffer, result.num, BASE_10);
      CREATE_ITEM_STRING(item, LOG_ID_DATA_NUMERIC_COUNT, itoa_buffer);
      LOG_ITEM(item);

      my_itoa(itoa_buffer, result.punc, BASE_10);
      CREATE_ITEM_STRING(item, LOG_ID_DATA_PUNCTUATION_COUNT, itoa_buffer);
      LOG_ITEM(item);

      my_itoa(itoa_buffer, result.misc, BASE_10);
      CREATE_ITEM_STRING(item, LOG_ID_DATA_MISC_COUNT, itoa_buffer);
      LOG_ITEM(item);
#endif // BINARY_LOGGER
      // Indicate analysis is complete
      CREATE_ITEM_DATA(item, LOG_ID_DATA_ANALYSIS_COMPLETED, NULL, 0);
      LOG_ITEM(item);
    }
  }
#else // UART_INTERRUPTS
#ifdef FRDM
  for (uint8_t i = 0; i < NUM_ANALYSIS; i++)
  {
    int8_t byte = uart_receive_byte();
    uart_send_byte(byte);
  }
#endif // FRDM
#endif // UART_INTERRUPTS
  // System Halted
  CREATE_ITEM_DATA(item, LOG_ID_SYSTEM_HALTED, NULL, 0);
  LOG_ITEM(item);

  // Destroy logs
  log_destroy();

  return SUCCESS;
} // project_2_data_analysis()
