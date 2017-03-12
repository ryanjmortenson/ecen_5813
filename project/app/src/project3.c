#include "project_defs.h"
#include "project3.h"

#ifdef FRDM
#include "spi.h"
#endif // FRDM

uint8_t project_3_spi()
{
#ifdef FRDM
  spi_configure();
#endif // FRDM
  return SUCCESS;
} // project_3_spi()
