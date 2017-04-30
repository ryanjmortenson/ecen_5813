#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>
#include "MKL25Z4.h"

#define GPIO_NRF_CSN_ENABLE (GPIOD_PDOR &= ~0x01)
#define GPIO_NRF_CSN_DISABLE (GPIOD_PDOR |= 0x01)
#define GPIO_NRF_CE_ENABLE (GPIOD_PDOR &= ~0x20)
#define GPIO_NRF_CE_DISABLE (GPIOD_PDOR |= 0x20)

/*
 * \brief gpio_nrf_init: initializes pins on port d to be csn and ce
 *                       for the nordic module
 *
 */
void gpio_nrf_init();

/*
 * \brief gpio_led_pwm_init: initializes the led
 *
 */
void gpio_led_pwm_init();

#endif
