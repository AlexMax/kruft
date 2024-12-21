//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// zztest - A greenfield subset of Google Test for crufty compilers.
//
// Configuration Defines:
// - ZZTEST_CONFIG_PRINTF: Define this to your own print function.
//

#if !defined(INCLUDE_ZZTEST_H)
#define INCLUDE_ZZTEST_H

#if defined(ZZTEST_CONFIG_PRINTF)
#define ZPRINTF_ ZZTEST_CONFIG_PRINTF
#else
#define ZPRINTF_ printf
#endif

struct zztest_state_s;

enum zztest_result_e
{
    ZZTEST_RESULT_SUCCESS,
    ZZTEST_RESULT_FAIL,
    ZZTEST_RESULT_SKIP,
};

typedef void (*zztest_func)(struct zztest_state_s *);

struct zztest_s
{
    zztest_func func;
    const char *suite_name;
    const char *test_name;
    struct zztest_s *next;
    struct zztest_s *next_skip;
    struct zztest_s *next_fail;
};

struct zztest_suite_s
{
    struct zztest_s *head;
    struct zztest_s *tail;
    const char *suite_name;
    unsigned long tests_count;
    struct zztest_suite_s *next;
};

/**
 * @brief Array length macro.
 */
#define ZZTEST_ARRLEN(a) (sizeof(a) / sizeof(*a))

/**
 * @brief Function name of a test suite.
 */
#define ZZTEST_SUITENAME(s) s##__SUITE

/**
 * @brief Symbol name of test suite info.
 */
#define ZZTEST_SUITEINFO(s) s##__SINFO

/**
 * @brief Function name of a test.
 */
#define ZZTEST_TESTNAME(s, t) s##__##t##__TEST

/**
 * @brief Symbol name of test info.
 */
#define ZZTEST_TESTINFO(s, t) s##__##t##__INFO

/**
 * @brief Define a test suite.
 *
 * @param s Test suite.  Must be valid identifier.
 */
#define SUITE(s)                                                                                                       \
    static struct zztest_suite_s ZZTEST_SUITEINFO(s);                                                                  \
    void ZZTEST_SUITENAME(s)(void)

/**
 * @brief Define a test.
 *
 * @param s Test suite.  Must be valid identifier.
 * @param t Test name.  Must be valid identifier.
 */
#define TEST(s, t)                                                                                                     \
    void ZZTEST_TESTNAME(s, t)(struct zztest_state_s * zztest_state);                                                  \
    static struct zztest_s ZZTEST_TESTINFO(s, t) = {ZZTEST_TESTNAME(s, t), #s, #s "." #t, NULL, NULL, NULL};           \
    void ZZTEST_TESTNAME(s, t)(struct zztest_state_s * zztest_state)

#define SUITE_TEST(s, t)                                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        struct zztest_suite_s *suite = &ZZTEST_SUITEINFO(s);                                                           \
        if (suite->head == NULL)                                                                                       \
        {                                                                                                              \
            suite->suite_name = #s;                                                                                    \
            suite->head = &ZZTEST_TESTINFO(s, t);                                                                      \
            suite->tail = suite->head;                                                                                 \
            suite->tests_count = 1;                                                                                    \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            suite->tail->next = &ZZTEST_TESTINFO(s, t);                                                                \
            suite->tail = suite->tail->next;                                                                           \
            suite->tests_count += 1;                                                                                   \
        }                                                                                                              \
    } while (0)

/**
 * @brief Expect equality.
 */
#define EXPECT_TRUE(t)                                                                                                 \
    {                                                                                                                  \
        if (!(t))                                                                                                      \
        {                                                                                                              \
            zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, #t);                                   \
        }                                                                                                              \
    }

/**
 * @brief Expect inequality.
 */
#define EXPECT_FALSE(t)                                                                                                \
    {                                                                                                                  \
        if (!!(t))                                                                                                     \
        {                                                                                                              \
            zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "!" #t);                               \
        }                                                                                                              \
    }

/**
 * @brief Expect boolean equality.
 */
#define EXPECT_BOOLEQ(l, r)                                                                                            \
    {                                                                                                                  \
        if (!!(l) != !!(r))                                                                                            \
        {                                                                                                              \
            zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "!!" #l " != !!" #r);                  \
        }                                                                                                              \
    }

/**
 * @brief Expect exact equality.
 */
#define EXPECT_EQ(l, r)                                                                                                \
    {                                                                                                                  \
        if ((l) != (r))                                                                                                \
        {                                                                                                              \
            zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, #l " != " #r);                         \
        }                                                                                                              \
    }

/**
 * @brief Expect string equality.
 */
#define EXPECT_STREQ(l, r)                                                                                             \
    {                                                                                                                  \
        if (zztest_strcmp((l), (r)) != 0)                                                                              \
        {                                                                                                              \
            zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "0 != strcmp(" #l ", " #r ")");        \
        }                                                                                                              \
    }

