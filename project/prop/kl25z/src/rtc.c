#include <stdint.h>
#include "MKL25Z4.h"
#include "log_item.h"
#include "project_defs.h"

/*
 * Function definitions see rtc.h for documentation
 */

#ifdef VERBOSE
  // No need for a log item if not verbose
  log_item_t * item;
  char * heart_beat_strings[] =
  {
    "Owner of a lonely heart",
    "Much better than the",
    "Owner of a broken heart"
  };
#endif // VERBOSE

extern void RTC_Seconds_IRQHandler()
{
  uint8_t modulo = RTC_TSR % 3;
  CREATE_ITEM_STRING(item, LOG_ID_HEARTBEAT, heart_beat_strings[modulo]);
  LOG_ITEM(item);
}

void rtc_init()
{

  MCG_C1 |= MCG_C1_IRCLKEN_MASK;
  MCG_C2 &= ~(MCG_C2_IRCS_MASK);
  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
  PORTC_PCR1 |= (PORT_PCR_MUX(0x1));
  SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);
  SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100);
  PORTC_PCR3 |= (PORT_PCR_MUX(0x5));
  // Turn on access and interrupts
  SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

  // Do a software reset to clear registers
  RTC_CR |= RTC_CR_SWR_MASK;
  RTC_CR &= ~RTC_CR_SWR_MASK;

  // Set the seconds register to the timestamp
  RTC_TSR = TIMESTAMP;

  // Enable the IRQ for the RTC seconds
  NVIC_EnableIRQ(RTC_Seconds_IRQn);

  // Clear all interrupts then set the timer seconds interrupt
  RTC_IER = 0;
  RTC_IER |= RTC_IER_TSIE_MASK;

  // Start the RTC
  RTC_SR |= RTC_SR_TCE_MASK;

} // rtc_init()
