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

/*
 * \brief dma_init: initialize dma subsystem
 *
 */
void dma_init();

void dma_uart_init();
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
uint8_t memmove_dma(uint8_t * src, uint8_t * dst, int32_t length);

/*
 * \brief memset_dma: moves memory with dma system
 *
 * \param dst: pointer to destination
 * \param length: length in bytes
 * \param value: value used to set
 *
 * \return: success or failure
 *
 */
uint8_t memset_dma(uint8_t * dst, int32_t length, uint8_t value);

/*
 * \brief memmove_dma: moves memory with dma system
 *
 * \param dst: pointer to destination
 * \param length: length in bytes
 *
 * \return: success or failure
 *
 */
uint8_t memzero_dma(uint8_t * dst, int32_t length);

#endif // __MEMORY_DMA_H__
