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
#ifdef CIRCBUF
    if (circbuf_add_item(transmit, *(bytes + i)) != CB_ENUM_NO_ERROR)
    {
      return FAILURE;
    }
#else // CIRCBUF
#ifdef FRDM
    uart_send_byte(*(bytes + i));
#else // FRDM
    printf("%c", *(bytes + i));
#endif // FRDM
#endif // CIRCBUF
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
#ifdef CIRCBUF
    if (circbuf_add_item(transmit, (*str++)) != CB_ENUM_NO_ERROR)
    {
      return FAILURE;
    }
#else // CIRCBUF
#ifdef FRDM
    uart_send_byte(*str++);
#else  // FRDM
    printf("%c", *str++);
#endif // FRDM
#endif // CIRCBUF
  }

  return SUCCESS;
} // log_string()

int8_t log_integer(int32_t integer)
{
  // Log the integer string
  return log_data((uint8_t *)&integer, 4);

} // log_integer()

void log_flush()
{

#ifdef CIRCBUF
#ifdef FRDM
  // Loop until the buffer is empty
  while (circbuf_empty(transmit) != CB_ENUM_EMPTY)
  {
#ifndef UART_INTERRUPTS
    uint8_t byte = 0;
    circbuf_remove_item(transmit, &byte);
    uart_send_byte(byte);
#else // UART_INTERRUPTS
    ;
#endif // UART_INTERRUPTS
  }

#else // FRDM
  // Loop until the buffer is empty placing items in circbuf
  while (circbuf_empty(transmit) != CB_ENUM_EMPTY)
  {
    uint8_t byte = 0;
    circbuf_remove_item(transmit, &byte);
    printf("%c", byte);
  }
#endif // FRDM
#endif // CIRCBUF
} // log_flush()

uint8_t log_item(log_item_t * item)
{
  if (item == NULL)
  {
    LOG_RAW_STRING("\nLog Item is null");
    return FAILURE;
  }

#ifdef BINARY_LOGGER
  LOG_RAW_DATA(&item->log_length, sizeof(item->log_length));
  LOG_RAW_DATA(&item->log_id, sizeof(item->log_id));
  LOG_RAW_DATA(item->payload, item->log_length);
#else
#ifdef VERBOSE
  int8_t itoa_buffer[10];
#endif // VERBOSE
  // Place the length on the line
  LOG_RAW_STRING("\nLog Payload Length: ");
  LOG_RAW_STRING(my_itoa(itoa_buffer, item->log_length, 10));
  LOG_RAW_STRING("\nLog ID: ");
  LOG_RAW_STRING(log_id_str[item->log_id]);
  LOG_RAW_STRING("\nLog Payload: ");
  LOG_RAW_DATA(item->payload, item->log_length);
  LOG_RAW_STRING("\n");
#endif // BINARY_LOGGER

  // Start tranmission and wait for the circular buffer to empty
#ifdef FRDM
#ifdef UART_INTERRUPTS
  TRANSMIT_READY;
#endif // UART_INTERRUPTS
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

#ifdef CIRCBUF
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
#endif // CIRCBUF

  return SUCCESS;
} // log_init()

void log_destroy()
{
#ifdef CIRCBUF
  // Destroy the circular buffers, since these exist for all time
  // checking an error before shutdown is a waste
  circbuf_destroy(receive);
  circbuf_destroy(transmit);
#endif // CIRCBUF
} // log_destroy()
