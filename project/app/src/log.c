#include <stdint.h>
#include "circbuf.h"
#include "control_lib.h"
#include "log.h"
#include "project_defs.h"

#ifdef FRDM
#include "uart.h"
#endif // FRDM

#define CIRC_BUF_SIZE (512)

/*
 * Function definitions see log.h for documentation
 */

// Transmit and receive circular buffers
circbuf_t * transmit;
circbuf_t * receive;

extern uint32_t __RX_BUFFER_START;
extern uint32_t __TX_BUFFER_START;

uint8_t log_timestamp(command_msg * cmd)
{
#ifdef VERBOSE
  // No need for a log item if not verbose
  log_item_t * item;
#endif // VERBOSE

  // Log an item without a payload because the timestamp is built in
  CREATE_ITEM_DATA(item, LOG_ID_INFO, NULL, 0);
  LOG_ITEM(item);

  return SUCCESS;
}

int8_t log_data(uint8_t * bytes, uint8_t length)
{
  // Check for null pointer
  CHECK_NULL(bytes);

  // Loop over string sending bytes
  for (uint8_t i = 0; i < length; i++)
  {
#if defined(CIRCBUF) || defined(CIRCBUF_DMA)
    // Put characters in circular buffer
    if (circbuf_add_item(transmit, *(bytes + i)) != CB_ENUM_NO_ERROR)
    {
      return FAILURE;
    }
#else // CIRCBUF
#ifdef FRDM
    // Send byte over uart for FRDM platform
    uart_send_byte(*(bytes + i));
#else // FRDM
    // Print character to terminal for non-FRDM platforms
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
#if defined(CIRCBUF) || defined(CIRCBUF_DMA)
    // Put characters in circular buffer
    if (circbuf_add_item(transmit, (*str++)) != CB_ENUM_NO_ERROR)
    {
      return FAILURE;
    }
#else // CIRCBUF
#ifdef FRDM
    // Send byte over uart for FRDM platform
    uart_send_byte(*str++);
#else  // FRDM
    // Print character to terminal for non-FRDM platforms
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

#if defined(CIRCBUF) || defined(CIRCBUF_DMA)
#ifdef FRDM
  // Loop until the buffer is empty
  while (circbuf_empty(transmit) != CB_ENUM_EMPTY)
  {
#ifndef UART_INTERRUPTS
    // If uart interrupts aren't being used pull items from buffer and
    // send them using uart
    uint8_t byte = 0;
    circbuf_remove_item(transmit, &byte);
    uart_send_byte(byte);
#else // UART_INTERRUPTS
    ;
#endif // UART_INTERRUPTS
  }

#else // FRDM
  // Loop until the buffer is empty printing characters to the terminal
  while (circbuf_empty(transmit) != CB_ENUM_EMPTY)
  {
    uint8_t byte = 0;
    circbuf_remove_item(transmit, &byte);
    printf("%c", byte);
  }
#endif // FRDM
#endif // CIRCBUF
} // log_flush()

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

#ifdef CIRCBUF_DMA
  // Try to initialize receive buffer
  if (circbuf_init_dma(&receive, CIRC_BUF_SIZE, (uint8_t *)&__RX_BUFFER_START) != CB_ENUM_NO_ERROR)
  {
    return FAILURE;
  }

  // Try to initialize receive buffer
  if (circbuf_init_dma(&transmit, CIRC_BUF_SIZE, (uint8_t *)&__TX_BUFFER_START) != CB_ENUM_NO_ERROR)
  {
    return FAILURE;
  }
#endif

#ifdef PROJECT4
  // Fill out a register struct for incoming commands
  registered_cb reg = {
    .id  = ID_LOGGER,
    .cmd = CMD_GET_TIMESTAMP,
    .cb  = log_timestamp
  };

  // Register callback
  register_cb(&reg);
#endif // PROJECT4

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
