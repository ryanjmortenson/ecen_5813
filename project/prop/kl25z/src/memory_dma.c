#include <stdint.h>
#include "log.h"
#include "MKL25Z4.h"
#include "project_defs.h"
#include "memory_dma.h"
#include "memory.h"

#define MEMMOVE_START(size) DMA_DCR_SINC_MASK | \
                            DMA_DCR_DINC_MASK | \
                            DMA_DCR_SSIZE(size) | \
                            DMA_DCR_DSIZE(size) | \
                            DMA_DCR_AA_MASK   | \
                            DMA_DCR_EINT_MASK | \
                            DMA_DCR_START_MASK

#define MEMSET_START(size) DMA_DCR_DINC_MASK | \
                           DMA_DCR_SSIZE(BYTE) | \
                           DMA_DCR_DSIZE(size) | \
                           DMA_DCR_AA_MASK   | \
                           DMA_DCR_START_MASK

/*
 * Function definitions see memory_dma.h for documentation
 */

extern void DMA0_IRQHandler()
{
  for(volatile uint8_t i = 0; i < 255; i++);
  NVIC_DisableIRQ(DMA0_IRQn);
}

void dma_init()
{
  // Setup the clock to go to the DMA module
  SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

  // Setup the clock to go to the DMAMUX module
  SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

} // dma_init()

uint8_t memmove_dma(uint8_t * src, uint8_t * dst, int32_t length)
{
  // Check for null pointers
  CHECK_NULL(src);
  CHECK_NULL(dst);

  // If src and dst are the same no need for copying
  if (src == dst)
  {
    return SUCCESS;
  }

  // Handle overlap when dst starts in source by using normal memmove
  if (dst > src && dst < src + length)
  {
    for (int32_t i = length - 1; i >= 0; i--)
    {
      *(dst + i) = *(src + i);
    }
  }
  // Handle the case when dst ends in source or dst doesn't overlap
  else
  {
    // Find the number left over bytes to do complete 2 transfers one of
    // width transfers and one of BYTE transfers of the left over bytes
    volatile uint8_t num_left_over_bytes = length % WORD;
    volatile uint32_t num_transfers = length - num_left_over_bytes;

    // Set the source, destination, and number of bytes
    DMA_DSR_BCR0 = num_transfers;
    DMA_SAR0 = (uint32_t) src;
    DMA_DAR0 = (uint32_t) dst;
    NVIC_EnableIRQ(DMA0_IRQn);
    DMA_DCR0 = MEMMOVE_START(WORD);

    // Set the source, destination, and number of bytes
    DMA_DSR_BCR1 = num_left_over_bytes;
    DMA_SAR1 = (uint32_t) src + num_transfers;
    DMA_DAR1 = (uint32_t) dst + num_transfers;
    DMA_DCR1 = MEMMOVE_START(BYTE);

    // Block until complete
    while(!(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK));
    while(!(DMA_DSR_BCR1 & DMA_DSR_BCR_DONE_MASK));
  }

  return SUCCESS;
} // memmove_dma()

uint8_t memset_dma(uint8_t * dst, int32_t length, uint8_t value)
{
  // Check for null pointers
  CHECK_NULL(dst);

  // Find the number left over bytes to do complete 2 transfers one of
  // width transfers and one of BYTE transfers of the left over bytes
  volatile uint8_t num_left_over_bytes = length % WORD;
  volatile uint32_t num_transfers = length - num_left_over_bytes;

  // Set the source, destination, and number of bytes
  DMA_DSR_BCR0 = num_transfers;
  DMA_SAR0 = (uint32_t) &value;
  DMA_DAR0 = (uint32_t) dst;
  NVIC_EnableIRQ(DMA0_IRQn);
  DMA_DCR0 = MEMSET_START(WORD);

  // Set the source, destination, and number of bytes
  DMA_DSR_BCR1 = num_left_over_bytes;
  DMA_SAR1 = (uint32_t) &value;
  DMA_DAR1 = (uint32_t) dst + num_transfers;
  DMA_DCR1 = MEMSET_START(BYTE);

  // Block until complete
  while(!(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK));
  while(!(DMA_DSR_BCR1 & DMA_DSR_BCR_DONE_MASK));

  return SUCCESS;
} // memset_dma()

uint8_t memzero_dma(uint8_t * dst, int32_t length)
{
  return memset_dma(dst, length, 0);
} // memzero_dma()
