#ifndef __TIMER_LINUX_H__
#define __TIMER_LINUX_H__

#include <stdint.h>
#include <stddef.h>
#include <time.h>

#define START_TIMER start_timer();
#define STOP_TIMER stop_timer();
#define RESET_TIMER reset_timer();
#define GET_TIME get_time();
#define GET_TIME_STAMP time(NULL);

/*
 * \brief timer_init: initialize timer subsystem
 *
 */
void profiler_init_linux();
void start_timer();
void stop_timer();
void reset_timer();
uint32_t get_time();


#endif // __TIMER_H__
