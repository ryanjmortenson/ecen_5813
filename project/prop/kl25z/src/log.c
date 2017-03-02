#include <stdint.h>
#include "circbuf.h"
#include "data.h"
#include "log.h"
#include "uart.h"
#include "project_defs.h"

#define BASE_16 (16)
#define MAX_HEX_BYTE_LEN (3)

/*
 * Function definitions see log.h for documentation
 */

extern circbuf_t * transmit;

int8_t log_data(uint8_t * bytes, uint8_t length)
{
  // Createa a buffer to hold the integer
  int8_t buffer[MAX_HEX_BYTE_LEN];

  // Check for null pointer
  CHECK_NULL(bytes);

  // Log bytes
  log_string((int8_t *)DATA_STRING);
  for (uint8_t i = 0; i < length; i++)
  {
    log_string((int8_t *)HEX_START);
    if(!(my_itoa(buffer, *bytes++, BASE_16)))
    {
      return FAILURE;
    }
    log_string((int8_t *)buffer);
    log_string((int8_t *)SPACE);
  }
  log_string((int8_t *)"\n");

  return SUCCESS;
} // log_data()

int8_t log_string(int8_t * str)
{
  // Check for null pointer
  CHECK_NULL(str);

  // Loop over string sending bytes
  while(*str)
  {
    circbuf_add_item(transmit, (*str++));
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

  log_string((int8_t *)buffer);

  return SUCCESS;
} // log_integer()

void log_flush()
{
  while(circbuf_empty(transmit) != CB_ENUM_NO_ERROR);
} // log_flush()

uint8_t log_item(log_item_t * item)
{
  return SUCCESS;
} // log_item()
