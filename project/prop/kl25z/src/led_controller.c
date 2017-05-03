#include "control_lib.h"
#include "gpio.h"
#include "MKL25Z4.h"
#include "project_defs.h"
#include "log_item.h"
#include "timer.h"

// Set the data direction to output for the led pins
#define R_ON TPM2_C0SC |= EDGE_ALIGNED_PWM_ON;
#define G_ON TPM2_C1SC |= EDGE_ALIGNED_PWM_ON;
#define B_ON TPM0_C1SC |= EDGE_ALIGNED_PWM_ON;
#define R_OFF TPM2_C0SC = 0;
#define G_OFF TPM2_C1SC = 0;
#define B_OFF TPM0_C1SC = 0;
#define R_STATE(data) (((*(uint8_t *) data) & 0x4) >> 2)
#define G_STATE(data) (((*(uint8_t *) data) & 0x2) >> 1)
#define B_STATE(data) ((*(uint8_t *) data) & 0x1)
#define R_CNT(data) (uint16_t)((*(data + 1) << 8) | (*(data + 2)))
#define G_CNT(data) (uint16_t)((*(data + 3) << 8) | (*(data + 4)))
#define B_CNT(data) (uint16_t)((*(data + 5) << 8) | (*(data + 6)))
#define R_CNT_REG (TPM2_C0V)
#define G_CNT_REG (TPM2_C1V)
#define B_CNT_REG (TPM0_C1V)
#define ON (1)

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

  // Turn RED portion of LED on/off
  if (R_STATE(cmd->data) == ON)
  {
    R_ON;
  }
  else
  {
    R_OFF;
  }

  // Turn GREEN portion of LED on/off
  if (G_STATE(cmd->data) == ON)
  {
    G_ON;
  }
  else
  {
    G_OFF;
  }

  // Turn BLUE portion of LED on/off
  if (B_STATE(cmd->data) == ON)
  {
    B_ON;
  }
  else
  {
    B_OFF;
  }

  return SUCCESS;
}

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
}
