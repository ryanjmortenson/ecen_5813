#ifndef __PROJECT_FIVE_H__
#define __PROJECT_FIVE_H__

#include <stdint.h>

/*
 * \brief project_5_spi: prepares system for project 5 execution
 * \return: SUCCESS\FAILURE
 */
uint8_t project_5_setup();

/*
 * \brief project_5_wireless_comms: executes wireless comms between BBB and
 *                                  FRDM board
 *
 */
void project_5_wireless_comms();


#endif // __PROJECT_FIVE_H__
