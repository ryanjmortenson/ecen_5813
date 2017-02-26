#include <stdint.h>
#include "data.h"
#include "uart.h"
#include "project_defs.h"

#define MAX_INT_LEN (11)

int8_t log_data(uint8_t * bytes, uint8_t length)
{
  // Check for null pointer
  CHECK_NULL(bytes);

  return uart_send_byte_n(bytes, length);
}

int8_t log_string(uint8_t * str)
{
  // Check for null pointer
  CHECK_NULL(str);

  while(*str)
  {
    uart_send_byte(*str++);
  }

  return SUCCESS;
}

int8_t log_integer(uint32_t integer)
{
  int8_t buffer[MAX_INT_LENGTH];

  if(!(my_itoa(buffer, integer, 10)))
  {
    return FAILURE;
  }

  return uart_send_byte_n((uint8_t *)buffer, MAX_INT_LENGTH);
}
