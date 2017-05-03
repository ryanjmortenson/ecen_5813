#include "MKL25Z4.h"

// Used to set pins to GPIO setting
#define ALT_1 (1)
#define ALT_3 (3)
#define ALT_4 (4)

void gpio_nrf_init()
{
  // Set the SIM_SCGC5 register PORTD bit to 1 which allows
  // the clock to go to port d
  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

  // Setup ports for CSN and CE on nordic module
  PORTD_PCR0 = PORT_PCR_MUX(ALT_1);
  PORTD_PCR5 = PORT_PCR_MUX(ALT_1);

  // Set initial state to CSN = 1, CE = 0
  GPIOD_PDDR |= 1;
  GPIOD_PDOR |= 1;
}

void gpio_led_pwm_init()
{
  // Set the clock for port b and d
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

  // Set the pin to output of their corresponding TPM
  // channel output for PWM
  PORTB_PCR18 = PORT_PCR_MUX(ALT_3);
  PORTB_PCR19 = PORT_PCR_MUX(ALT_3);
  PORTD_PCR1  = PORT_PCR_MUX(ALT_4);
}
