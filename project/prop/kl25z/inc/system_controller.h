#ifndef __SYSTEM_CONTROLLER_H__
#define __SYSTEM_CONTROLLER_H__

#include <stdint.h>
#include "MKL25Z4.h"


/*
 * \brief system_reset: callback registered for system reset command
 *
 * \param cmd: command structure
 *
 * \return: success/failure
 *
 */
uint8_t system_reset(command_msg * cmd);

/*
 * \brief control_lib_main: registers system reset callback
 *
 */
void system_control_init();

#endif
