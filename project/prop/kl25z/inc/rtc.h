#ifndef __RTC_H__
#define __RTC_H__

#include <stdint.h>
#include "MKL25Z4.h"

#define GET_TIME_STAMP RTC_TSR

/*
 * \brief rtc_init: initialize dma subsystem
 *
 */

void rtc_init();

#endif // __RTC_H__
