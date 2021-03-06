#include "control_lib.h"
#include "circbuf.h"
#include "project_defs.h"
#include "data.h"
#include "memory.h"

// Maximum number of registered callbacks
#define MAX_REGS (32)

static registered_cb regs[MAX_REGS];
static uint8_t current_cbs = 0;
extern circbuf_t * receive;

uint8_t register_cb(registered_cb * reg_cb)
{
  // TODO: For a multithreaded environment this should be made atomic
  // Check for null pointer
  CHECK_NULL(reg_cb);

  // Don't register another functionality if out of space
  if (current_cbs >= MAX_REGS - 1)
  {
    return FAILURE;
  }

  // Register functionality
  *(regs + current_cbs) = *(reg_cb);
  current_cbs++;
  return SUCCESS;
} // register_cb()

uint8_t unregister_cb(registered_cb * reg_cb)
{
  // TODO: For a multithreaded environment this should be made atomic
  // Check for null pointer
  CHECK_NULL(reg_cb);

  // Loop over registered callbacks looking for a match to remove.  When
  // a match is found shift all registered cbs 1 index lower
  for (uint8_t i = 0; i < current_cbs; i++)
  {
    if (reg_cb->id == (regs + i)->id && reg_cb->cmd == (regs + i)->cmd)
    {
      for (uint8_t k = i; k < current_cbs; k++)
      {
        *(regs + k) = *(regs + k + 1);
      }
      current_cbs--;
      return SUCCESS;
    }
  }
  return FAILURE;
} // unregister_cb()

uint8_t distribute_cmd(command_msg * cmd)
{
  // Loop over registered callbacks looking for command ids that match.
  // When a match occurs call the callback.  A failure in a callback
  // stops the search and returns a failure
  for (uint8_t i = 0; i < current_cbs; i++)
  {
    if ((regs + i)->cmd == cmd->cmd)
    {
      if ((regs + i)->cb(cmd) != SUCCESS)
      {
        return FAILURE;
      }
    }
  }
  return SUCCESS;
} // distribute_cmd()

void control_lib_main()
{
  uint8_t byte = 0;
  command_msg cmd;
  uint16_t checksum = 0;

  for(;;)
  {
    // Clear out cmd structure
    my_memset((uint8_t *)&cmd, sizeof(cmd), 0);

    // Receive 1 byte for the cmd enum
    while(circbuf_remove_item(receive, (uint8_t *)&(cmd.cmd)) != CB_ENUM_NO_ERROR);

    // Receive 1 byte for the data length
    while(circbuf_remove_item(receive, &(cmd.length)) != CB_ENUM_NO_ERROR);

    // Wait for all bytes to be received for the data
    while(circbuf_peek(receive, cmd.length, &byte) != CB_ENUM_NO_ERROR);

    // Copy all the bytes into the command struct
    for (uint8_t i = 0; i < cmd.length; i++)
    {
      circbuf_remove_item(receive, &byte);
      *(cmd.data + i) = byte;
    }

    // Wait for all bytes to be received for the data, byte will have the
    // high byte
    while(circbuf_remove_item(receive, &byte) != CB_ENUM_NO_ERROR);

    // Get the low byte and place in checksum
    while(circbuf_remove_item(receive, (uint8_t *)&cmd.checksum));

    // Compute the full 16 bit value by shifting the high byte 8 and oring
    // with checksum
    cmd.checksum |= (byte << 8);

    // Calculate super simple additive checksum
    for (uint8_t i = 0; i < cmd.length; i++)
    {
      checksum += (*(cmd.data + i) & 0xffff);
    }

    // Only execute command if checksum is correct
    if (checksum == cmd.checksum)
    {
      distribute_cmd(&cmd);
    }

    // Reset checksum
    checksum = 0;
  }
}  // control_lib_main()
