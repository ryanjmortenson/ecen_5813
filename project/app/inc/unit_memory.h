#ifndef __UNIT_MEMORY_H__
#define __UNIT_MEMORY_H__

/*
 * \brief test_my_memmove: test my_memmove function in normal operation
 *
 */
void test_my_memmove(void **state);

/*
 * \brief test_my_memmove_dst_starts_in_src: test my_memmove function where
 *                                           destination starts in source
 *
 */
void test_my_memmove_dst_starts_in_src(void **state);

/*
 * \brief test_my_memmove_dst_ends_in_src: test my_memmove function where
 *                                         destination ends in source
 *
 */
void test_my_memmove_dst_ends_in_src(void **state);

/*
 * \brief test_my_memmove_null_ptrs: test my_memmove function trying to catch
 *                                   null pointers
 *
 */
void test_my_memmove_null_ptrs(void **state);

/*
 * \brief test_my_memset: test my_memset under normal operations
 *
 */
void test_my_memset(void **state);

/*
 * \brief test_my_memset_null_ptr: test my_memset trying to catch null
 *                                   pointers
 *
 */
void test_my_memset_null_ptr(void **state);

/*
 * \brief test_my_memzero: test my_memzero under normal operations
 *
 */
void test_my_memzero(void **state);

/*
 * \brief test_my_memzero_null_ptr: test my_memzero trying to catch null
 *                                  pointers
 *
 */
void test_my_memzero_null_ptr(void **state);

/*
 * \brief test_my_reverse_odd: test my_reverse with odd length string
 *
 */
void test_my_reverse_odd(void **state);

/*
 * \brief test_my_reverse_even: test my_reverse with even length string
 *
 */
void test_my_reverse_even(void **state);

/*
 * \brief test_my_reverse_single: test my_reverse with single character
 *
 */
void test_my_reverse_single(void **state);

/*
 * \brief test_my_reverse_null_ptr: test my_reverse trying to catch null pointer
 *
 */
void test_my_reverse_null_ptr(void **state);

/*
 * \brief test_my_reverse_max: test my_reverse with 255 character string
 *
 */
void test_my_reverse_max(void **state);

#endif // __UNIT_MEMORY_H__
