#include <stdint.h>
#include "circbuf.h"
#include "log.h"
#include "MKL25Z4.h"
#include "project_defs.h"
#include "spi.h"

// Used to put the transmit/receive into GPIO
#define ALT_2 (2)

extern void SPI0_IRQHandler()
{

} // SPI0_IRQHandler()

uint8_t spi_init()
{
  // Set the SIM_SCGC5 register PORTD and PORTC bit to 1 which
  // allows the clock to go to port d and portc
  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

  // Set the system gating clock control register SPI0 bit to 1
  // allowing clock to spi subsystem
  SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

  // Select ALT_2 usage to enable SPI0 on pins
  PORTC_PCR5 = PORT_PCR_MUX(ALT_2);
  PORTD_PCR2 = PORT_PCR_MUX(ALT_2);
  PORTD_PCR3 = PORT_PCR_MUX(ALT_2);

  // Setup the baud rate for the slowest data transmission
  SPI0_BR |= SPI_BR_SPR(2);
  SPI0_BR |= SPI_BR_SPPR(2);

  // Set device to master
  SPI0_C1 |= SPI_C1_MSTR_MASK | SPI_C1_SPE_MASK;
  SPI0_C1 &= ~SPI_C1_CPHA_MASK;

  return SUCCESS;
} // spi_configure()

void spi_send_byte(uint8_t byte)
{
  while(!(SPI0_S & SPI_S_SPTEF_MASK));
  SPI0_D = byte;
} // spi_send_byte()

void spi_send_byte_n(uint8_t * bytes, uint32_t length)
{
  // Loop over bytes to send
  for (uint32_t i = 0; i < length; i++)
  {
    while(!(SPI0_S & SPI_S_SPTEF_MASK));
    SPI0_D = bytes[i];
  }
} // spi_send_byte_n()

uint8_t spi_receive_byte()
{
  while(!(SPI0_S & SPI_S_SPRF_MASK));
  return SPI0_D;
} // spi_receive_byte()
