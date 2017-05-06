#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>
#include "MKL25Z4.h"

extern volatile uint8_t overflows;
#define START_TIMER  TPM0_SC |= TPM_SC_CMOD(1);
#define STOP_TIMER TPM0_SC &= ~TPM_SC_CMOD(1);
#define RESET_TIMER TPM0_CNT = 0; overflows = 0;
#define GET_TIME (overflows * 65535 + TPM0_CNT) * 48
#define EDGE_ALIGNED_PWM_ON TPM_CnSC_ELSB(1) | \
                            TPM_CnSC_ELSB(0) | \
                            TPM_CnSC_MSB(1)  | \
                            TPM_CnSC_MSA(0)


/*
 * \brief profiler_init: initialize timer subsystem
 *
 */
void profiler_init();

/*
 * \brief tpm_led_pwm_init: initialize tpm for pwm driving led
 *
 */
void tpm_led_pwm_init();

#endif // __TIMER_H__
