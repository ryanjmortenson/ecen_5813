#ifndef __LOG_ITEM_H__
#define __LOG_ITEM_H__

#include <stdint.h>
#include "log.h"

#define LOG_ITEM_STRING (-1)

// Enum of log ids used in log item structure
typedef enum log_id
{
	LOG_ID_LOGGER_INITIALIZED,
	LOG_ID_GPIO_INITIALZED,
	LOG_ID_SYSTEM_INITIALIZED,
	LOG_ID_SYSTEM_HALTED,
	LOG_ID_INFO,
	LOG_ID_WARNING,
	LOG_ID_ERROR,
	LOG_ID_DATA_RECEIVED,
	LOG_ID_DATA_ANALYSIS_STARTED,
	LOG_ID_DATA_ALPHA_COUNT,
	LOG_ID_DATA_NUMERIC_COUNT,
	LOG_ID_DATA_PUNCTUATION_COUNT,
	LOG_ID_DATA_MISC_COUNT,
	LOG_ID_DATA_ANALYSIS_COMPLETED
} log_id_t;

// Mapping from log id to string for pretty printing
extern char * log_id_str[];

/*
 * \brief log_item_t: structure for log items
 * \param log_id: type of log in structure
 * \param log_length: length of log payload
 * \param payload: payload of log
 *
 */
typedef struct log_item_struct
{
  log_id_t log_id;
  uint8_t log_length;
  uint8_t * payload;
} log_item_t;

/*
 * \brief create_log_item: creates a log item
 * \param item: double pointer to log item structure to be initialized
 * \param log_id: enum for log type
 * \param payload: payload to be place in log item
 * \return: success/fail
 *
 */
uint8_t create_log_item(log_item_t ** item, log_id_t log_id, uint8_t * payload, int16_t length);

/*
 * \brief destroy_log_item: creates a log item
 * \param item: double pointer to log item structure to be destroyed
 * \return: success/fail
 *
 */
uint8_t destroy_log_item(log_item_t * _item);

/*
 * \brief log_item: creates a log item
 * \param log_item: double pointer to log item structure to be destroyed
 * \return: success/fail
 *
 */
uint8_t log_item(log_item_t * item);

#endif // __LOG_ITEM_H__
