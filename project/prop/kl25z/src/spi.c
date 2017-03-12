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

}
void spi_configure()
{

  // Set the SIM_SCGC5 register PORTD bit to 1 which allows
  // the clock to go to port d
  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;


  // Set the system gating clock control register SPI0 bit to 1
  // allowing clock to spi subsystem
  SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

  // Select ALT_2 usage to enable SPI0 on pins
  PORTD_PCR0 = PORT_PCR_MUX(ALT_2);
  PORTD_PCR1 = PORT_PCR_MUX(ALT_2);
  PORTD_PCR2 = PORT_PCR_MUX(ALT_2);
  PORTD_PCR3 = PORT_PCR_MUX(ALT_2);

  // Set device to master
  SPI0_C1 |= SPI_C1_MSTR_MASK | SPI_C1_SPE_MASK;

} // spi_configure()

void spi_send_byte(uint8_t byte)
{
} // spi_send_byte()

int8_t spi_send_byte_n(uint8_t * bytes, uint32_t length)
{
  return 0;
} // spi_send_byte_n()

uint8_t spi_receive_byte()
{
  return 0;
} // spi_receive_byte()
