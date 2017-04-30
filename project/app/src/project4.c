#include "project4.h"
#include "project_defs.h"
#include "control_lib.h"
#include "circbuf.h"
#include "log_item.h"

#ifdef FRDM
#include "rtc.h"
#include "gpio.h"
#include "timer.h"
#include "led_controller.h"
#include "system_controller.h"
#endif // FRDM

extern circbuf_t * receive;
extern circbuf_t * transmit;

#ifdef VERBOSE
  // No need for a log item if not verbose
  static log_item_t * item;
#endif // VERBOSE

uint8_t project_4_setup()
{
#ifdef FRDM
  // Setup the rtc for logging timestamps
  rtc_init();

  // Setup the LED controller
  led_control_init();

  // System controller init (reset)
  system_control_init();
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

  // Loop waiting for commands
  control_lib_main();

  return SUCCESS;
}
