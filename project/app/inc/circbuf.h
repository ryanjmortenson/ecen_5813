#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

#include <stdint.h>

// Check for null pointer
#define CB_CHECK_NULL(x) if (x == NULL) {return CB_ENUM_NULL_POINTER;}

// Status enum for circular buffer functions
typedef enum cb_enum
{
  CB_ENUM_NO_ERROR,
  CB_ENUM_FULL,
  CB_ENUM_EMPTY,
  CB_ENUM_NULL_POINTER,
  CB_ENUM_NO_LENGTH,
  CB_ENUM_ALLOC_FAILURE,
  CB_ENUM_FAILURE,
  CB_ENUM_BAD_INDEX
} cb_enum_t;

// Keep struct members private
typedef struct circbuf circbuf_t;

/*
 * \brief circ_buf_init: Initialize circular buffer with a length this will
 *                       call malloc to put the buffer and the structure
 *                       on the heap
 *
 * \param buf: pointer to a pointer for the circular buffer structure
 * \param length: length of the circular buffer
 * \return: success or error
 *
 */
cb_enum_t circ_buf_init(circbuf_t ** buf, uint8_t length);

/*
 * \brief circ_buf_destroy: calls free on the buffer and the structure
 *
 * \param buf: pointer to a pointer for the circular buffer structure
 * \return: success or error
 *
 */
cb_enum_t circ_buf_destroy(circbuf_t * buf);

/*
 * \brief circ_buf_add_item: adds and item to the head pointer and increments
 *                           head
 *
 * \param buf: pointer to a pointer for the circular buffer structure
 * \param payload: payload to be added to circular buffer
 * \return: success or error
 *
 */
cb_enum_t circ_buf_add_item(circbuf_t * buf, uint8_t payload);

/*
 * \brief circ_buf_remove_item: removes and item from tail and in payload
 *
 * \param buf: pointer to a pointer for the circular buffer structure
 * \param payload: memory location where removed item will be placed
 * \return: success or error
 *
 */
cb_enum_t circ_buf_remove_item(circbuf_t * buf, uint8_t * payload);

/*
 * \brief circ_buf_full: checks if buffer is full
 *
 * \param buf: pointer to a pointer for the circular buffer structure
 * \return: success if full or error if not full
 *
 */
cb_enum_t circ_buf_full(circbuf_t * buf);

/*
 * \brief circ_buf_empty: checks if buffer is empty
 *
 * \param buf: pointer to a pointer for the circular buffer structure
 * \return: success if empty or error if not empty
 *
 */
cb_enum_t circ_buf_empty(circbuf_t * buf);

/*
 * \brief circ_buf_peak: gets the index item from tail
 *
 * \param buf: pointer to a pointer for the circular buffer structure
 * \param index: index from tail to get payload from
 * \param payload: memory location to place item
 * \return: success if empty or error if not empty
 *
 */
cb_enum_t circ_buf_peak(circbuf_t * buf, uint32_t index, uint8_t * payload);

#endif // __CIRCBUF_H__