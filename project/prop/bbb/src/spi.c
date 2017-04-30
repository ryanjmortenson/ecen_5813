#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "project_defs.h"

#define DEVICE "/dev/spidev1.0"
#define MAX_BUF_SIZE 32

static int32_t fd;
const static int32_t mode = SPI_CPHA;
const static int32_t bits_per_word = 8;
const static int32_t max_speed_hz = 500000;
static uint8_t rx_byte = 0;

int spi_init()
{
  // Get access to the device
  if ((fd = open(DEVICE, O_RDWR)))
  {
    return FAILURE;
  }

  if (ioctl(fd, SPI_IOC_WR_MODE32, &mode) == -1)
  {
    return FAILURE;
  }

  if (ioctl(fd, SPI_IOC_RD_MODE32, &mode) == -1)
  {
    return FAILURE;
  }

  if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word) == -1)
  {
    return FAILURE;
  }

  if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits_per_word) == -1)
  {
    return FAILURE;
  }

  if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &max_speed_hz) == -1)
  {
    return FAILURE;
  }

  if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &max_speed_hz) == -1)
  {
    return FAILURE;
  }

  return SUCCESS;
}

void spi_send_byte(uint8_t byte)
{
  struct spi_ioc_transfer tr = {
    .tx_buf = (unsigned long)&byte,
    .rx_buf = (unsigned long)&rx_byte,
    .len = 1,
    .delay_usecs = 0,
    .speed_hz = max_speed_hz,
    .bits_per_word = bits_per_word
  };

  ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
}

void spi_send_bytes(uint8_t * bytes, uint32_t length)
{
  struct spi_ioc_transfer tr = {
    .tx_buf = (unsigned long)bytes,
    .rx_buf = (unsigned long)&rx_byte,
    .len = length,
    .delay_usecs = 0,
    .speed_hz = max_speed_hz,
    .bits_per_word = bits_per_word
  };

  ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
}

uint8_t spi_receive_byte()
{
  return rx_byte;
}
