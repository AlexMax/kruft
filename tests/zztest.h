//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(INCLUDE_ZZTEST_H)
#define INCLUDE_ZZTEST_H

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
 * @brief Define a test
 *
 * @param s Test suite.  Must be valid identifier.
 * @param t Test name.  Must be valid identifier.
 */
#define TEST(s, t) void zztest__##s##__##t(struct zztest_state_s *zztest_state)

/**
 * @brief Expect boolean equality.
 */
#define EXPECT_TRUE(l, r)                                                                                              \
    {                                                                                                                  \
        (void)zztest_state;                                                                                            \
        if (!!l != !!r)                                                                                                \
        {                                                                                                              \
            zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "!!" #l " != !!" #r);                  \
            return;                                                                                                    \
        }                                                                                                              \
    }

/**
 * @brief Expect boolean inequality.
 */
#define EXPECT_FALSE(l, r)                                                                                             \
    {                                                                                                                  \
        (void)zztest_state;                                                                                            \
        if (!!l == !!r)                                                                                                \
        {                                                                                                              \
            zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "!!" #l " == !!" #r);                  \
            return;                                                                                                    \
        }                                                                                                              \
    }

/**
 * @brief Expect exact equality.
 */
#define EXPECT_EQ(l, r)                                                                                                \
    {                                                                                                                  \
        (void)zztest_state;                                                                                            \
        if (l != r)                                                                                                    \
        {                                                                                                              \
            zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, #l " != " #r);                         \
            return;                                                                                                    \
        }                                                                                                              \
    }

/**
 * @brief Expect string equality.
 */
#define EXPECT_STREQ(l, r)                                                                                             \
    {                                                                                                                  \
        (void)zztest_state;                                                                                            \
        if (strcmp(l, r) != 0)                                                                                         \
        {                                                                                                              \
            zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "0 != strcmp(" #l ", " #r ")");        \
            return;                                                                                                    \
        }                                                                                                              \
    }

/**
 * @brief Signal success.
 */
#define SUCCEED()                                                                                                      \
    {                                                                                                                  \
        zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_SUCCESS, NULL);                                  \
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
 * @brief Add a failure, without a return.
 */
#define ADD_FAILURE()                                                                                                  \
    {                                                                                                                  \
        zztest_result(zztest_state, __FILE__, __LINE__, ZZTEST_RESULT_FAIL, "Failure");                                \
    }

/**
 * @brief Define an array of tests.
 */
#define EXPORT_TEST_SUITE(s) struct zztest_s zztest_suite__##s[]

/**
 * @brief A pointer to a test function.
 */
#define EXPORT_TEST(s, t) {&zztest__##s##__##t, #s, #s "." #t}

/**
 * @brief Define a count of how many tests we have.
 */
#define EXPORT_TEST_SUITE_COUNT(s)                                                                                     \
    unsigned long zztest_suite_count__##s = sizeof(zztest_suite__##s) / sizeof(struct zztest_s)

/**
 * @brief Run a test suite.  Call this from main().
 */
#define RUN_TEST_SUITE(s) zztest_suite_run(#s, &zztest_suite__##s[0], zztest_suite_count__##s);

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

#include <stdio.h>
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

//------------------------------------------------------------------------------

static void zztest_cleanup(void)
{
    free(g_nszFailed);
    free(g_nszSkipped);
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
        printf("%s(%lu): error: %s\n\n", file, line, msgstr);
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
    printf("[----------] %lu tests from %s\n", count, name);

    unsigned i;
    for (i = 0; i < count; i++)
    {
        struct zztest_s *test = &tests[i];

        printf("[ RUN      ] %s\n", test->test_name);

        struct zztest_state_s state;
        state.test = test;
        state.failed = 0;
        state.skipped = 0;
        test->func(&state);

        if (state.failed > 0)
        {
            printf("[  FAILED  ] %s (0 ms)\n", test->test_name);

            const char **failed = (const char **)realloc(g_nszFailed, sizeof(char *) * (g_ulFailed + 1));
            if (failed == NULL)
            {
                printf("realloc failure\n");
                zztest_cleanup();
                exit(1);
            }

            g_nszFailed = failed;
            g_nszFailed[g_ulFailed] = test->test_name;
            g_ulFailed += 1;
        }
        else if (state.skipped > 0)
        {
            printf("[  SKIPPED ] %s (0 ms)\n", test->test_name);

            const char **skipped = (const char **)realloc(g_nszSkipped, sizeof(char *) * (g_ulSkipped + 1));
            if (skipped == NULL)
            {
                printf("realloc failure\n");
                zztest_cleanup();
                exit(1);
            }

            g_nszSkipped = skipped;
            g_nszSkipped[g_ulSkipped] = test->test_name;
            g_ulSkipped += 1;
        }
        else
        {
            printf("[       OK ] %s (0 ms)\n", test->test_name);
            g_ulPassed += 1;
        }
    }

    printf("[----------] %lu tests from %s (%lu ms total)\n\n", count, name, 0);
}

//------------------------------------------------------------------------------

void RUN_TESTS(void)
{
    printf("[----------] Global test environment set-up.\n");

    g_ulPassed = 0;
    g_ulFailed = 0;
    g_ulSkipped = 0;
    g_ulSuites = 0;
    g_nszFailed = NULL;
    g_nszSkipped = NULL;
}

//------------------------------------------------------------------------------

int RUN_TESTS_RESULT(void)
{
    printf("[----------] Global test environment tear-down.\n");
    printf("[==========] %lu tests from %lu test suites ran. (%lu ms total)\n", g_ulPassed + g_ulFailed, g_ulSuites, 0);
    printf("[  PASSED  ] %lu tests.\n", g_ulPassed);

    if (g_ulSkipped != 0)
    {
        unsigned long i;

        printf("[  SKIPPED ] %lu tests, listed below:\n", g_ulSkipped);
        for (i = 0; i < g_ulSkipped; i++)
        {
            printf("[  SKIPPED ] %s\n", g_nszSkipped[i]);
        }
    }

    if (g_ulFailed != 0)
    {
        unsigned long i;

        printf("[  FAILED  ] %lu tests, listed below:\n", g_ulFailed);
        for (i = 0; i < g_ulFailed; i++)
        {
            printf("[  FAILED  ] %s\n", g_nszFailed[i]);
        }
    }

    zztest_cleanup();
    return g_ulFailed == 0;
}

#endif // defined(ZZTEST_IMPLEMENTATION)
#endif // !defined(INCLUDE_ZZTEST_H)
