#include <stdint.h>
#include "log.h"
#include "MKL25Z4.h"
#include "project_defs.h"
#include "timer.h"

#define MCGFLLCLK (1)
#define PRESCALER_8 (3)
/*
 * Function definitions see timer.h for documentation
 */

// Used to keep track of timer overflows register is only a uint16_t
volatile uint8_t overflows = 0;

extern void TPM0_IRQHandler()
{
  // Keep track of overflows
  overflows++;

  // Clear timer overflow flag
  TPM0_SC |= TPM_SC_TOF_MASK;
}

void profiler_init()
{
  // Allow clock to go to TIMER0
  SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;

  // Reset the SIM_SOPT2 register TPMSRC bits to 0
  SIM_SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;

  // Set the SIM_SOPT2 register TPMSRC bits to 10 which MCGFLLCLK
  SIM_SOPT2 |= SIM_SOPT2_TPMSRC(MCGFLLCLK);

  // Set the counter to 0
  TPM0_CNT = 0;

  // Turn on debug mode so the timer will run while debugging
  TPM0_CONF = TPM_CONF_DBGMODE(3);

  TPM0_SC = TPM_SC_PS(0) | TPM_SC_TOIE_MASK;

  NVIC_EnableIRQ(TPM0_IRQn);
} // timer_init()

void tpm_led_pwm_init()
{
  // Allow clock to go to TIMER0 and TIMER2
  SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK;

  // Reset the SIM_SOPT2 register TPMSRC bits to 0
  SIM_SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;

  // Set the SIM_SOPT2 register TPMSRC bits to 10 which MCGFLLCLK
  SIM_SOPT2 |= SIM_SOPT2_TPMSRC(MCGFLLCLK);

  // Set the counters to 0
  TPM0_CNT = TPM2_CNT = 0;

  // Turn on debug mode so the timer will run while debugging
  TPM0_CONF = TPM2_CONF = TPM_CONF_DBGMODE(3);

  // Use the selected prescaler
  TPM0_SC = TPM2_SC = TPM_SC_PS(PRESCALER_8);

  // Turn on TPM module
  TPM2_SC |= TPM_SC_CMOD(1);
  TPM0_SC |= TPM_SC_CMOD(1);
}
