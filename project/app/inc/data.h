#ifndef __DATA_H__
#define __DATA_H__

#include <stdint.h>
#include "circbuf.h"

#define BASE_10 (10)

// Struct to hold results from analysis
typedef struct analysis
{
  uint32_t alpha;
  uint32_t num;
  uint32_t punc;
  uint32_t misc;
} analysis_t;

/*
 * \brief my_itoa: used to convert an integer to a string
 *
 * \param str pointer to array to place string into
 * \param data data to be converted to string
 * \param base base of integer when converted to string (2-36 for base)
 * \return pointer to input param str
 *
 */
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base);

/*
 * \brief my_atoi: used to convert an ASCII character sequence into an integer
 *
 * \param str pointer to string for conversion
 * \return fail result or pointer to converted string
 *
 */
int32_t my_atoi(int8_t * str);

/*
 * \brief big_to_little32: used to convert an array from big endian to little endian
 *
 * \param data pointer to data for conversion from big endian to little endian
 * \param length length of data to convert
 * \return converted integer or failure
 *
 */
int8_t big_to_little32(uint32_t * data, uint32_t length);

/*
 * \brief little_to_big32: used to convert an array from little endian to big endian
 *
 * \param data pointer to data for conversion from little endian to big endian
 * \param length length of data to convert
 * \return pass/fail
 *
 */
int8_t little_to_big32(uint32_t * data, uint32_t length);

/*
 * \brief print_memory: used to print memory in hex format
 *
 * \param start pointer to first element of memory to print
 * \param length length of data to convert
 *
 */
void print_memory(uint8_t * start, uint32_t length);

uint8_t analyze_bytes(uint8_t * buf, analysis_t * results, uint8_t num_bytes);
#endif
