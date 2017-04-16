#include <stdint.h>
#include "circbuf.h"
#include "log.h"
#include "MKL25Z4.h"
#include "project_defs.h"
#include "memory_dma.h"
#include "memory.h"

// Starts the memmove with the following parameters
#define MEMMOVE_START(size) DMA_DCR_SINC_MASK | \
                            DMA_DCR_DINC_MASK | \
                            DMA_DCR_SSIZE(size) | \
                            DMA_DCR_DSIZE(size) | \
                            DMA_DCR_AA_MASK   | \
                            DMA_DCR_EINT_MASK | \
                            DMA_DCR_START_MASK;

// Starts the memset with the following parameters
#define MEMSET_START(size) DMA_DCR_DINC_MASK | \
                           DMA_DCR_SSIZE(BYTE) | \
                           DMA_DCR_DSIZE(size) | \
                           DMA_DCR_EINT_MASK | \
                           DMA_DCR_START_MASK;

// Set DMA_SIZE
#ifndef DMA_SIZE
#define DMA_SIZE 4
#endif

// Validate the DMA_SIZE for transfer, couldn't seem to get || or != to
// work correctly in 1 statement
#if DMA_SIZE == 4
#elif DMA_SIZE == 2
#elif DMA_SIZE == 1
#else
#error Incorrect DMA_SIZE must be 1, 2, or 4
#endif

extern circbuf_t * receive;
extern circbuf_t * transmit;

/*
 * Function definitions see memory_dma.h for documentation
 */

extern void DMA0_IRQHandler()
{
  NVIC_DisableIRQ(DMA0_IRQn);
}

extern void DMA2_IRQHandler()
{
  NVIC_DisableIRQ(DMA2_IRQn);
  UART0_C5 &= ~UART0_C5_TDMAE_MASK;
  DMA_DSR_BCR2 |= DMA_DSR_BCR_DONE_MASK;
  transmit->tail = (uint8_t *) (DMA_SAR2);
  transmit->head = (uint8_t *) (DMA_SAR2);
  transmit->count = 0;
  NVIC_EnableIRQ(DMA2_IRQn);
}

extern void DMA3_IRQHandler()
{
  for(volatile uint8_t i = 0; i < 256; i++);
}

void dma_init()
{
  // Setup the clock to go to the DMA module
  SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

  // Setup the clock to go to the DMAMUX module
  SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

} // dma_init()

void dma_uart_init()
{
  // Setup the clock to go to the DMA module
  SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

  // Setup the clock to go to the DMAMUX module
  SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

  // Setup the UART0_D register as the src
  DMA_SAR3 = (uint32_t) &UART0_D;

  // Setup the receive buffer as the dst
  DMA_DAR3 = (uint32_t) receive->buffer;

  // Setup the UART0_D register as the src
  DMA_SAR2 = (uint32_t) transmit->buffer;

  // Setup the receive buffer as the dst
  DMA_DAR2 = (uint32_t) &UART0_D;

  // Set the dma mux chanel for UART
  DMAMUX0_CHCFG3 |= DMAMUX_CHCFG_ENBL_MASK | 2;

  // Set the dma mux chanel for UART
  DMAMUX0_CHCFG2 |= DMAMUX_CHCFG_ENBL_MASK | 3;

  // Enable IRQ for the 2 dma channels
  NVIC_EnableIRQ(DMA2_IRQn);
  NVIC_EnableIRQ(DMA3_IRQn);

  // Finish setting up the dma channel
  DMA_DCR3 |= (DMA_DCR_SSIZE(1)
               | DMA_DCR_DSIZE(1)
               | DMA_DCR_DINC_MASK
               | DMA_DCR_EINT_MASK
               | DMA_DCR_EADREQ_MASK
               | DMA_DCR_CS_MASK
               | DMA_DCR_DMOD(0b0110)
               | DMA_DCR_ERQ_MASK);

  // Finish setting up the dma channel
  DMA_DCR2 |= (DMA_DCR_SSIZE(1)
               | DMA_DCR_DSIZE(1)
               | DMA_DCR_SINC_MASK
               | DMA_DCR_EINT_MASK
               | DMA_DCR_CS_MASK
               | DMA_DCR_EADREQ_MASK
               | DMA_DCR_SMOD(0b0110)
               | DMA_DCR_ERQ_MASK);
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
    // Set the source, destination, and number of bytes
    DMA_DSR_BCR0 = length;
    DMA_SAR0 = (uint32_t) src;
    DMA_DAR0 = (uint32_t) dst;
    NVIC_EnableIRQ(DMA0_IRQn);
    DMA_DCR0 = MEMMOVE_START(DMA_SIZE);

    // Block until complete
    while(!(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK));
  }

  return SUCCESS;
} // memmove_dma()

uint8_t memset_dma(uint8_t * dst, int32_t length, uint8_t value)
{
  // Check for null pointers
  CHECK_NULL(dst);

  // Set the source, destination, and number of bytes
  DMA_DSR_BCR0 = length;
  DMA_SAR0 = (uint32_t) &value;
  DMA_DAR0 = (uint32_t) dst;
  NVIC_EnableIRQ(DMA0_IRQn);
  DMA_DCR0 = MEMSET_START(DMA_SIZE);

  // Block until complete
  while(!(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK));

  return SUCCESS;
} // memset_dma()

uint8_t memzero_dma(uint8_t * dst, int32_t length)
{
  return memset_dma(dst, length, 0);
} // memzero_dma()
