#ifndef __CONTROL_LIB_H__
#define __CONTROL_LIB_H__

#include <stdint.h>

// Max size of data for command message
#define MAX_DATA_SIZE (32)

// Enum for different commands
typedef enum {
  CMD_ALL = 0x00,
  CMD_GET_TEMP,
  CMD_SET_SPEED,
  CMD_LED_CONFIG,
  CMD_SET_LPM,
  CMD_GET_TIMESTAMP,
  CMD_SYSTEM_RESET
} command;

// Indentifiers for modules that register with control lib
typedef enum {
  ID_TEMP_CONTROLLER = 0x01,
  ID_LED_CONTROLLER,
  ID_SYSTEM_CONTROLLER,
  ID_LOGGER
} indentifier;

// Command structure, this could be made more generic as a void * so modules
// registering with control lib could define their own command structure
typedef struct {
  command cmd;
  uint8_t length;
  uint8_t data[MAX_DATA_SIZE];
  uint16_t checksum;
} command_msg;

// Function pointer for callback
typedef uint8_t (*COMMAND_CB)(command_msg * cmd);

// Structure used for modules to register/unregister a callback for commands
typedef struct {
  indentifier id;
  command cmd;
  COMMAND_CB cb;
} registered_cb;

/*
 * \brief register_cb: registers a callback for system and based on a command
 *
 * \param reg: registration structure
 *
 * \return: success/failure
 *
 */
uint8_t register_cb(registered_cb * reg);

/*
 * \brief unregister_cb: unregisters a callback for system and based on a
 *                       command
 *
 * \param reg: unregistration structure
 *
 * \return: success/failure
 *
 */
uint8_t unregister_cb(registered_cb * reg);

/*
 * \brief distribute_cmd: looks for callbacks registered for the current
 *                        command and calls them
 *
 * \param cmd: command structure
 *
 * \return: success/failure
 *
 */
uint8_t distribute_cmd(command_msg * cmd);


/*
 * \brief control_lib_main: main control lib loop waiting for inputs
 *
 */
void control_lib_main();

#endif // __CONTROL_LIB_H__
