#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>
#include "data.h"
#include "memory.h"
#include "project1.h"
#include "project_defs.h"

// String length for most of the memory tests
#define STR_LEN (10)

// Byte swap length
#define BYTE_SWAP_LEN (7)

// String used for memory tests
uint8_t *str = (uint8_t *)"1234567890";

// Buffer user for memory tests
uint8_t src[STR_LEN + 1] = {0};

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
uint32_t res = 0;

void test_my_memmove(void **state)
{
  res = my_memmove(str, src, STR_LEN);
  assert_int_equal(res, SUCCESS);
  assert_memory_equal((void *)src, (void *)str, STR_LEN);
} // test_my_memmove()

void test_my_memmove_dst_starts_in_src(void **state)
{
  res = my_memmove(str, src, STR_LEN);
  res = my_memmove((src + 2), (src + 5), 4);
  assert_int_equal(res, SUCCESS);
  assert_memory_equal((void *)src, (void *)"1234534560", STR_LEN);
} // test_my_memmove_dst_starts_in_src()

void test_my_memmove_dst_ends_in_src(void **state)
{
  res = my_memmove(str, src, STR_LEN);
  res = my_memmove((src + 5), (src + 1), 4);
  assert_int_equal(res, SUCCESS);
  assert_memory_equal((void *)src, (void *)"1678967890", STR_LEN);
} // test_my_memmove_dst_ends_in_src()

void test_my_memmove_null_ptrs(void **state)
{
  res = my_memmove((uint8_t *)NULL, src, 4);
  assert_int_equal(res, NULL_POINTER);
  res = my_memmove(src, (uint8_t *)NULL, 4);
  assert_int_equal(res, NULL_POINTER);
} // test_my_memmove_null_ptrs()

void test_my_memset(void **state)
{
  res = my_memset(src, STR_LEN, 'A');
  assert_int_equal(res, SUCCESS);
  assert_memory_equal((void *)src, (void *)"AAAAAAAAAA", STR_LEN);
} // test_my_memset()

void test_my_memset_null_ptr(void **state)
{
  res = my_memset((uint8_t *)NULL, STR_LEN, 'A');
  assert_int_equal(res, NULL_POINTER);
} // test_my_memset_null_ptr()

void test_my_memzero(void **state)
{
  uint8_t zeros[10] = {0};
  res = my_memzero(src, STR_LEN);
  assert_int_equal(res, SUCCESS);
  assert_memory_equal((void *)src, (void *)zeros, STR_LEN);
} // test_my_memzero()

void test_my_memzero_null_ptr(void **state)
{
  res = my_memzero((uint8_t *)NULL, STR_LEN);
  assert_int_equal(res, NULL_POINTER);
} // test_my_memzero_null_ptr()

void test_my_reverse_odd(void **state)
{
  res = my_memmove(str, src, STR_LEN);
  res = my_reverse(src, STR_LEN - 1);
  assert_int_equal(res, SUCCESS);
  assert_memory_equal((void *)src, (void *)"987654321", STR_LEN - 1);
} // test_my_reverse_odd()

void test_my_reverse_even(void **state)
{
  res = my_memmove(str, src, STR_LEN);
  res = my_reverse(src, STR_LEN);
  assert_int_equal(res, SUCCESS);
  assert_memory_equal((void *)src, (void *)"0987654321", STR_LEN);
} // test_my_reverse_even()

void test_my_reverse_single(void **state)
{
  res = my_memmove((uint8_t *)"a", src, 1);
  res = my_reverse(src, 1);
  assert_int_equal(res, SUCCESS);
  assert_memory_equal((void *)src, (void *)"a", 1);
} // test_my_reverse_single()

void test_my_reverse_null_ptr(void **state)
{
  res = my_reverse((uint8_t *)NULL, STR_LEN);
  assert_int_equal(res, NULL_POINTER);
} // test_my_reverse_null_prt()

void test_my_reverse_max(void **state)
{
  const uint8_t MAX = 255;
  uint8_t buffer[MAX];
  uint8_t rev_buffer[MAX];

  for (int i = 0; i < MAX; i++)
  {
    buffer[i] = i;
    rev_buffer[i] = MAX - i - 1;
  }

  res = my_reverse(buffer, MAX);
  assert_int_equal(res, SUCCESS);
  assert_memory_equal(rev_buffer, buffer, MAX);
} // test_my_reverse_max()

void test_big_to_little32(void **state)
{
  my_memmove((uint8_t *)big_to_little, (uint8_t *)byte_swap_buffer, BYTE_SWAP_LEN);
  res = big_to_little32(byte_swap_buffer, BYTE_SWAP_LEN);
  assert_int_equal(res, SUCCESS);
  assert_memory_equal(byte_swap_buffer, little_to_big, BYTE_SWAP_LEN);
} // test_big_to_little32()

void test_big_to_little32_null_ptr(void **state)
{
  res = big_to_little32((uint32_t *)NULL, BYTE_SWAP_LEN);
  assert_int_equal(res, NULL_POINTER);
} // test_big_to_little32_null_ptr()

void test_little_to_big32(void **state)
{
  my_memmove((uint8_t *)little_to_big, (uint8_t *)byte_swap_buffer, BYTE_SWAP_LEN);
  res = little_to_big32(byte_swap_buffer, BYTE_SWAP_LEN);
  assert_int_equal(res, SUCCESS);
  assert_memory_equal(byte_swap_buffer, big_to_little, BYTE_SWAP_LEN);
} // test_little_to_big32()

void test_little_to_big32_null_ptr(void **state)
{
  res = big_to_little32((uint32_t *)NULL, BYTE_SWAP_LEN);
  assert_int_equal(res, NULL_POINTER);
} // test_little_to_big32_null_prt()
