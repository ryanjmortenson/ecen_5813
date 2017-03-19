#include <stdint.h>
#include "log.h"
#include "MKL25Z4.h"
#include "project_defs.h"
#include "memory_dma.h"

#define DMA_START(size) DMA_DCR_SINC_MASK | \
                        DMA_DCR_DINC_MASK | \
                        DMA_DCR_SSIZE(size) | \
                        DMA_DCR_DSIZE(size) | \
                        DMA_DCR_START_MASK


/*
 * Function definitions see memory.h for documentation
 */

void dma_init()
{
  // Setup the clock to go to the DMA module
  SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

  // Setup the clock to go to the DMAMUX module
  SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

} // dma_init()

uint8_t memmove_dma(uint8_t * src, uint8_t * dst, int32_t length, dma_width_t width)
{
  // Check for null pointers
  CHECK_NULL(src);
  CHECK_NULL(dst);
  dma_width_setting_t setting;

  // Check to make sure the width is is accetable
  if (width == BYTE)
  {
    setting = BYTE_SETTING;
  }
  else if (width == HALF_WORD)
  {
    setting = HALF_WORD_SETTING;
  }
  else if (width == WORD)
  {
    setting = WORD_SETTING;
  }
  else
  {
    return INVALID_PARAM;
  }

  // Find the number left over bytes to do complete 2 transfers one of
  // width transfers and one of BYTE transfers of the left over bytes
  volatile uint8_t num_left_over_bytes = length % width;
  volatile uint32_t num_transfers = length - num_left_over_bytes;

  // If src and dst are the same no need for copying
  if (src == dst)
  {
    return SUCCESS;
  }

  // Handle overlap when dst starts in source
  if (dst > src && dst < src + length)
  {
    return FAILURE;
  }
  // Handle the case when dst ends in source or dst doesn't overlap
  else
  {
    // Set the number of transfers

    // Set the source, destination, and number of bytes
    DMA_DSR_BCR0 = num_transfers;
    DMA_SAR0 = (uint32_t) src;
    DMA_DAR0 = (uint32_t) dst;

    // Set the source, destination, and number of bytes
    DMA_DSR_BCR1 = num_left_over_bytes;
    DMA_SAR1 = (uint32_t) (src + num_transfers)
    DMA_DAR1 = (uint32_t) (dst + num_transfers);

    // Start the transfer
    DMA_DCR0 = DMA_START((uint8_t) setting);
    DMA_DCR1 = DMA_START((uint8_t) BYTE);

    // Block until complete
    while(!(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK));
    while(!(DMA_DSR_BCR1 & DMA_DSR_BCR_DONE_MASK));
  }

  return SUCCESS;
} // my_memmove()
