#ifndef __PROJECT_THREE_H__
#define __PROJECT_THREE_H__

#include <stdint.h>

/*
 * \brief project_3_spi: prepares system for project 3 execution
 * \return: SUCCESS\FAILURE
 */
uint8_t project_3_setup();

/*
 * \brief project_3_spi: executes required spi functionality
 *
 */
void project_3_spi();

/*
 * \brief project_3_profiler: executes required profiler functionality
 *
 */
void project_3_profiler();

#endif // __PROJECT_THREE_H__
