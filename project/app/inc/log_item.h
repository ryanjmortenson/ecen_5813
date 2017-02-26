
#ifndef __LOG_ITEM_H__
#define __LOG_ITEM_H__

#include <stdint.h>
#include "log.h"

/*
 * \brief create_log_item: creates a log item
 * \param item: double pointer to log item structure to be initialized
 * \param log_id: enum for log type
 * \param payload: payload to be place in log item
 * \return: success/fail
 *
 */
uint8_t create_log_item(log_item_t ** item, uint8_t log_id, uint8_t * payload, uint8_t length);

/*
 * \brief destroy_log_item: creates a log item
 * \param item: double pointer to log item structure to be destroyed
 * \return: success/fail
 *
 */
uint8_t destroy_log_item(log_item_t * _item);

#endif // __LOG_ITEM_H__
