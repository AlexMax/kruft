//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

//
// zztest - A greenfield subset of Google Test for crufty compilers.
//
// Important defines:
// - ZZTEST_IMPLEMENTATION: You must define this before including zztest.h
//                          in a single file, otherwise internal functions
//                          will be missing their implementation.
// - ZZTEST_SELFCHECK: Define this before including zztest.h to create a
//                     self-contained program that shows output of sample
//                     tests.  Useful to sanity check your environment.
// - ZZTEST_CONFIG_PRINTF: Define this to your own print function.
//

#if !defined(INCLUDE_ZZTEST_H)
#define INCLUDE_ZZTEST_H

#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS // Say the line, Bart!
#endif

#if defined(ZZTEST_CONFIG_PRINTF)
#define ZZT_PRINTF ZZTEST_CONFIG_PRINTF
#else
#define ZZT_PRINTF printf
#endif

#include <limits.h>

// Boolean datatype.
typedef int ZZT_BOOL;
#define ZZT_FALSE (0)
#define ZZT_TRUE (1)

// Determine our 64-bit data type.
#if defined(ULLONG_MAX) // C99
#if (ULLONG_MAX == 0xFFFFFFFFFFFFFFFFull)
#define ZZT_64BIT_LL_
#endif
#elif defined(ULONG_LONG_MAX) // GNU
#if (ULONG_LONG_MAX == 0xFFFFFFFFFFFFFFFFull)
#define ZZT_64BIT_LL_
#endif
#endif
#if defined(ZZT_64BIT_LL_)
#define ZZTEST_HAS_64BIT (1)
typedef long long ZZT_INT64;
typedef unsigned long long ZZT_UINT64;
#define ZZT_PRIi64 "lld"
#define ZZT_PRIu64 "llu"
#define ZZT_PRIx64 "llx"
#undef ZZT_64BIT_LL_
#elif defined(_UI64_MAX) // MSVC
#define ZZTEST_HAS_64BIT (1)
typedef __int64 ZZT_INT64;
typedef unsigned __int64 ZZT_UINT64;
#define ZZT_PRIi64 "I64d"
#define ZZT_PRIu64 "I64u"
#define ZZT_PRIx64 "I64x"
#else
#define ZZTEST_HAS_64BIT (0)
#endif

enum zzt_fmt_e
{
    ZZT_FMT_BOOL,
    ZZT_FMT_CHAR,
    ZZT_FMT_LONG,
    ZZT_FMT_ULONG,
    ZZT_FMT_XLONG,
    ZZT_FMT_I64,
    ZZT_FMT_UI64,
    ZZT_FMT_XI64,
    ZZT_FMT_STR,
};

struct zzt_test_state_s;

enum zzt_result_e
{
    ZZT_RESULT_SUCCESS,
    ZZT_RESULT_FAIL,
    ZZT_RESULT_SKIP,
};

typedef void (*zzt_testfunc)(struct zzt_test_state_s *);

struct zzt_test_s
{
    zzt_testfunc func;
    const char *suite_name;
    const char *test_name;
    struct zzt_test_s *next;
    struct zzt_test_s *next_skip;
    struct zzt_test_s *next_fail;
};

struct zzt_test_suite_s
{
    struct zzt_test_s *head;
    struct zzt_test_s *tail;
    const char *suite_name;
    unsigned long tests_count;
    struct zzt_test_suite_s *next;
};

/**
 * @brief Function name of a test suite.
 */
#define ZZT_SUITENAME(s) s##__SUITE

/**
 * @brief Symbol name of test suite info.
 */
#define ZZT_SUITEINFO(s) s##__SINFO

/**
 * @brief Function name of a test.
 */
#define ZZT_TESTNAME(s, t) s##__##t##__TEST

/**
 * @brief Symbol name of test info.
 */
#define ZZT_TESTINFO(s, t) s##__##t##__INFO

/**
 * @brief Define a test suite.
 *
 * @param s Test suite.  Must be valid identifier.
 */
