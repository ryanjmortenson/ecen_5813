#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>
#include "data.h"
#include "memory.h"
#include "project_defs.h"
#include "unit_data.h"

// Byte swap length
#define BYTE_SWAP_LEN (7)

// Array of integers for byteswapping
uint32_t big_to_little[] = {
  1,
  2,
  1512354,
  44312,
  415123,
  45135212,
  13515
};

// Byte swapped array of integers for byteswapping
uint32_t little_to_big[] = {
  16777216,
  33554432,
  2719160064,
  413990912,
  2471822848,
  1823846402,
  3409182720
};

// Buffer for bytswapping
uint32_t byte_swap_buffer[BYTE_SWAP_LEN];

// Result used in most tests
uint32_t data_res = 0;

void test_big_to_little32(void **state)
{
  my_memmove((uint8_t *)big_to_little, (uint8_t *)byte_swap_buffer, BYTE_SWAP_LEN);
  data_res = big_to_little32(byte_swap_buffer, BYTE_SWAP_LEN);
  assert_int_equal(data_res, SUCCESS);
  assert_memory_equal(byte_swap_buffer, little_to_big, BYTE_SWAP_LEN);
} // test_big_to_little32()

void test_big_to_little32_null_ptr(void **state)
{
  data_res = big_to_little32((uint32_t *)NULL, BYTE_SWAP_LEN);
  assert_int_equal(data_res, NULL_POINTER);
} // test_big_to_little32_null_ptr()

void test_little_to_big32(void **state)
{
  my_memmove((uint8_t *)little_to_big, (uint8_t *)byte_swap_buffer, BYTE_SWAP_LEN);
  data_res = little_to_big32(byte_swap_buffer, BYTE_SWAP_LEN);
  assert_int_equal(data_res, SUCCESS);
  assert_memory_equal(byte_swap_buffer, big_to_little, BYTE_SWAP_LEN);
} // test_little_to_big32()

void test_little_to_big32_null_ptr(void **state)
{
  data_res = big_to_little32((uint32_t *)NULL, BYTE_SWAP_LEN);
  assert_int_equal(data_res, NULL_POINTER);
} // test_little_to_big32_null_prt()
