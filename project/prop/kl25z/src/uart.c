#include <stdint.h>
#include "MKL25Z4.h"
#include "project_defs.h"

// Typical clock speed for the fll
#define CORE_CLOCK (20970000L)
#define MCGFLLCLK (1)

// User the lowest over sample for more speed
#define OVER_SAMPLE (0x03)

// Used to put the transmit/receive into GPIO
#define ALT_2 (2)

int8_t uart_configure(uint32_t baud)
{
  // Calculate baud rate modulo devisor
  uint16_t brmd = (CORE_CLOCK / ((OVER_SAMPLE + 1) * baud));

  // Set the SIM_SCGC5 register PORTA bit to 1
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

  // Set the system gating clock control register UART0 bit to 1
  SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

  // Reset the SIM_SOPT2 register UART0 bits to 0
  SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;

  // Reset the SIM_SOPT2 register UART0 bits to 10 which MCGFLLCLK
  SIM_SOPT2 |= SIM_SOPT2_UART0SRC(MCGFLLCLK);

  // Select ALT_2 usage to enable UART0 on pins
  PORTA_PCR1 = PORT_PCR_MUX(ALT_2);
  PORTA_PCR2 = PORT_PCR_MUX(ALT_2);

  // Set the oversample to 4
  UART0_C4 = UARTLP_C4_OSR(OVER_SAMPLE);

  // Set the BOTHEDGE bit because the sample rate is really low
  UART0_C5 = UART0_C5_BOTHEDGE_MASK;

  // Set the baud rate modulo divisor to the calculated value
  UART0_BDH = (brmd >> 8) & UARTLP_BDH_SBR_MASK;
  UART0_BDL = (brmd & UARTLP_BDL_SBR_MASK);

  // Enable the transmitter and receiver
  UART0_C2 = UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK;
  return 0;
}

int8_t uart_send_byte(uint8_t byte)
{
  // Wait for the ready flag to transmit
  while(!(UART0_S1_REG(UART0_BASE_PTR) & UART0_S1_TDRE_MASK));
  UART_D_REG(UART0_BASE_PTR) = byte;
  return 0;
}

int8_t uart_send_byte_n(uint8_t * bytes, uint8_t length)
{
  // Loop over length sending each byte
  for(uint8_t i = 0; i < length; i++)
  {
    uart_send_byte(*(bytes + i));
  }
  return 0; }

uint8_t uart_receive_byte()
{
  while (!(UART_S1_REG(UART0_BASE_PTR) & UART_S1_RDRF_MASK));
  return UART_D_REG(UART0_BASE_PTR);
}

