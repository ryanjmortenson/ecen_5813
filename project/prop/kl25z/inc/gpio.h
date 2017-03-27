#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>
#include "MKL25Z4.h"

#define GPIO_NRF_CSN_ENABLE (GPIOD_PDOR &= ~0x01)
#define GPIO_NRF_CSN_DISABLE (GPIOD_PDOR |= 0x01)
#define GPIO_NRF_CE_ENABLE (GPIOD_PDOR &= ~0x20)
#define GPIO_NRF_CE_DISABLE (GPIOD_PDOR |= 0x20)

/*
 * \brief uart_configure: configures uart for baud rate
 *
 * \param baud baud rate for uart communications
 *
 */
void gpio_nrf_init();

#endif
