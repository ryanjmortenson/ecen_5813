#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>

/*
 * \brief my_memmove: used to copy src array to dst array
 *                    does not handle overlap
 *
 * \param src pointer to array
 * \param dst  pointer to array
 * \param length length of array
 * \return pass/fail results
 *
 */
int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length);

/*
 * \brief my_memset: used to set an array with a length to a value
 *
 * \param src pointer to array
 * \param length length of array
 * \param value value to set all of the array to
 * \return pass/fail results
 *
 */
int8_t my_memset(uint8_t * src, uint32_t length, uint8_t value);

/*
 * \brief my_memzero: used to set an array with length to 0
 *
 * \param src pointer to array
 * \param length length of array
 * \return pass/fail results
 *
 */
int8_t my_memzero(uint8_t * src, uint32_t length);

/*
 * \brief my_reverse: used to reverse and array
 *
 * \param src pointer to array
 * \param length length of pointer
 * \return pass/fail results
 *
 */
int8_t my_reverse(uint8_t * src, uint32_t length);

#endif
