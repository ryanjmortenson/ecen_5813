#ifndef __UNIT_DATA_H__
#define __UNIT_DATA_H__

/*
 * \brief test_big_to_little32: test big_to_little32 under normal operations
 *
 */
void test_big_to_little32(void **state);

/*
 * \brief test_big_to_little32_null_ptr: test big_to_little32 trying to catch
 *                                       null pointer
 *
 */
void test_big_to_little32_null_ptr(void **state);

/*
 * \brief test_little_to_big32: test little_to_big32 under normal operations
 *
 */
void test_little_to_big32(void **state);

/*
 * \brief test_little_to_big32_null_ptr: test little_to_big32 trying to catch
 *                                       null pointer
 *
 */
void test_little_to_big32_null_ptr(void **state);

#endif // __UNIT_DATA_H__
