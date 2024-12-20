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
};

/**
 * @brief Array length macro.
 */
#define ZZTEST_ARRLEN(a) (sizeof(a) / sizeof(*a))

/**
 * @brief Symbol name of a test.
 */
#define ZZTEST_SUITENAME(s) s##__SUITE

/**
 * @brief Symbol name of a test.
 */
#define ZZTEST_TESTNAME(s, t) s##__##t##__TEST

/**
 * @brief Define a test
 *
 * @param s Test suite.  Must be valid identifier.
 * @param t Test name.  Must be valid identifier.
 */
#define TEST(s, t) void ZZTEST_TESTNAME(s, t)(struct zztest_state_s * zztest_state)

/**
 * @brief Expect equality.
 */
#define EXPECT_TRUE(t)                                                                                                 \
    {                                                                                                                  \
        if ((t))                                                                                                       \
        {                                                                                                              \
            zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, #t);                                   \
        }                                                                                                              \
    }

/**
 * @brief Expect inequality.
 */
#define EXPECT_FALSE(t)                                                                                                \
    {                                                                                                                  \
        if (!(t))                                                                                                      \
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
        if (strcmp((l), (r)) != 0)                                                                                     \
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
 * @brief Define an array of tests.
 */
#define EXPORT_TEST_SUITE(s) struct zztest_s ZZTEST_SUITENAME(s)[]

/**
 * @brief A pointer to a test function.
 */
#define EXPORT_TEST(s, t) {ZZTEST_TESTNAME(s, t), #s, #s "." #t}

/**
 * @brief Run a test suite.  Call this from main().
 */
#define RUN_TEST_SUITE(s) zztest_suite_run(#s, &ZZTEST_SUITENAME(s)[0], ZZTEST_ARRLEN(ZZTEST_SUITENAME(s)));

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

void zztest_result(struct zztest_state_s *state, const char *file, unsigned long line, enum zztest_result_e msg,
                   const char *msgstr);
void zztest_suite_run(const char *name, struct zztest_s *tests, unsigned long count);

//------------------------------------------------------------------------------
#if defined(ZZTEST_IMPLEMENTATION)
//------------------------------------------------------------------------------

#if defined(_WIN32)
#pragma comment(lib, "WinMM.Lib") // Timer functions
#include <Windows.h>
#elif defined(__unix__)
#include <sys/time.h> // Timer functions.
static struct timeval g_cTimeStart;
#else
#error "not implemented"
#endif

#if !defined(ZZTEST_CONFIG_PRINTF)
#include <stdio.h>
#endif

#include <stdlib.h>

//------------------------------------------------------------------------------

struct zztest_state_s
{
    struct zztest_s *test;
    int failed;
    int skipped;
};

static unsigned long g_ulSuites;
static unsigned long g_ulPassed;
static unsigned long g_ulFailed;
static unsigned long g_ulSkipped;
static const char **g_nszFailed;
static const char **g_nszSkipped;
static unsigned long g_ulStartTime;

//------------------------------------------------------------------------------

static void zztest_cleanup(void)
{
    free(g_nszFailed);
    free(g_nszSkipped);
}

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
#error "not implemented"
#endif
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

void zztest_suite_run(const char *name, struct zztest_s *tests, unsigned long count)
{
    unsigned i;
    unsigned long startms, endms;

    ZPRINTF_("[----------] %lu tests from %s\n", count, name);
    startms = zztest_ms();
    for (i = 0; i < count; i++)
    {
        struct zztest_state_s state;

        struct zztest_s *test = &tests[i];
        ZPRINTF_("[ RUN      ] %s\n", test->test_name);
        state.test = test;
        state.failed = 0;
        state.skipped = 0;
        test->func(&state);

        if (state.failed > 0)
        {
            const char **failed;

            ZPRINTF_("[  FAILED  ] %s (0 ms)\n", test->test_name);
            failed = (const char **)realloc(g_nszFailed, sizeof(char *) * (g_ulFailed + 1));
            if (failed == NULL)
            {
                ZPRINTF_("realloc failure\n");
                zztest_cleanup();
                exit(1);
            }

            g_nszFailed = failed;
            g_nszFailed[g_ulFailed] = test->test_name;
            g_ulFailed += 1;
        }
        else if (state.skipped > 0)
        {
            const char **skipped;

            ZPRINTF_("[  SKIPPED ] %s (0 ms)\n", test->test_name);
            skipped = (const char **)realloc(g_nszSkipped, sizeof(char *) * (g_ulSkipped + 1));
            if (skipped == NULL)
            {
                ZPRINTF_("realloc failure\n");
                zztest_cleanup();
                exit(1);
            }

            g_nszSkipped = skipped;
            g_nszSkipped[g_ulSkipped] = test->test_name;
            g_ulSkipped += 1;
        }
        else
        {
            ZPRINTF_("[       OK ] %s (0 ms)\n", test->test_name);
            g_ulPassed += 1;
        }
    }

    endms = zztest_ms();
    ZPRINTF_("[----------] %lu tests from %s (%lu ms total)\n\n", count, name, endms - startms);
}

//------------------------------------------------------------------------------

void RUN_TESTS(void)
{
    ZPRINTF_("[----------] Global test environment set-up.\n");

#if defined(_WIN32)
    // Set timer resolution to 1ms.
    timeBeginPeriod(1);
#endif

    g_ulPassed = 0;
    g_ulFailed = 0;
    g_ulSkipped = 0;
    g_ulSuites = 0;
    g_nszFailed = NULL;
    g_nszSkipped = NULL;
    g_ulStartTime = zztest_ms();
}

//------------------------------------------------------------------------------

int RUN_TESTS_RESULT(void)
{
    unsigned long endms = zztest_ms();

    ZPRINTF_("[----------] Global test environment tear-down.\n");
    ZPRINTF_("[==========] %lu tests from %lu test suites ran. (%lu ms total)\n", g_ulPassed + g_ulFailed, g_ulSuites,
             endms - g_ulStartTime);
    ZPRINTF_("[  PASSED  ] %lu tests.\n", g_ulPassed);

    if (g_ulSkipped != 0)
    {
        unsigned long i;

        ZPRINTF_("[  SKIPPED ] %lu tests, listed below:\n", g_ulSkipped);
        for (i = 0; i < g_ulSkipped; i++)
        {
            ZPRINTF_("[  SKIPPED ] %s\n", g_nszSkipped[i]);
        }
    }

    if (g_ulFailed != 0)
    {
        unsigned long i;

        ZPRINTF_("[  FAILED  ] %lu tests, listed below:\n", g_ulFailed);
        for (i = 0; i < g_ulFailed; i++)
        {
            ZPRINTF_("[  FAILED  ] %s\n", g_nszFailed[i]);
        }
    }

    zztest_cleanup();
    return g_ulFailed == 0 ? 0 : 1;
}

#endif // defined(ZZTEST_IMPLEMENTATION)
#endif // !defined(INCLUDE_ZZTEST_H)