/**
 * @brief Add a failure, without a return.
 */
#define ADD_FAILURE()                                                                                                  \
    {                                                                                                                  \
        zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "Failure");                                \
    }

/**
 * @brief Signal failure.
 */
#define FAIL()                                                                                                         \
    {                                                                                                                  \
        zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "Failure");                                \
        return;                                                                                                        \
    }

/**
 * @brief Signal skip.
 */
#define SKIP()                                                                                                         \
    {                                                                                                                  \
        zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_SKIP, NULL);                                     \
        return;                                                                                                        \
    }

/**
 * @brief Add suite of tests to be run when RUN_TESTS is called.
 */
#define ADD_TEST_SUITE(s)                                                                                              \
    {                                                                                                                  \
        ZZTEST_SUITENAME(s)();                                                                                         \
        zztest_add_test_suite(&ZZTEST_SUITEINFO(s));                                                                   \
    }

/**
 * @brief Run all tests and return code which can be returned from main().
 */
#define RUN_TESTS() (zztest_run_all())

int zztest_strcmp(const char *lhs, const char *rhs);
void zztest_result(struct zztest_state_s *state, const char *file, unsigned long line, enum zztest_result_e msg,
                   const char *msgstr);
void zztest_add_test_suite(struct zztest_suite_s *suite);
int zztest_run_all(void);

//------------------------------------------------------------------------------
#if defined(ZZTEST_IMPLEMENTATION)
//------------------------------------------------------------------------------

#if defined(_WIN32)
#pragma comment(lib, "WinMM.Lib") // Timer functions
#include <Windows.h>
#elif defined(__unix__)
#include <sys/time.h> // Timer functions.
static struct timeval g_cTimeStart;
#endif

#if !defined(ZZTEST_CONFIG_PRINTF)
#include <stdio.h>
#endif

//------------------------------------------------------------------------------

struct zztest_state_s
{
    struct zztest_s *test;
    int failed;
    int skipped;
};

static unsigned long g_testsCount;
static struct zztest_suite_s *g_suitesHead;
static struct zztest_suite_s *g_suitesTail;
static unsigned long g_suitesCount;
static struct zztest_s *g_testFailHead;
static struct zztest_s *g_testFailTail;
static struct zztest_s *g_testSkipHead;
static struct zztest_s *g_testSkipTail;

/**
 * @brief Return time point with ms resolution.
 *
 * @details This is a compatible timer, not an accurate one.  We're making
 *          a test suite, not a benchmark.
 */
static unsigned long zztest_ms(void)
{
#if defined(_WIN32)
    return timeGetTime();
#elif defined(__unix__)
    unsigned long ms;
    struct timeval now;
    gettimeofday(&now, NULL);
    ms = (now.tv_sec - g_cTimeStart.tv_sec) * 1000 + (now.tv_usec - g_cTimeStart.tv_usec) / 1000;
    return ms;
#else
    return 0; // oh well...
#endif
}

/**
 * @brief Add a test to our list of failed tests.
 */
static void zztest_add_fail(struct zztest_s *test)
{
    if (g_testFailHead == NULL)
    {
        g_testFailHead = test;
        g_testFailTail = test;
    }
    else
    {
        g_testFailTail->next_fail = test;
        g_testFailTail = test;
    }
}

/**
 * @brief Add a test to our list of skipped tests.
 */
static void zztest_add_skip(struct zztest_s *test)
{
    if (g_testSkipHead == NULL)
    {
        g_testSkipHead = test;
        g_testSkipTail = test;
    }
    else
    {
        g_testSkipTail->next_skip = test;
        g_testSkipTail = test;
    }
}

//------------------------------------------------------------------------------

int zztest_strcmp(const char *lhs, const char *rhs)
{
    for (;; lhs++, rhs++)
    {
        if (*lhs != *rhs || *lhs == '\0')
        {
            break;
        }
    }
    return *((const unsigned char *)lhs) - *((const unsigned char *)rhs);
}

//------------------------------------------------------------------------------

void zztest_result(struct zztest_state_s *state, const char *file, unsigned long line, enum zztest_result_e msg,
                   const char *msgstr)
{
    switch (msg)
    {
    case ZZTEST_RESULT_SUCCESS:
        state->failed = 0;
        state->skipped = 0;
        break;
    case ZZTEST_RESULT_FAIL:
        ZPRINTF_("%s(%lu): error: %s\n\n", file, line, msgstr);
        state->failed += 1;
        break;
    case ZZTEST_RESULT_SKIP:
        state->skipped += 1;
        break;
    }
}

//------------------------------------------------------------------------------