#define SUITE(s)                                                                                                       \
    static struct zzt_test_suite_s ZZT_SUITEINFO(s);                                                                   \
    void ZZT_SUITENAME(s)(void)

/**
 * @brief Define a test.
 *
 * @param s Test suite.  Must be valid identifier.
 * @param t Test name.  Must be valid identifier.
 */
#define TEST(s, t)                                                                                                     \
    void ZZT_TESTNAME(s, t)(struct zzt_test_state_s * zzt_test_state);                                                 \
    static struct zzt_test_s ZZT_TESTINFO(s, t) = {ZZT_TESTNAME(s, t), #s, #s "." #t, NULL, NULL, NULL};               \
    void ZZT_TESTNAME(s, t)(struct zzt_test_state_s * zzt_test_state)

#define SUITE_TEST(s, t)                                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        struct zzt_test_suite_s *suite = &ZZT_SUITEINFO(s);                                                            \
        if (suite->head == NULL)                                                                                       \
        {                                                                                                              \
            suite->suite_name = #s;                                                                                    \
            suite->head = &ZZT_TESTINFO(s, t);                                                                         \
            suite->tail = suite->head;                                                                                 \
            suite->tests_count = 1;                                                                                    \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            suite->tail->next = &ZZT_TESTINFO(s, t);                                                                   \
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
            zzt_result(zzt_test_state, __FILE__, __LINE__, ZZT_RESULT_FAIL,                                            \
                       "Value of: " #t "\n  Actual: false\nExpected: true");                                           \
        }                                                                                                              \
    }

/**
 * @brief Expect inequality.
 */
#define EXPECT_FALSE(t)                                                                                                \
    {                                                                                                                  \
        if ((t))                                                                                                       \
        {                                                                                                              \
            zzt_result(zzt_test_state, __FILE__, __LINE__, ZZT_RESULT_FAIL,                                            \
                       "Value of: " #t "\n  Actual: true\nExpected: false");                                           \
        }                                                                                                              \
    }

/**
 * @brief Expect boolean equality.
 */
#define EXPECT_BOOLEQ(l, r)                                                                                            \
    {                                                                                                                  \
        int ll = (l) ? 1 : 0, rr = (r) ? 1 : 0;                                                                        \
        zzt_eq(zzt_test_state, ZZT_FMT_BOOL, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
    }

/**
 * @brief Expect char equality.
 */
#define EXPECT_CHAREQ(l, r)                                                                                            \
    {                                                                                                                  \
        char ll = l, rr = r;                                                                                           \
        zzt_eq(zzt_test_state, ZZT_FMT_CHAR, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
    }

/**
 * @brief Expect exact integer equality.
 */
#define EXPECT_INTEQ(l, r)                                                                                             \
    {                                                                                                                  \
        long ll = l, rr = r;                                                                                           \
        zzt_eq(zzt_test_state, ZZT_FMT_LONG, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
    }

/**
 * @brief Expect exact integer equality.
 */
#define EXPECT_UINTEQ(l, r)                                                                                            \
    {                                                                                                                  \
        long ll = l, rr = r;                                                                                           \
        zzt_eq(zzt_test_state, ZZT_FMT_ULONG, &ll, &rr, #l, #r, __FILE__, __LINE__);                                   \
    }

/**
 * @brief Expect exact integer equality, failures are shown in hex.
 */
#define EXPECT_XINTEQ(l, r)                                                                                            \
    {                                                                                                                  \
        long ll = l, rr = r;                                                                                           \
        zzt_eq(zzt_test_state, ZZT_FMT_XLONG, &ll, &rr, #l, #r, __FILE__, __LINE__);                                   \
    }

/**
 * @brief Expect exact 64-bit integer equality.
 */
#define EXPECT_INT64EQ(l, r)                                                                                           \
    {                                                                                                                  \
        ZZT_INT64 ll = l, rr = r;                                                                                      \
        zzt_eq(zzt_test_state, ZZT_FMT_I64, &ll, &rr, #l, #r, __FILE__, __LINE__);                                     \
    }

/**
 * @brief Expect exact 64-bit integer equality.
 */
#define EXPECT_UINT64EQ(l, r)                                                                                          \
    {                                                                                                                  \
        ZZT_UINT64 ll = l, rr = r;                                                                                     \
        zzt_eq(zzt_test_state, ZZT_FMT_UI64, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
    }

/**
 * @brief Expect exact 64-bit integer equality, failures are shown in hex.
 */
#define EXPECT_XINT64EQ(l, r)                                                                                          \
    {                                                                                                                  \
        ZZT_UINT64 ll = l, rr = r;                                                                                     \
        zzt_eq(zzt_test_state, ZZT_FMT_XI64, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
    }

#if (ZZTEST_HAS_64BIT)
#define EXPECT_IMAXEQ EXPECT_INT64EQ
#define EXPECT_UIMAXEQ EXPECT_UINT64EQ
#define EXPECT_SIZEEQ EXPECT_UINT64EQ
#define EXPECT_ISIZEEQ EXPECT_INT64EQ
#else
#define EXPECT_IMAXEQ EXPECT_INTEQ
#define EXPECT_UIMAXEQ EXPECT_UINTEQ
#define EXPECT_SIZEEQ EXPECT_UINTEQ
#define EXPECT_ISIZEEQ EXPECT_INTEQ
#endif

/**
 * @brief Expect string equality.
 */
#define EXPECT_STREQ(l, r)                                                                                             \
    {                                                                                                                  \
        const char *ll = l, *rr = r;                                                                                   \
        zzt_eq(zzt_test_state, ZZT_FMT_STR, (const void *)ll, (const void *)rr, #l, #r, __FILE__, __LINE__);           \
    }

/**
 * @brief Add a failure, without a return.
 */
#define ADD_FAILURE()                                                                                                  \
    {                                                                                                                  \
        zzt_result(zzt_test_state, __FILE__, __LINE__, ZZT_RESULT_FAIL, "Failure");                                    \
    }

/**
 * @brief Signal failure.
 */
#define FAIL()                                                                                                         \
    {                                                                                                                  \
        zzt_result(zzt_test_state, __FILE__, __LINE__, ZZT_RESULT_FAIL, "Failure");                                    \
        return;                                                                                                        \
    }

/**
 * @brief Signal skip.
 */
#define SKIP()                                                                                                         \
    {                                                                                                                  \
        zzt_result(zzt_test_state, __FILE__, __LINE__, ZZT_RESULT_SKIP, NULL);                                         \
        return;                                                                                                        \
    }

/**
 * @brief Add suite of tests to be run when RUN_TESTS is called.
 */
#define ADD_TEST_SUITE(s)                                                                                              \
    {                                                                                                                  \
        ZZT_SUITENAME(s)();                                                                                            \
        zzt_add_test_suite(&ZZT_SUITEINFO(s));                                                                         \
    }

/**
 * @brief Run all tests and return code which can be returned from main().
 */
#define RUN_TESTS() (zzt_run_all())

int zzt_strcmp(const char *lhs, const char *rhs);
ZZT_BOOL zzt_eq(struct zzt_test_state_s *state, enum zzt_fmt_e fmt, const void *l, const void *r, const char *ls,
                const char *rs, const char *file, unsigned long line);
void zzt_result(struct zzt_test_state_s *state, const char *file, unsigned long line, enum zzt_result_e msg,
                const char *msgstr);
void zzt_add_test_suite(struct zzt_test_suite_s *suite);
int zzt_run_all(void);

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

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define ZZTLOG_H1 "[==========]"
#define ZZTLOG_H2 "[----------]"
#define ZZTLOG_RUN "[ RUN      ]"
#define ZZTLOG_OK "[       OK ]"
#define ZZTLOG_SKIPPED "[  SKIPPED ]"
#define ZZTLOG_FAILED "[  FAILED  ]"
#define ZZTLOG_PASSED "[  PASSED  ]"

//------------------------------------------------------------------------------

struct zzt_test_state_s
{
    struct zzt_test_s *test;
    int failed;
    int skipped;
};

static unsigned long g_testsCount;
static struct zzt_test_suite_s *g_suitesHead;
static struct zzt_test_suite_s *g_suitesTail;
static unsigned long g_suitesCount;
static struct zzt_test_s *g_testFailHead;
static struct zzt_test_s *g_testFailTail;
static struct zzt_test_s *g_testSkipHead;
static struct zzt_test_s *g_testSkipTail;

/**
 * @brief Return time point with ms resolution.
 *
 * @details This is a compatible timer, not an accurate one.  We're making
 *          a test suite, not a benchmark.
 */
static unsigned long zzt_ms(void)
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
 * @brief Use the safest vsprintf we have available.
 *
 * @param buf Buffer to write to.
 * @param buflen Length of buffer.
 * @param fmt Format string.
 * @param ... Format parameters.
 */
static void zzt_sprintf(char *buf, unsigned buflen, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

#if defined(__GNUC__)
    vsnprintf(buf, buflen, fmt, args);
#elif defined(_MSC_VER) // FIXME: When was this added?
    _vsnprintf(buf, buflen, fmt, args);
    buf[buflen - 1] = '\0';
#else
    (void)buflen;
    vsprintf(buf, fmt, args);
#endif

    va_end(args);
}

/**
 * @brief Turn a string into a typical quoted string literal.
 *
 * @param buf Buffer to write to.
 * @param buflen Length of destination buffer.
 * @param str Input string to convert.
 */
static void zzt_stringify(char *buf, unsigned long buflen, const char *str)
{
    ZZT_BOOL partial = ZZT_FALSE;
    const char *cur = str;
    char *w = buf;
    char *end = buf + buflen;
#define REMAIN_() (end - w)
#define WRITE_(c) (*w++ = (c))

    if (buflen == 0)
    {
        return;
    }
    else if (REMAIN_() < 5) // Needs to contain at least "...\0
    {
        WRITE_('\0');
        return;
    }

    WRITE_('\"');
    while (*cur != '\0')
    {
        if (*cur == '\t' || *cur == '\n' || *cur == '\r' || *cur == '\\')
        {
            if (REMAIN_() < 3)
            {
                partial = ZZT_TRUE;
                break;
            }

            WRITE_('\\');
            if (*cur == '\t')
            {
                WRITE_('t');
            }
            else if (*cur == '\n')
            {
                WRITE_('n');
            }
            else if (*cur == '\r')
            {
                WRITE_('r');
            }
            else if (*cur == '\\')
            {
                WRITE_('\\');
            }
        }
        else if (*cur >= ' ' && *cur <= '~')
        {
            if (REMAIN_() < 2)
            {
                partial = ZZT_TRUE;
                break;
            }
            WRITE_(*cur);
        }
        else
        {
            if (REMAIN_() < 5)
            {
                partial = ZZT_TRUE;
                break;
            }

            zzt_sprintf(w, 5, "\\x%02x", ((unsigned)*cur) & 0xFF);
            w += 4;
        }

        cur += 1;
    }

    if (partial)
    {
        w = end - 5;
        WRITE_('.');
        WRITE_('.');
        WRITE_('.');
        WRITE_('\0');
        return;
    }

    WRITE_('\"');
    WRITE_('\0');
#undef REMAIN_
}

/**
 * @brief Print a value based on its desired format.
 *
 * @param fmt Format type.
 * @param v Pointer to underlying value.
 * @param vs String representation of value.
 */
static void zzt_printv(enum zzt_fmt_e fmt, const void *v, const char *vs)
{
    char buffer[64];

    switch (fmt)
    {
    case ZZT_FMT_BOOL: {
        const int boolean = *((int *)v);
        if (boolean)
        {
            zzt_sprintf(buffer, sizeof(buffer), "true");
        }
        else
        {
            zzt_sprintf(buffer, sizeof(buffer), "false");
        }
        break;
    }
    case ZZT_FMT_CHAR: {
        const char ch = *((char *)v);
        if (ch == '\0')
        {
            zzt_sprintf(buffer, sizeof(buffer), "'\\0'", ch);
        }
        else if (ch == '\t')
        {
            zzt_sprintf(buffer, sizeof(buffer), "'\\t'", ch);
        }
        else if (ch == '\n')
        {
            zzt_sprintf(buffer, sizeof(buffer), "'\\n'", ch);
        }
        else if (ch == '\r')
        {
            zzt_sprintf(buffer, sizeof(buffer), "'\\r'", ch);
        }
        else if (ch == '\\')
        {
            zzt_sprintf(buffer, sizeof(buffer), "'\\\\'", ch);
        }
        else if (ch >= ' ' && ch <= '~')
        {
            zzt_sprintf(buffer, sizeof(buffer), "'%c'", ch);
        }
        else
        {
            zzt_sprintf(buffer, sizeof(buffer), "'\\x%02x'", ((unsigned)ch) & 0xFF);
        }
        break;
    }
    case ZZT_FMT_LONG:
        zzt_sprintf(buffer, sizeof(buffer), "%ld", *((long *)v));
        break;
    case ZZT_FMT_ULONG:
        zzt_sprintf(buffer, sizeof(buffer), "%lu", *((unsigned long *)v));
        break;
    case ZZT_FMT_XLONG:
        zzt_sprintf(buffer, sizeof(buffer), "0x%lx", *((unsigned long *)v));
        break;
#if (ZZTEST_HAS_64BIT)
    case ZZT_FMT_I64:
        zzt_sprintf(buffer, sizeof(buffer), "%" ZZT_PRIi64, *((ZZT_INT64 *)v));
        break;
    case ZZT_FMT_UI64:
        zzt_sprintf(buffer, sizeof(buffer), "%" ZZT_PRIu64, *((ZZT_UINT64 *)v));
        break;
    case ZZT_FMT_XI64:
        zzt_sprintf(buffer, sizeof(buffer), "0x%" ZZT_PRIx64, *((ZZT_UINT64 *)v));
        break;
#endif // (ZZT_HAS_64BIT)
    case ZZT_FMT_STR:
        zzt_stringify(buffer, sizeof(buffer), (const char *)v);
        break;
    default:
        return;
    }

    ZZT_PRINTF("  %s\n", vs);
    if (strcmp(buffer, vs))
    {
        ZZT_PRINTF("    Which is: %s\n", buffer);
    }
}

/**
 * @brief Add a test to our list of failed tests.
 */
static void zzt_add_fail(struct zzt_test_s *test)
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
static void zzt_add_skip(struct zzt_test_s *test)
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

int zzt_strcmp(const char *lhs, const char *rhs)
{
    return strcmp(lhs, rhs);
}

//------------------------------------------------------------------------------

ZZT_BOOL zzt_eq(struct zzt_test_state_s *state, enum zzt_fmt_e fmt, const void *l, const void *r, const char *ls,
                const char *rs, const char *file, unsigned long line)
{
    ZZT_BOOL isEqual = ZZT_FALSE;

    if (fmt == ZZT_FMT_BOOL)
    {
        isEqual = *((int *)l) == *((int *)r);
    }
    else if (fmt == ZZT_FMT_CHAR)
    {
        isEqual = *((char *)l) == *((char *)r);
    }
    else if (fmt == ZZT_FMT_LONG)
    {
        isEqual = *((long *)l) == *((long *)r);
    }
    else if (fmt == ZZT_FMT_ULONG || fmt == ZZT_FMT_XLONG)
    {
        isEqual = *((unsigned long *)l) == *((unsigned long *)r);
    }
#if (ZZTEST_HAS_64BIT)
    else if (fmt == ZZT_FMT_I64)
    {
        isEqual = *((ZZT_INT64 *)l) == *((ZZT_INT64 *)r);
    }
    else if (fmt == ZZT_FMT_UI64 || fmt == ZZT_FMT_XI64)
    {
        isEqual = *((ZZT_UINT64 *)l) == *((ZZT_UINT64 *)r);
    }
#endif // (ZZT_HAS_64BIT)
    else if (fmt == ZZT_FMT_STR)
    {
        isEqual = strcmp((const char *)l, (const char *)r) == 0;
    }
    else
    {
        return ZZT_FALSE;
    }

    if (isEqual)
    {
        state->failed = 0;
        state->skipped = 0;
        return ZZT_TRUE;
    }

    state->failed += 1;

    ZZT_PRINTF("%s(%lu): error: Expected equality of these values:\n", file, line);
    zzt_printv(fmt, l, ls);
    zzt_printv(fmt, r, rs);
    puts("");

    return ZZT_FALSE;
}

//------------------------------------------------------------------------------

void zzt_result(struct zzt_test_state_s *state, const char *file, unsigned long line, enum zzt_result_e msg,
                const char *msgstr)
{
    switch (msg)
    {
    case ZZT_RESULT_SUCCESS:
        state->failed = 0;
        state->skipped = 0;
        break;
    case ZZT_RESULT_FAIL:
        ZZT_PRINTF("%s(%lu): error: %s\n\n", file, line, msgstr);
        state->failed += 1;
        break;
    case ZZT_RESULT_SKIP:
        state->skipped += 1;
        break;
    }
}

//------------------------------------------------------------------------------

void zzt_add_test_suite(struct zzt_test_suite_s *suite)
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

int zzt_run_all(void)
{
    unsigned long passed = 0, failed = 0, skipped = 0;
    unsigned long startAllMs = 0, allMs = 0;
    struct zzt_test_suite_s *suite = g_suitesHead;
    struct zzt_test_s *test = NULL;

#if defined(_WIN32)
    // Set timer resolution to 1ms.
    timeBeginPeriod(1);
#endif

    ZZT_PRINTF(ZZTLOG_H1 " Running %lu tests from %lu test suites.\n", g_testsCount, g_suitesCount);
    startAllMs = zzt_ms();

    for (; suite; suite = suite->next)
    {
        unsigned long startSuiteMs = 0, suiteMs = 0;

        ZZT_PRINTF(ZZTLOG_H2 " %lu tests from %s\n", suite->tests_count, suite->suite_name);
        startSuiteMs = zzt_ms();

        test = suite->head;
        for (; test; test = test->next)
        {
            const char *result = "";
            unsigned long startTestMs = 0, testMs = 0;
            struct zzt_test_state_s state;

            ZZT_PRINTF(ZZTLOG_RUN " %s\n", test->test_name);
            state.test = test;
            state.failed = 0;
            state.skipped = 0;

            startTestMs = zzt_ms();
            test->func(&state);
            testMs = zzt_ms() - startTestMs;

            if (state.failed != 0)
            {
                result = ZZTLOG_FAILED;
                zzt_add_fail(test);
                failed += 1;
            }
            else if (state.skipped != 0)
            {
                result = ZZTLOG_SKIPPED;
                zzt_add_skip(test);
                skipped += 1;
            }
            else
            {
                result = ZZTLOG_OK;
                passed += 1;
            }

            if (testMs)
            {
                ZZT_PRINTF("%s %s (%lu ms)\n", result, test->test_name, testMs);
            }
            else
            {
                ZZT_PRINTF("%s %s\n", result, test->test_name);
            }
        }

        suiteMs = zzt_ms() - startSuiteMs;
        if (suiteMs)
        {
            ZZT_PRINTF(ZZTLOG_H2 " %lu tests from %s (%lu ms total)\n\n", suite->tests_count, suite->suite_name,
                       suiteMs);
        }
        else
        {
            ZZT_PRINTF(ZZTLOG_H2 " %lu tests from %s\n\n", suite->tests_count, suite->suite_name);
        }
    }

    allMs = zzt_ms() - startAllMs;
    if (allMs)
    {
        ZZT_PRINTF(ZZTLOG_H1 " %lu tests from %lu test suites ran. (%lu ms total)\n", g_testsCount, g_suitesCount,
                   allMs);
    }
    else
    {
        ZZT_PRINTF(ZZTLOG_H1 " %lu tests from %lu test suites ran.\n", g_testsCount, g_suitesCount);
    }

    ZZT_PRINTF(ZZTLOG_PASSED " %lu tests.\n", passed);

    if (skipped != 0)
    {
        ZZT_PRINTF(ZZTLOG_SKIPPED " %lu tests, listed below:\n", skipped);

        test = g_testSkipHead;
        for (; test; test = test->next_skip)
        {
            ZZT_PRINTF(ZZTLOG_SKIPPED " %s\n", test->test_name);
        }
    }

    if (failed != 0)
    {
        ZZT_PRINTF(ZZTLOG_FAILED " %lu tests, listed below:\n", failed);

        test = g_testFailHead;
        for (; test; test = test->next_fail)
        {
            ZZT_PRINTF(ZZTLOG_FAILED " %s\n", test->test_name);
        }
    }

    return 0;
}

#if defined(ZZTEST_SELFCHECK)

TEST(zztest, passing)
{
    EXPECT_TRUE(1 == 1);
    EXPECT_FALSE(1 != 1);
    EXPECT_BOOLEQ(1, 2);
    EXPECT_CHAREQ('a', 'a');
    EXPECT_STREQ("foo", "foo");
}

TEST(zztest, passing_int)
{
    EXPECT_INTEQ(1, 1);
    EXPECT_UINTEQ(1, 1);
    EXPECT_XINTEQ(1, 1);
#if (ZZTEST_HAS_64BIT)
    EXPECT_INT64EQ(1, 1);
    EXPECT_UINT64EQ(1, 1);
    EXPECT_XINT64EQ(1, 1);
#endif
    EXPECT_IMAXEQ(1, 1);
    EXPECT_UIMAXEQ(1, 1);
    EXPECT_SIZEEQ(1, 1);
    EXPECT_ISIZEEQ(1, 1);
}

TEST(zztest, failing)
{
    EXPECT_TRUE(1 == 2);
    EXPECT_FALSE(1 != 2);
    EXPECT_BOOLEQ(1, 0);
    ADD_FAILURE();
}

TEST(zztest, failing_char)
{
    EXPECT_CHAREQ('a', 'b');
    EXPECT_CHAREQ('\0', '\xaa');
    EXPECT_CHAREQ('\n', '\r');
    EXPECT_CHAREQ('\t', '\\');
    EXPECT_CHAREQ(0x61, 0x62);
    EXPECT_CHAREQ(0x00, (char)0xaa);
    EXPECT_CHAREQ(0x0a, 0x0d);
    EXPECT_CHAREQ(0x09, 0x5c);
}

TEST(zztest, failing_int)
{
    EXPECT_INTEQ(1, (int)2);
    EXPECT_UINTEQ(1, 2u);
    EXPECT_XINTEQ(0xabc, 0x0DEF);
#if (ZZTEST_HAS_64BIT)
    EXPECT_INT64EQ(1, (int)2);
    EXPECT_UINT64EQ(1, 2u);
    EXPECT_XINT64EQ(0xabc, 0x0DEF);
#endif
    EXPECT_IMAXEQ(1, (int)2);
    EXPECT_UIMAXEQ(1, 2u);
    EXPECT_SIZEEQ(1, 2u);
    EXPECT_ISIZEEQ(1, (int)2);
}

TEST(zztest, failing_str)
{
    EXPECT_STREQ("foo", "bar");
    EXPECT_STREQ("\r\n", "\t\\");
    EXPECT_STREQ("f\x6F\x6F", "b\x61r");
    EXPECT_STREQ("", "The quick brown fox jumps over the lazy dog.\nLorem ipsum dolor sit amet.");
}

TEST(zztest, skipping)
{
    SKIP();
}

TEST(zztest, skipping2)
{
    SKIP();
}

SUITE(zztest)
{
    SUITE_TEST(zztest, passing);
    SUITE_TEST(zztest, passing_int);
    SUITE_TEST(zztest, failing);
    SUITE_TEST(zztest, failing_char);
    SUITE_TEST(zztest, failing_int);
    SUITE_TEST(zztest, failing_str);
    SUITE_TEST(zztest, skipping);
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
