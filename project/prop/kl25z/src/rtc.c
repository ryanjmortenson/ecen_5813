#include <stdint.h>
#include "MKL25Z4.h"
#include "log_item.h"
#include "project_defs.h"

/*
 * Function definitions see rtc.h for documentation
 */

#ifdef VERBOSE
  // No need for a log item if not verbose
  static log_item_t * item;
#endif // VERBOSE

// Used to set pins to GPIO setting
#define ALT_1 (1)
#define ALT_5 (5)
#define RTC_CLKIN (2)
#define MCGIRCLK (4)

extern void RTC_Seconds_IRQHandler()
{
  CREATE_ITEM_STRING(item, LOG_ID_HEARTBEAT, "HEARTBEAT");
  LOG_ITEM(item);
}

void rtc_init()
{
  // Turn on internal reference clock
  MCG_C1 |= MCG_C1_IRCLKEN_MASK;

  // Select slow internal reference clock
  MCG_C2 &= ~(MCG_C2_IRCS_MASK);

  // Allow clocks to go to port c
  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

  // Set pin C1 to alt 1 for gpio
  PORTC_PCR1 |= (PORT_PCR_MUX(ALT_1));

  // Select RTC clock in for 32kHz oscillator
  SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(RTC_CLKIN);

  // Select the clock out on pin C5 as internal reference clock
  SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(MCGIRCLK);

  // Set pin C5 to clock out
  PORTC_PCR3 |= (PORT_PCR_MUX(ALT_5));

  // Turn on access and interrupts
  SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

  // Do a software reset to clear registers
  RTC_CR |= RTC_CR_SWR_MASK;
  RTC_CR &= ~RTC_CR_SWR_MASK;

  // Set the seconds register to the timestamp
  RTC_TSR = TIMESTAMP;

  // Enable the IRQ for the RTC seconds
  NVIC_EnableIRQ(RTC_Seconds_IRQn);

  // Set the priority lower than UART to allow interruption by UART
  // for printing the heartbeat
  NVIC_SetPriority(RTC_Seconds_IRQn, 10);

  // Clear all interrupts then set the timer seconds interrupt
  RTC_IER = 0;
  RTC_IER |= RTC_IER_TSIE_MASK;

  // Start the RTC
  RTC_SR |= RTC_SR_TCE_MASK;

} // rtc_init()
