#include "control_lib.h"
#include "MKL25Z4.h"
#include "project_defs.h"
#include "system_controller.h"

uint8_t system_reset(command_msg * cmd)
{
  // Reset System
  NVIC_SystemReset();
  return SUCCESS;
}

void system_control_init()
{
  // Register control function with control lib
  registered_cb reg = {
    .id  = ID_SYSTEM_CONTROLLER,
    .cmd = CMD_SYSTEM_RESET,
    .cb  = system_reset
  };
  register_cb(&reg);
}
