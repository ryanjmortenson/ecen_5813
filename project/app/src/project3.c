#include "project_defs.h"
#include "MKL25Z4.h"
#include "project3.h"
#include "memory.h"

#ifdef FRDM
#include "spi.h"
#include "memory_dma.h"
#endif // FRDM

/*
 * Function definitions see project3.h for documentation
 */

#define BUFFER_SIZE (255)

uint8_t project_3_spi()
{
#ifdef FRDM

  uint8_t src[BUFFER_SIZE] = {0xff};
  uint8_t dst[BUFFER_SIZE] = {0};
  my_memset(src, BUFFER_SIZE, 0xff);
  my_memset(dst, BUFFER_SIZE, 0);

  dma_init();
  memmove_dma(src, dst, BUFFER_SIZE, WORD);

#endif // FRDM
  return SUCCESS;
} // project_3_spi()
