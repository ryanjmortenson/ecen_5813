#ifndef FRDM
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdint.h>
#include <stdlib.h>

#include "timer_linux.h"

//static uint32_t start;
//static uint32_t end;
struct timespec start;
struct timespec end;

void profiler_init_linux()
{
  reset_timer();
}

void start_timer()
{
  clock_gettime(CLOCK_MONOTONIC, &start);
}

void stop_timer()
{
  clock_gettime(CLOCK_MONOTONIC, &end);
}

void reset_timer()
{
  start.tv_nsec = end.tv_nsec = 0;
}

uint32_t get_time()
{
  return end.tv_nsec - start.tv_nsec;
}
#endif // FRDM
