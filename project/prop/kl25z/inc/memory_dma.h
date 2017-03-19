#ifndef __MEMORY_DMA_H__
#define __MEMORY_DMA_H__

#include <stdint.h>
#include "MKL25Z4.h"

typedef enum
{
  BYTE = 1,
  HALF_WORD = 2,
  WORD = 4
} dma_width_t;

typedef enum
{
  WORD_SETTING = 0,
  BYTE_SETTING = 1,
  HALF_WORD_SETTING = 2
} dma_width_setting_t;

/*
 * \brief dma_init: initialize dma subsystem
 *
 */
void dma_init();

/*
 * \brief memmove_dma: moves memory with dma system
 *
 * \param src: pointer to source
 * \param dst: pointer to destination
 * \param length: length in bytes
 * \param width: width of an individual unit of transfer can be 1, 2, or 4 bytes
 *
 * \return: success or failure
 *
 */
uint8_t memmove_dma(uint8_t * src, uint8_t * dst, int32_t length, dma_width_t width);

#endif // __MEMORY_DMA_H__
