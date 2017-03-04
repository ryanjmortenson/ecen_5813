#include <stdint.h>
#include "circbuf.h"
#include "data.h"
#include "log.h"
#include "log_item.h"
#include "project_defs.h"

#ifdef FRDM
#include "uart.h"
#endif // FRDM

#define CIRC_BUF_SIZE (1024)

/*
 * Function definitions see log.h for documentation
 */

// Transmit and receive circular buffers
circbuf_t * transmit;
circbuf_t * receive;

int8_t log_data(uint8_t * bytes, uint8_t length)
{
  // Check for null pointer
  CHECK_NULL(bytes);

  // Loop over string sending bytes
  for (uint8_t i = 0; i < length; i++)
  {
    if (circbuf_add_item(transmit, *(bytes + i)) != CB_ENUM_NO_ERROR)
    {
      return FAILURE;
    }
  }

  return SUCCESS;
} // log_data()

int8_t log_string(int8_t * str)
{
  // Check for null pointer
  CHECK_NULL(str);

  // Loop over string sending bytes
  while(*str)
  {
    if (circbuf_add_item(transmit, (*str++)) != CB_ENUM_NO_ERROR)
    {
      return FAILURE;
    }
  }

  return SUCCESS;
} // log_string()

int8_t log_integer(int32_t integer)
{
  // Createa a buffer to hold the integer
  int8_t buffer[MAX_INT_LEN];

  // Convert integer to string in base 10
  if(!(my_itoa(buffer, integer, BASE_10)))
  {
    return FAILURE;
  }

  // Log the integer string
  return log_string((int8_t *)buffer);

} // log_integer()

void log_flush()
{
  // Loop until the buffer is empty
#ifdef FRDM
  while (circbuf_empty(transmit) != CB_ENUM_NO_ERROR);
#else
  while (circbuf_empty(transmit) != CB_ENUM_NO_ERROR)
  {
    uint8_t byte = 0;
    circbuf_remove_item(transmit, &byte);
    printf("%c", byte);
  }
#endif // FRDM
} // log_flush()

uint8_t log_item(log_item_t * item)
{
  if (item == NULL)
  {
    LOG_RAW_STRING("\nLog Item is null");
    return FAILURE;
  }

  // Place the length on the line
  LOG_RAW_STRING("\nLog Payload Length: ");
  LOG_RAW_INT(item->log_length);
  LOG_RAW_STRING("\nLog ID: ");
  LOG_RAW_STRING(log_id_str[item->log_id]);
  LOG_RAW_STRING("\nLog Payload: ");
  LOG_RAW_DATA(item->payload, item->log_length);
  LOG_RAW_STRING("\n");

  // Start tranmission and wait for the circular buffer to empty
#ifdef FRDM
  TRANSMIT_READY;
#endif // FRDM
  LOG_RAW_FLUSH();

  return SUCCESS;
} // log_item()

uint8_t log_init()
{

#ifdef FRDM
  // Initialize uart
  uart_configure(BAUD_RATE);
#endif // FRDM

  // Try to initialize receive buffer
  if (circbuf_init(&receive, CIRC_BUF_SIZE) != CB_ENUM_NO_ERROR)
  {
    return FAILURE;
  }

  // Try to initialize receive buffer
  if (circbuf_init(&transmit, CIRC_BUF_SIZE) != CB_ENUM_NO_ERROR)
  {
    return FAILURE;
  }

  return SUCCESS;
} // log_init()

void log_destroy()
{
  // Destroy the circular buffers, since these exist for all time
  // checking an error before shutdown is a waste
  circbuf_destroy(receive);
  circbuf_destroy(transmit);
} // log_destroy()
