#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>
#include "circbuf.h"
#include "project_defs.h"
#include "unit_circbuf.h"

// TODO: Remove
#include <stdio.h>

#define BUF_SIZE (10)

// Result used in most tests
uint32_t circbuf_res = 0;
circbuf_t * buf = NULL;

void test_circbuf_init_destroy(void **state)
{
  circbuf_res = circbuf_init(&buf, BUF_SIZE);
  assert_int_equal(circbuf_res, CB_ENUM_NO_ERROR);

  circbuf_res = circbuf_destroy(buf);
  assert_int_equal(circbuf_res, CB_ENUM_NO_ERROR);
} // test_circbuf_init_destroy()

void test_circbuf_ops_null_ptr(void **state)
{
  uint8_t value = 0;

  assert_int_equal(circbuf_init((circbuf_t **)NULL, BUF_SIZE), CB_ENUM_NULL_POINTER);
  assert_int_equal(circbuf_destroy((circbuf_t *)NULL), CB_ENUM_NULL_POINTER);
  assert_int_equal(circbuf_add_item((circbuf_t *)NULL, 1), CB_ENUM_NULL_POINTER);
  assert_int_equal(circbuf_remove_item((circbuf_t *)NULL, &value), CB_ENUM_NULL_POINTER);
  assert_int_equal(circbuf_peak((circbuf_t *)NULL, 1, &value), CB_ENUM_NULL_POINTER);
  assert_int_equal(circbuf_empty((circbuf_t *)NULL), CB_ENUM_NULL_POINTER);
  assert_int_equal(circbuf_full((circbuf_t *)NULL), CB_ENUM_NULL_POINTER);
} // test_circbuf_init_null_ptr()

void test_circbuf_add_remove_full(void **state)
{
  uint8_t value = 0;

  circbuf_res = circbuf_init(&buf, BUF_SIZE);
  assert_int_equal(circbuf_res, CB_ENUM_NO_ERROR);

  // Loop over buf size adding values
  for (uint32_t i = 0; i < BUF_SIZE; i++)
  {
    assert_int_equal(circbuf_add_item(buf, i), CB_ENUM_NO_ERROR);
  }

  // Loop over buf size removing values and checking contents
  for (uint32_t i = 0; i < BUF_SIZE; i++)
  {
    assert_int_equal(circbuf_remove_item(buf, &value), CB_ENUM_NO_ERROR);
    assert_int_equal(value, i);
  }

  circbuf_res = circbuf_destroy(buf);
  assert_int_equal(circbuf_res, CB_ENUM_NO_ERROR);
} // test_circbuf_add_remove_full()

void test_circbuf_add_full(void **state)
{
  assert_int_equal(circbuf_init(&buf, BUF_SIZE), CB_ENUM_NO_ERROR);

  // Loop over buf size adding values until full
  for (uint32_t i = 0; i < BUF_SIZE; i++)
  {
    assert_int_equal(circbuf_add_item(buf, i), CB_ENUM_NO_ERROR);
  }

  assert_int_equal(circbuf_add_item(buf, 100), CB_ENUM_FULL);
  assert_int_equal(circbuf_destroy(buf), CB_ENUM_NO_ERROR);
} // test_circbuf_add__full()

void test_circbuf_remove_empty(void **state)
{
  uint8_t value = 0;

  assert_int_equal(circbuf_init(&buf, BUF_SIZE), CB_ENUM_NO_ERROR);
  assert_int_equal(circbuf_remove_item(buf, &value), CB_ENUM_EMPTY);
  assert_int_equal(circbuf_destroy(buf), CB_ENUM_NO_ERROR);
} // test_circbuf_add_remove_full()

void test_circbuf_wrap_add_remove(void **state)
{
  uint8_t value = 0;

  circbuf_res = circbuf_init(&buf, BUF_SIZE);
  assert_int_equal(circbuf_res, CB_ENUM_NO_ERROR);

  // Loop over buf size adding values
  for (uint32_t i = 0; i < 6; i++)
  {
    assert_int_equal(circbuf_add_item(buf, i), CB_ENUM_NO_ERROR);
  }

  // Loop over buf size removing values and checking contents
  for (uint32_t i = 0; i < 6; i++)
  {
    assert_int_equal(circbuf_remove_item(buf, &value), CB_ENUM_NO_ERROR);
    assert_int_equal(value, i);
  }

  // Loop over buf size adding values
  for (uint32_t i = 0; i < BUF_SIZE; i++)
  {
    assert_int_equal(circbuf_add_item(buf, i), CB_ENUM_NO_ERROR);
  }

  // Loop over buf size removing values and checking contents
  for (uint32_t i = 0; i < BUF_SIZE; i++)
  {
    assert_int_equal(circbuf_remove_item(buf, &value), CB_ENUM_NO_ERROR);
    assert_int_equal(value, i);
  }

  circbuf_res = circbuf_destroy(buf);
  assert_int_equal(circbuf_res, CB_ENUM_NO_ERROR);
} // test_circbuf_wrap_add()

void test_circbuf_check_full(void **state)
{
  assert_int_equal(circbuf_init(&buf, BUF_SIZE), CB_ENUM_NO_ERROR);
  assert_int_equal(circbuf_full(buf), CB_ENUM_FAILURE);

  // Fill up buffer
  for (uint32_t i = 0; i < BUF_SIZE; i++)
  {
    assert_int_equal(circbuf_add_item(buf, i), CB_ENUM_NO_ERROR);
  }

  assert_int_equal(circbuf_full(buf), CB_ENUM_NO_ERROR);
  assert_int_equal(circbuf_destroy(buf), CB_ENUM_NO_ERROR);
} // test_circbuf_check_full()

void test_circbuf_check_empty(void **state)
{
  assert_int_equal(circbuf_init(&buf, BUF_SIZE), CB_ENUM_NO_ERROR);
  assert_int_equal(circbuf_empty(buf), CB_ENUM_NO_ERROR);
  assert_int_equal(circbuf_add_item(buf, 1), CB_ENUM_NO_ERROR);
  assert_int_equal(circbuf_empty(buf), CB_ENUM_FAILURE);
  assert_int_equal(circbuf_destroy(buf), CB_ENUM_NO_ERROR);
} // test_circbuf_check_full()
