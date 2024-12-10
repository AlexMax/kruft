//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

struct zz_test_state_s;

enum zz_test_result_e
{
    ZZTEST_RESULT_SUCCESS,
    ZZTEST_RESULT_FAIL,
    ZZTEST_RESULT_SKIP,
};

typedef void (*zz_test_func)(struct zz_test_state_s *);

struct zz_test_s
{
    zz_test_func func;
    const char *suite_name;
    const char *test_name;
};

/**
 * @brief Define a test
 *
 * @param s Test suite.  Must be valid identifier.
 * @param t Test name.  Must be valid identifier.
 */
#define TEST(s, t) void zz_test__##s##__##t(struct zz_test_state_s *zz_test_state)

/**
 * @brief Expect boolean equality.
 */
#define EXPECT_TRUE(l, r)                                                                                              \
    {                                                                                                                  \
        (void)zz_test_state;                                                                                           \
        if (!!l != !!r)                                                                                                \
        {                                                                                                              \
            zz_test_result(zz_test_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "!!" #l " != !!" #r);                \
            return;                                                                                                    \
        }                                                                                                              \
    }

/**
 * @brief Expect boolean inequality.
 */
#define EXPECT_FALSE(l, r)                                                                                             \
    {                                                                                                                  \
        (void)zz_test_state;                                                                                           \
        if (!!l == !!r)                                                                                                \
        {                                                                                                              \
            zz_test_result(zz_test_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "!!" #l " == !!" #r);                \
            return;                                                                                                    \
        }                                                                                                              \
    }

/**
 * @brief Expect exact equality.
 */
#define EXPECT_EQ(l, r)                                                                                                \
    {                                                                                                                  \
        (void)zz_test_state;                                                                                           \
        if (l != r)                                                                                                    \
        {                                                                                                              \
            zz_test_result(zz_test_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, #l " != " #r);                       \
            return;                                                                                                    \
        }                                                                                                              \
    }

/**
 * @brief Expect string equality.
 */
#define EXPECT_STREQ(l, r)                                                                                             \
    {                                                                                                                  \
        (void)zz_test_state;                                                                                           \
        if (strcmp(l, r) != 0)                                                                                         \
        {                                                                                                              \
            zz_test_result(zz_test_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "0 != strcmp(" #l ", " #r ")");      \
            return;                                                                                                    \
        }                                                                                                              \
    }

/**
 * @brief Signal success.
 */
#define SUCCEED()                                                                                                      \
    {                                                                                                                  \
        zz_test_result(zz_test_state, __FILE__, __LINE__, ZZTEST_RESULT_SUCCESS, NULL);                                \
    }

/**
 * @brief Signal failure.
 */
#define FAIL()                                                                                                         \
    {                                                                                                                  \
        zz_test_result(zz_test_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "Failure");                              \
        return;                                                                                                        \
    }

/**
 * @brief Signal skip.
 */
#define SKIP()                                                                                                         \
    {                                                                                                                  \
        zz_test_result(zz_test_state, __FILE__, __LINE__, ZZTEST_RESULT_SKIP, NULL);                                   \
        return;                                                                                                        \
    }

/**
 * @brief Add a failure, without a return.
 */
#define ADD_FAILURE()                                                                                                  \
    {                                                                                                                  \
        zz_test_result(zz_test_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "Failure");                              \
    }

/**
 * @brief Define an array of tests.
 */
#define EXPORT_TEST_SUITE(s) struct zz_test_s zz_test_suite__##s[]

/**
 * @brief A pointer to a test function.
 */
#define EXPORT_TEST(s, t) {&zz_test__##s##__##t, #s, #s "." #t}

/**
 * @brief Define a count of how many tests we have.
 */
#define EXPORT_TEST_SUITE_COUNT(s)                                                                                     \
    unsigned long zz_test_suite_count__##s = sizeof(zz_test_suite__##s) / sizeof(struct zz_test_s)

/**
 * @brief Run a test suite.  Call this from main().
 */
#define RUN_TEST_SUITE(s)                                                                                              \
    {                                                                                                                  \
        extern struct zz_test_s *zz_test_suite__##s;                                                                   \
        extern unsigned long zz_test_suite_count__##s;                                                                 \
        zz_test_suite_run(#s, &zz_test_suite__##s, zz_test_suite_count__##s);                                          \
    }

/**
 * @brief Initialize test suite.
 */
void RUN_TESTS(void);

/**
 * @brief Get result of test suite.
 *
 * @return Return code to return from main().
 */
int RUN_TESTS_RESULT(void);

void zz_test_result(struct zz_test_state_s *state, const char *file, unsigned long line, enum zz_test_result_e msg,
                    const char *msgstr);
void zz_test_suite_run(const char *name, struct zz_test_s *tests, unsigned long count);
