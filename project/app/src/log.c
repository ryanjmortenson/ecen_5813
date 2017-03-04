#include <stdint.h>
#include <stdio.h>
#include "data.h"
#include "log.h"
#include "project_defs.h"

/*
 * Function definitions see log.h for documentation
 */

int8_t log_data(uint8_t * bytes, uint8_t length)
{
  // Check for null pointer
  CHECK_NULL(bytes);

  // Loop over bytes displaying them in hex
  printf(DATA_STRING);
  for (uint8_t i = 0; i < length; i++)
  {
    printf("%s%02x ", HEX_START, *bytes++);
  }
  printf("\n");

  return SUCCESS;
} // log_data()

int8_t log_string(int8_t * str)
{
  // Check for null pointer
  CHECK_NULL(str);

  // Use printf to print string
  printf("%s", str);

  return SUCCESS;
} // log_string()

int8_t log_integer(int32_t integer)
{
  // Createa a buffer to hold the interger
  int8_t buffer[MAX_INT_LEN];

  // Convert integer to string in base 10
  if(!(my_itoa(buffer, integer, BASE_10)))
  {
    return FAILURE;
  }

  // Print create buffer
  printf("%s%s\n", INT_STRING, buffer);

  // Log the string
  return SUCCESS;
} // log_integer()

void log_flush()
{
  // Currently just a stub
} // log_flush()

uint8_t log_item(log_item_t * item)
{
  // Check for null pointer
  CHECK_NULL(item);

  // Print the items in the structure
  printf("log_id: %d\n", item->log_id);
  printf("log_length: %d\n", item->log_length);
  printf("payload: ");
  for (uint8_t i = 0; i < item->log_length; i++)
  {
    printf("%s%02x ", HEX_START, *(item->payload + i));
  }
  printf("\n");

  return SUCCESS;
} // log_item()
