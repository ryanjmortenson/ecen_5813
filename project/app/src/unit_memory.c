#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "memory.h"
#include "project_defs.h"
#include "unit_memory.h"

// String length for most of the memory tests
#define STR_LEN (10)

// String used for memory tests
uint8_t *str = (uint8_t *)"1234567890";

// Buffer user for memory tests
uint8_t src[STR_LEN + 1] = {0};

// Result used in most tests
uint32_t memory_res = 0;

// Test memmove normally
void test_my_memmove(void **state)
{
  memory_res = my_memmove(str, src, STR_LEN);
  assert_int_equal(memory_res, SUCCESS);
  assert_memory_equal((void *)src, (void *)str, STR_LEN);
} // test_my_memmove()

// Test memmove where destination starts in source
void test_my_memmove_dst_starts_in_src(void **state)
{
  memory_res = my_memmove(str, src, STR_LEN);
  memory_res = my_memmove((src + 2), (src + 5), 4);
  assert_int_equal(memory_res, SUCCESS);
  assert_memory_equal((void *)src, (void *)"1234534560", STR_LEN);
} // test_my_memmove_dst_starts_in_src()

// Test memmove where source starts in destination
void test_my_memmove_dst_ends_in_src(void **state)
{
  memory_res = my_memmove(str, src, STR_LEN);
  memory_res = my_memmove((src + 5), (src + 1), 4);
  assert_int_equal(memory_res, SUCCESS);
  assert_memory_equal((void *)src, (void *)"1678967890", STR_LEN);
} // test_my_memmove_dst_ends_in_src()

// Test memmove where null pointers are passed in for source and destination
void test_my_memmove_null_ptrs(void **state)
{
  memory_res = my_memmove((uint8_t *)NULL, src, 4);
  assert_int_equal(memory_res, NULL_POINTER);
  memory_res = my_memmove(src, (uint8_t *)NULL, 4);
  assert_int_equal(memory_res, NULL_POINTER);
} // test_my_memmove_null_ptrs()

// Test memset normally
void test_my_memset(void **state)
{
  memory_res = my_memset(src, STR_LEN, 'A');
  assert_int_equal(memory_res, SUCCESS);
  assert_memory_equal((void *)src, (void *)"AAAAAAAAAA", STR_LEN);
} // test_my_memset()

// Test memset where a null pointer is passed in for source
void test_my_memset_null_ptr(void **state)
{
  memory_res = my_memset((uint8_t *)NULL, STR_LEN, 'A');
  assert_int_equal(memory_res, NULL_POINTER);
} // test_my_memset_null_ptr()

// Test memzero normally
void test_my_memzero(void **state)
{
  uint8_t zeros[10] = {0};
  memory_res = my_memzero(src, STR_LEN);
  assert_int_equal(memory_res, SUCCESS);
  assert_memory_equal((void *)src, (void *)zeros, STR_LEN);
} // test_my_memzero()

// Test memzero where a null pointer is passed in for source
void test_my_memzero_null_ptr(void **state)
{
  memory_res = my_memzero((uint8_t *)NULL, STR_LEN);
  assert_int_equal(memory_res, NULL_POINTER);
} // test_my_memzero_null_ptr()

// Test reverse on an odd string
void test_my_reverse_odd(void **state)
{
  memory_res = my_memmove(str, src, STR_LEN);
  memory_res = my_reverse(src, STR_LEN - 1);
  assert_int_equal(memory_res, SUCCESS);
  assert_memory_equal((void *)src, (void *)"987654321", STR_LEN - 1);
} // test_my_reverse_odd()

// Test reverse on an even string
void test_my_reverse_even(void **state)
{
  memory_res = my_memmove(str, src, STR_LEN);
  memory_res = my_reverse(src, STR_LEN);
  assert_int_equal(memory_res, SUCCESS);
  assert_memory_equal((void *)src, (void *)"0987654321", STR_LEN);
} // test_my_reverse_even()

// Test reverse on single character
void test_my_reverse_single(void **state)
{
  memory_res = my_memmove((uint8_t *)"a", src, 1);
  memory_res = my_reverse(src, 1);
  assert_int_equal(memory_res, SUCCESS);
  assert_memory_equal((void *)src, (void *)"a", 1);
} // test_my_reverse_single()

// Test reverse where a null pointer is passed in for source
void test_my_reverse_null_ptr(void **state)
{
  memory_res = my_reverse((uint8_t *)NULL, STR_LEN);
  assert_int_equal(memory_res, NULL_POINTER);
} // test_my_reverse_null_prt()

// Test reverse with a 255 byte string
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

  memory_res = my_reverse(buffer, MAX);
  assert_int_equal(memory_res, SUCCESS);
  assert_memory_equal(rev_buffer, buffer, MAX);
} // test_my_reverse_max()
