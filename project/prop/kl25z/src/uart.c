#include <stdint.h>
#include "circbuf.h"
#include "log.h"
#include "MKL25Z4.h"
#include "project_defs.h"
#include "uart.h"

// Typical clock speed for the fll
#define CORE_CLOCK (20970000L)
#define MCGFLLCLK (1)

// Use oversampling of 8 + 1
#define OVER_SAMPLE (0x08)

// Shift for high byte of bdrm
#define BRMD_HIGH_SHIFT (8)

extern circbuf_t * receive;
extern circbuf_t * transmit;

// Uart ISR
extern void UART0_IRQHandler()
{
  // Critical section don't allow an interrupt in an interrupt
  NVIC_DisableIRQ(UART0_IRQn);

  // Take a byte out of the circular buffer and send it
  if (UART0_S1 & UART_S1_RDRF_MASK)
  {
    if (circbuf_full(receive) != CB_ENUM_FULL)
    {
      uint8_t rx_byte = uart_receive_byte();
      circbuf_add_item(receive, rx_byte);
    }
  }
  // Transmit a byte until the buffer is empty then shut off the TIE
  else if (UART0_S1 & UART_S1_TDRE_MASK)
  {
    if (circbuf_empty(transmit) != CB_ENUM_EMPTY)
    {
      uint8_t tx_byte = 0;
      circbuf_remove_item(transmit, &tx_byte);
      uart_send_byte(tx_byte);
    }
    else
    {
      // Signal transmit is done
      TRANSMIT_DONE;
    }
  }

  // Turn interrupts back on
  NVIC_EnableIRQ(UART0_IRQn);
}

void uart_configure(uint32_t baud)
{
  // Calculate baud rate modulo devisor
  uint16_t brmd = (CORE_CLOCK / ((OVER_SAMPLE + 1) * baud));

  // Set the SIM_SCGC5 register PORTA bit to 1 which allows
  // the clock to go to port a
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

  // Set the system gating clock control register UART0 bit to 1
  // allowing clock to uart subsystem
  SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

  // Reset the SIM_SOPT2 register UART0 bits to 0
  SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;

  // Set the SIM_SOPT2 register UART0 bits to 10 which MCGFLLCLK
  SIM_SOPT2 |= SIM_SOPT2_UART0SRC(MCGFLLCLK);

  // Select ALT_2 usage to enable UART0 on pins
  PORTA_PCR1 = PORT_PCR_MUX(ALT_2);
  PORTA_PCR2 = PORT_PCR_MUX(ALT_2);

  // Set the oversample to OVER_SAMPLE
  UART0_C4 = UARTLP_C4_OSR(OVER_SAMPLE);

  // Set the BOTHEDGE bit because the sample rate is low
  UART0_C5 = UART0_C5_BOTHEDGE_MASK;

  // Set the baud rate modulo divisor to the calculated value
  UART0_BDH = (brmd >> BRMD_HIGH_SHIFT) & UARTLP_BDH_SBR_MASK;
  UART0_BDL = (brmd & UARTLP_BDL_SBR_MASK);

  // Enable the transmitter and receiver and their interrupts
  UART0_C2 = UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK;

#ifdef CIRCBUF_DMA
  // Turn on the dma request for receive
  UART0_C5 |= UART0_C5_RDMAE_MASK;
#endif

#ifdef UART_INTERRUPTS
  // Add receive interrupt
  UART0_C2 |= UART_C2_RIE_MASK;

  // Enable the UART0 IRQ
  NVIC_EnableIRQ(UART0_IRQn);
#endif // UART_INTERRUPTS

} // uart_configure()

void uart_send_byte(uint8_t byte)
{
#ifndef UART_INTERRUPTS
  while(!(UART0_S1 & UART0_S1_TDRE_MASK));
#endif
  UART0_D = byte;
} // uart_send_byte()

int8_t uart_send_byte_n(uint8_t * bytes, uint32_t length)
{
  // Check for null pointer
  CHECK_NULL(bytes);

  // Loop over length sending each byte
  for(uint8_t i = 0; i < length; i++)
  {
    uart_send_byte(*(bytes + i));
  }
  return SUCCESS;
} // uart_send_byte_n()

uint8_t uart_receive_byte()
{
#ifndef UART_INTERRUPTS
  while (!(UART0_S1 & UART_S1_RDRF_MASK));
#endif
  return UART0_D;
} // uart_receive_byte()
