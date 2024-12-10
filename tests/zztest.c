//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "zztest.h"

#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------------

struct zz_test_state_s
{
    struct zz_test_s *test;
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

static void zz_test_cleanup(void)
{
    free(g_nszFailed);
    free(g_nszSkipped);
}

//------------------------------------------------------------------------------

void zz_test_result(struct zz_test_state_s *state, const char *file, unsigned long line, enum zz_test_result_e msg,
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

void zz_test_suite_run(const char *name, struct zz_test_s *tests, unsigned long count)
{
    printf("[----------] %lu tests from %s\n", count, name);

    unsigned i;
    for (i = 0; i < count; i++)
    {
        struct zz_test_s *test = &tests[i];

        printf("[ RUN      ] %s\n", test->test_name);

        struct zz_test_state_s state;
        state.test = test;
        state.failed = 0;
        state.skipped = 0;
        test->func(&state);

        if (state.failed > 0)
        {
            printf("[  FAILED  ] %s (0 ms)\n", test->test_name);

            char **failed = realloc(g_nszFailed, sizeof(char *) * (g_ulFailed + 1));
            if (failed == NULL)
            {
                printf("realloc failure\n");
                zz_test_cleanup();
                exit(1);
            }

            g_nszFailed = failed;
            g_nszFailed[g_ulFailed] = test->test_name;
            g_ulFailed += 1;
        }
        else if (state.skipped > 0)
        {
            printf("[  SKIPPED ] %s (0 ms)\n", test->test_name);

            char **skipped = realloc(g_nszSkipped, sizeof(char *) * (g_ulSkipped + 1));
            if (skipped == NULL)
            {
                printf("realloc failure\n");
                zz_test_cleanup();
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

    zz_test_cleanup();
    return g_ulFailed == 0;
}