void zztest_add_test_suite(struct zztest_suite_s *suite)
{
    if (g_suitesHead == NULL)
    {
        g_testsCount = suite->tests_count;
        g_suitesHead = suite;
        g_suitesTail = g_suitesHead;
        g_suitesCount = 1;
    }
    else
    {
        g_testsCount += suite->tests_count;
        g_suitesTail->next = suite;
        g_suitesTail = g_suitesTail->next;
        g_suitesCount += 1;
    }
}

//------------------------------------------------------------------------------

int zztest_run_all(void)
{
    unsigned long passed = 0, failed = 0, skipped = 0;
    unsigned long startAllMs = 0, endAllMs = 0;
    struct zztest_suite_s *suite = g_suitesHead;
    struct zztest_s *test = NULL;

#if defined(_WIN32)
    // Set timer resolution to 1ms.
    timeBeginPeriod(1);
#endif

    ZPRINTF_("[==========] Running %lu tests from %lu test suites.\n", g_testsCount, g_suitesCount);
    startAllMs = zztest_ms();

    for (; suite; suite = suite->next)
    {
        unsigned long startSuiteMs = 0, endSuiteMs = 0;

        ZPRINTF_("[----------] %lu tests from %s\n", suite->tests_count, suite->suite_name);
        startSuiteMs = zztest_ms();

        test = suite->head;
        for (; test; test = test->next)
        {
            unsigned long startTestMs = 0, endTestMs = 0;
            struct zztest_state_s state;

            ZPRINTF_("[ RUN      ] %s\n", test->test_name);
            state.test = test;
            state.failed = 0;
            state.skipped = 0;

            startTestMs = zztest_ms();
            test->func(&state);
            endTestMs = zztest_ms();

            if (state.failed != 0)
            {
                ZPRINTF_("[  FAILED  ] %s (%lu ms)\n", test->test_name, endTestMs - startTestMs);
                zztest_add_fail(test);
                failed += 1;
            }
            else if (state.skipped != 0)
            {
                ZPRINTF_("[  SKIPPED ] %s (%lu ms)\n", test->test_name, endTestMs - startTestMs);
                zztest_add_skip(test);
                skipped += 1;
            }
            else
            {
                ZPRINTF_("[       OK ] %s (%lu ms)\n", test->test_name, endTestMs - startTestMs);
                passed += 1;
            }
        }

        endSuiteMs = zztest_ms();
        ZPRINTF_("[----------] %lu tests from %s (%lu ms total)\n\n", suite->tests_count, suite->suite_name,
                 endSuiteMs - startSuiteMs);
    }

    endAllMs = zztest_ms();
    ZPRINTF_("[==========] %lu tests from %lu test suites ran. (%lu ms total)\n", g_testsCount, g_suitesCount,
             endAllMs - startAllMs);
    ZPRINTF_("[  PASSED  ] %lu tests.\n", passed);

    if (skipped != 0)
    {
        ZPRINTF_("[  SKIPPED ] %lu tests, listed below:\n", skipped);

        test = g_testSkipHead;
        for (; test; test = test->next_skip)
        {
            ZPRINTF_("[  SKIPPED ] %s\n", test->test_name);
        }
    }

    if (failed != 0)
    {
        ZPRINTF_("[  FAILED  ] %lu tests, listed below:\n", failed);

        test = g_testFailHead;
        for (; test; test = test->next_fail)
        {
            ZPRINTF_("[  FAILED  ] %s\n", test->test_name);
        }
    }

    return 0;
}

#if defined(ZZTEST_SELFCHECK)

TEST(zztest, passing1)
{
    EXPECT_TRUE(1 == 1);
    EXPECT_FALSE(1 != 1);
    EXPECT_BOOLEQ(1, 2);
}

TEST(zztest, passing2)
{
    EXPECT_EQ(1, 1);
    EXPECT_STREQ("foo", "foo");
}

TEST(zztest, failing1)
{
    EXPECT_TRUE(1 == 2);
    EXPECT_FALSE(1 != 2);
    EXPECT_BOOLEQ(1, 0);
}

TEST(zztest, failing2)
{
    EXPECT_EQ(1, 2);
    EXPECT_STREQ("foo", "bar");
    ADD_FAILURE();
}

TEST(zztest, skipping1)
{
    SKIP();
}

TEST(zztest, skipping2)
{
    SKIP();
}

SUITE(zztest)
{
    SUITE_TEST(zztest, passing1);
    SUITE_TEST(zztest, passing2);
    SUITE_TEST(zztest, failing1);
    SUITE_TEST(zztest, failing2);
    SUITE_TEST(zztest, skipping1);
    SUITE_TEST(zztest, skipping2);
}

int main()
{
    ADD_TEST_SUITE(zztest);
    return RUN_TESTS();
}

#endif // defined(ZZTEST_SELFCHECK)
#endif // defined(ZZTEST_IMPLEMENTATION)
#endif // !defined(INCLUDE_ZZTEST_H)
