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

// Test memmove normally
void test_my_memmove(void **state)
{
  // Do a normal move from str to src checking for success
  assert_int_equal(my_memmove(str, src, STR_LEN), SUCCESS);

  // Validate memory should be equal
  assert_memory_equal((void *)src, (void *)str, STR_LEN);
} // test_my_memmove()

// Test memmove where destination starts in source
void test_my_memmove_dst_starts_in_src(void **state)
{
  // Do a normal move from str to src checking for success
  assert_int_equal(my_memmove(str, src, STR_LEN), SUCCESS);

  // Do a a move where the dst starts in src
  assert_int_equal(my_memmove((src + 2), (src + 5), 4), SUCCESS);

  // Validate memory should be equal to string
  assert_memory_equal((void *)src, (void *)"1234534560", STR_LEN);
} // test_my_memmove_dst_starts_in_src()

// Test memmove where source starts in destination
void test_my_memmove_dst_ends_in_src(void **state)
{
  // Do a normal move from str to src checking for success
  assert_int_equal(my_memmove(str, src, STR_LEN), SUCCESS);

  // Do a a move where the src starts in dst
  assert_int_equal(my_memmove((src + 5), (src + 1), 4), SUCCESS);

  // Validate memory should be equal to string
  assert_memory_equal((void *)src, (void *)"1678967890", STR_LEN);
} // test_my_memmove_dst_ends_in_src()

// Test memmove where null pointers are passed in for source and destination
void test_my_memmove_null_ptrs(void **state)
{
  // Pass a null pointer into src and ensure it returns null pointer
  assert_int_equal(my_memmove((uint8_t *)NULL, src, 4), NULL_POINTER);

  // Pass a null pointer into dst and ensure it returns null pointer
  assert_int_equal(my_memmove(src, (uint8_t *)NULL, 4), NULL_POINTER);
} // test_my_memmove_null_ptrs()

// Test memset normally
void test_my_memset(void **state)
{
  // Do a normal memset and ensure memory was set properly
  assert_int_equal(my_memset(src, STR_LEN, 'A'), SUCCESS);
  assert_memory_equal((void *)src, (void *)"AAAAAAAAAA", STR_LEN);
} // test_my_memset()

// Test memset where a null pointer is passed in for source
void test_my_memset_null_ptr(void **state)
{
  // Pass a null pointer into src and ensure it returns null pointer
  assert_int_equal(my_memset((uint8_t *)NULL, STR_LEN, 'A'), NULL_POINTER);
} // test_my_memset_null_ptr()

// Test memzero normally
void test_my_memzero(void **state)
{
  uint8_t zeros[10] = {0};

  // Do a normal memmzero and ensure memory is zeroed out
  assert_int_equal(my_memzero(src, STR_LEN), SUCCESS);
  assert_memory_equal((void *)src, (void *)zeros, STR_LEN);
} // test_my_memzero()

// Test memzero where a null pointer is passed in for source
void test_my_memzero_null_ptr(void **state)
{
  // Pass a null pointer into src and ensure it returns null pointer
  assert_int_equal(my_memzero((uint8_t *)NULL, STR_LEN), NULL_POINTER);
} // test_my_memzero_null_ptr()

// Test reverse on an odd string
void test_my_reverse_odd(void **state)
{
  // Do a normal move from str to src checking for success
  assert_int_equal(my_memmove(str, src, STR_LEN), SUCCESS);

  // Do a reverse on an odd length string and ensure memory is
  // equal to reversed string
  assert_int_equal(my_reverse(src, STR_LEN - 1), SUCCESS);
  assert_memory_equal((void *)src, (void *)"987654321", STR_LEN - 1);
} // test_my_reverse_odd()

// Test reverse on an even string
void test_my_reverse_even(void **state)
{
  // Do a normal move from str to src checking for success
  assert_int_equal(my_memmove(str, src, STR_LEN), SUCCESS);

  // Do a reverse on an even length string and ensure memory is
  // equal to reversed string
  assert_int_equal(my_reverse(src, STR_LEN), SUCCESS);
  assert_memory_equal((void *)src, (void *)"0987654321", STR_LEN);
} // test_my_reverse_even()

// Test reverse on single character
void test_my_reverse_single(void **state)
{
  // Put a 1 character string in src and ensure success
  assert_int_equal(my_memmove((uint8_t *)"a", src, 1), SUCCESS);

  // Do a reverse on a one character string and ensure memory is
  // equal to reversed string
  assert_int_equal(my_reverse(src, 1), SUCCESS);
  assert_memory_equal((void *)src, (void *)"a", 1);
} // test_my_reverse_single()

// Test reverse where a null pointer is passed in for source
void test_my_reverse_null_ptr(void **state)
{
  // Pass a null pointer into src and ensure it returns null pointer
  assert_int_equal(my_reverse((uint8_t *)NULL, STR_LEN), NULL_POINTER);
} // test_my_reverse_null_prt()

// Test reverse with a 255 byte string
void test_my_reverse_max(void **state)
{
  const uint8_t MAX = 255;
  uint8_t buffer[MAX];
  uint8_t rev_buffer[MAX];

  // Create a max length buffer and reverse max length buffer
  for (int i = 0; i < MAX; i++)
  {
    buffer[i] = i;
    rev_buffer[i] = MAX - i - 1;
  }

  // Reverse string ensuring success and check result is reversed
  assert_int_equal(my_reverse(buffer, MAX), SUCCESS);
  assert_memory_equal(rev_buffer, buffer, MAX);
} // test_my_reverse_max()
