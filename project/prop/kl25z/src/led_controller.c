#include "control_lib.h"
#include "gpio.h"
#include "MKL25Z4.h"
#include "project_defs.h"
#include "log_item.h"
#include "timer.h"

#define R_STATE(data) (((*(uint8_t *) data) & 0x4) >> 2)
#define G_STATE(data) (((*(uint8_t *) data) & 0x2) >> 1)
#define B_STATE(data) ((*(uint8_t *) data) & 0x1)
#define R_CNT(data) (uint16_t)((*(data + 1) << 8) | (*(data + 2)))
#define G_CNT(data) (uint16_t)((*(data + 3) << 8) | (*(data + 4)))
#define B_CNT(data) (uint16_t)((*(data + 5) << 8) | (*(data + 6)))
#define R_CNT_REG (TPM2_C0V)
#define G_CNT_REG (TPM2_C1V)
#define B_CNT_REG (TPM0_C1V)
#define R_TPM_REG (TPM2_C0SC)
#define G_TPM_REG (TPM2_C1SC)
#define B_TPM_REG (TPM0_C1SC)

// Array of states for LED on/off
static const uint8_t state[] = {0, EDGE_ALIGNED_PWM_ON};

/*
 * \brief led_control: callback registered for led control command
 *
 * \param cmd: command structure
 *
 * \return: success/failure
 *
 */
uint8_t led_control(command_msg * cmd)
{
  // Set the counts for the PWM (0-65536)
  R_CNT_REG = R_CNT(cmd->data);
  G_CNT_REG = G_CNT(cmd->data);
  B_CNT_REG = B_CNT(cmd->data);

  // Set the correct register state
  R_TPM_REG = state[R_STATE(cmd->data)];
  G_TPM_REG = state[G_STATE(cmd->data)];
  B_TPM_REG = state[B_STATE(cmd->data)];

  return SUCCESS;
} // led_control()

void led_control_init()
{
  // Initialize the GPIO for pins going to LED
  gpio_led_pwm_init();

  // Initialize the TPM module to use PWM features for controlling led
  // color and brigtness
  tpm_led_pwm_init();

  // Register control function with control lib
  registered_cb reg = {
    .id = ID_LED_CONTROLLER,
    .cmd = CMD_LED_CONFIG,
    .cb = led_control
  };
  register_cb(&reg);
} // led_control_init()
