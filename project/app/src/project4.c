#include "project4.h"
#include "project_defs.h"
#include "control_lib.h"
#include "circbuf.h"
#include "log_item.h"

#ifdef FRDM
#include "rtc.h"
#endif // FRDM






// TODO: REMOVE ALL THIS!!!!!
#include "data.h"

#ifdef VERBOSE
  // No need for a log item if not verbose
  static log_item_t * item;
#endif // VERBOSE

uint8_t test_cb (command_msg * cmd)
{
  // Send log system initialized
  int8_t itoa_buffer[16] = {0};
  my_itoa(itoa_buffer, cmd->cmd, BASE_10);
  CREATE_ITEM_STRING(item, LOG_ID_INFO, itoa_buffer);
  LOG_ITEM(item);

  return SUCCESS;
}

extern circbuf_t * receive;
extern circbuf_t * transmit;

uint8_t project_4_setup()
{
#ifdef FRDM
  // Setup the rtc for logging timestamps
  rtc_init();
#endif // FRDM

  // Init log and bail out if a failure occurs
  if (log_init())
  {
    return FAILURE;
  }

  // Send log system initialized
  CREATE_ITEM_STRING(item, LOG_ID_LOGGER_INITIALIZED, "");
  LOG_ITEM(item);

  // Indicate logger initialized
  CREATE_ITEM_STRING(item, LOG_ID_SYSTEM_INITIALIZED, "");
  LOG_ITEM(item);

  registered_cb reg = {
    .id = ID_LED_CONTROLLER,
    .cmd = CMD_ALL,
    .cb = test_cb
  };
  register_cb(&reg);

  reg.id  = ID_TEMP_CONTROLLER,
  reg.cmd = CMD_GET_TEMP,
  reg.cb  = test_cb;
  register_cb(&reg);

  reg.id  = ID_SPEED_CONTROLLER,
  reg.cmd = CMD_SET_SPEED,
  reg.cb  = test_cb;
  register_cb(&reg);

  circbuf_add_item(receive, CMD_GET_TEMP);
  circbuf_add_item(receive, 0);
  circbuf_add_item(receive, 0);
  circbuf_add_item(receive, 0);

  circbuf_add_item(receive, CMD_GET_TIMESTAMP);
  circbuf_add_item(receive, 0);
  circbuf_add_item(receive, 0);
  circbuf_add_item(receive, 0);

  control_lib_main();

  return SUCCESS;
}

