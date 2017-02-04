#include <stdint.h>
#include <stddef.h>

#define INVALID_PARAM 2
#define NULL_POINTER 1
#define SUCCESS 0

/*
 * \brief Function used to copy src to dst array
 *
 * \param src pointer to array
 * \param dst  pointer to array
 * \param length length of array
 * \return pass/fail results
 *
 */
uint8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length)
{

  // Check to make sure either pointer isn't NULL
  if (src == NULL || dst == NULL)
    return NULL_POINTER;

  // Copy src to dst
  for (int i = 0; i < length; i++)
  {
    *(dst + i) = *(src + i);
  }

  return SUCCESS;
}

/*
 * \brief Function used to set array to a value
 *
 * \param src pointer to array
 * \param length length of array
 * \param value value to set all of the array to
 * \return pass/fail results
 *
 */
uint8_t my_memset(uint8_t *src, uint32_t length, uint8_t value)
{

  // Check to make sure either pointer isn't NULL
  if (src == NULL)
    return NULL_POINTER;

  // Copy value to src
  for (int i = 0; i < length; i++)
  {
    *(src + i) = value;
  }

  return SUCCESS;
}

/*
 * \brief Function used to set array to 0
 *
 * \param src pointer to array
 * \param length length of array
 * \return pass/fail results
 *
 */
uint8_t my_memzero(uint8_t *src, uint32_t length)
{
  // Call memset with 0 as value
  return my_memset(src, length, 0);
}

/*
 * \brief Function used to reverse and array
 *
 * \param src pointer to array
 * \param length length of pointer
 * \return pass/fail results
 *
 */
uint8_t my_reverse(uint8_t *src, uint32_t length)
{
  uint8_t temp;
  uint32_t middle = length >> 1;
  uint32_t end = length - 1;

  // Check to make sure the pointer isn't 0
  if (src == NULL)
    return NULL_POINTER;

  // Reverse array by swapping elements around a center point
  for (int i = 0; i < middle; i++)
  {
    temp = *(src + end - i);
    *(src + end - i) = *(src + i);
    *(src + i) = temp;
  }

  return SUCCESS;
}
