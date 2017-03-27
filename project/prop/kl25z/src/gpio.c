#include "MKL25Z4.h"

// Used to put the transmit/receive into GPIO
#define ALT_2 (2)
#define ALT_1 (1)

void gpio_nrf_init()
{
  // Set the SIM_SCGC5 register PORTD bit to 1 which allows
  // the clock to go to port d
  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

  // Setup ports for CSN and CE on nordic module
  PORTD_PCR0 = PORT_PCR_MUX(ALT_1);
  PORTD_PCR5 = PORT_PCR_MUX(ALT_1);
  GPIOD_PDDR |= 0b000001;
  GPIOD_PDOR |= 0b000001;
}
