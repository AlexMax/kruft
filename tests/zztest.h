/*
 * zztest - A test framework for crufty compilers.
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

/*
 * ABOUT
 *  zztest is a test framework for crufty compilers.
 *
 * COMPILER SUPPORT
 *  - Modern GCC, Clang, MSVC
 *  - Microsoft Visual C++ 6.0
 *  - Borland C++ 3.1 (DOS)
 *  - Watcom C 9.01 (DOS)
 *
 * Important defines:
 *  ZZTEST_IMPLEMENTATION: You must define this before including zztest.h
 *                         in a single file, otherwise internal functions
 *                         will be missing their implementation.
 *  ZZTEST_SELFCHECK: Define this before including zztest.h to create a
 *                    self-contained program that shows output of sample
 *                    tests.  Useful to sanity check your environment.
 *  ZZTEST_CONFIG_PRINTF: Define this to your own print function.
 */

#if !defined(INCLUDE_ZZTEST_H)
#define INCLUDE_ZZTEST_H

#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS /* Say the line, Bart! */
#endif

#if defined(ZZTEST_CONFIG_PRINTF)
#define ZZT_PRINTF ZZTEST_CONFIG_PRINTF
#else
#define ZZT_PRINTF printf
#endif

#include <limits.h>
#include <stddef.h>

/* Boolean datatype. */
typedef int ZZT_BOOL;
#define ZZT_FALSE (0)
#define ZZT_TRUE (1)

/* Determine our 64-bit data type. */
#if defined(ULLONG_MAX) /* C99 */
#if (ULLONG_MAX == 0xFFFFFFFFFFFFFFFF)
#define ZZT_HAS_LONGLONG_
#endif
#elif defined(ULONG_LONG_MAX) /* GNU */
#if (ULONG_LONG_MAX == 0xFFFFFFFFFFFFFFFF)
#define ZZT_HAS_LONGLONG_
#endif
#endif
#if defined(ZZT_HAS_LONGLONG_)
typedef long long ZZT_INTMAX;
typedef unsigned long long ZZT_UINTMAX;
#define ZZT_PRIiMAX "lld"
#define ZZT_PRIuMAX "llu"
#define ZZT_PRIxMAX "llx"
#elif defined(_UI64_MAX) /* MSVC */
typedef __int64 ZZT_INTMAX;
typedef unsigned __int64 ZZT_UINTMAX;
#define ZZT_PRIiMAX "I64d"
#define ZZT_PRIuMAX "I64u"
#define ZZT_PRIxMAX "I64x"
#else
typedef long ZZT_INTMAX;
typedef unsigned long ZZT_UINTMAX;
#define ZZT_PRIiMAX "ld"
#define ZZT_PRIuMAX "lu"
#define ZZT_PRIxMAX "lx"
#endif

enum zzt_fmt_e
{
    ZZT_FMT_BOOL,
    ZZT_FMT_CHAR,
    ZZT_FMT_INT,
    ZZT_FMT_UINT,
    ZZT_FMT_XINT,
    ZZT_FMT_STR,
};

struct zzt_test_state_s;

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
#define ZZT_TESTINFO(s, t) s##__##t##__TINFO

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
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(t))                                                                                                      \
        {                                                                                                              \
            zzt_fail(zzt_test_state, __FILE__, __LINE__, "Value of: " #t "\n  Actual: false\nExpected: true");         \
        }                                                                                                              \
    } while (0)

/**
 * @brief Assert equality.
 */
#define ASSERT_TRUE(t)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(t))                                                                                                      \
        {                                                                                                              \
            zzt_fail(zzt_test_state, __FILE__, __LINE__, "Value of: " #t "\n  Actual: false\nExpected: true");         \
            return;                                                                                                    \
        }                                                                                                              \
    } while (0)

/**
 * @brief Expect inequality.
 */
#define EXPECT_FALSE(t)                                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((t))                                                                                                       \
        {                                                                                                              \
            zzt_fail(zzt_test_state, __FILE__, __LINE__, "Value of: " #t "\n  Actual: true\nExpected: false");         \
        }                                                                                                              \
    } while (0)

/**
 * @brief Assert inequality.
 */
#define ASSERT_FALSE(t)                                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((t))                                                                                                       \
        {                                                                                                              \
            zzt_fail(zzt_test_state, __FILE__, __LINE__, "Value of: " #t "\n  Actual: true\nExpected: false");         \
            return;                                                                                                    \
        }                                                                                                              \
    } while (0)

/**
 * @brief Expect boolean equality.
 */
#define EXPECT_BOOLEQ(l, r)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        int ll = (l) ? 1 : 0, rr = (r) ? 1 : 0;                                                                        \
        zzt_eq(zzt_test_state, ZZT_FMT_BOOL, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
    } while (0)

/**
 * @brief Assert boolean equality.
 */
#define ASSERT_BOOLEQ(l, r)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        int ll = (l) ? 1 : 0, rr = (r) ? 1 : 0;                                                                        \
        zzt_eq(zzt_test_state, ZZT_FMT_BOOL, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
        return;                                                                                                        \
    } while (0)

/**
 * @brief Expect char equality.
 */
#define EXPECT_CHAREQ(l, r)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        char ll = l, rr = r;                                                                                           \
        zzt_eq(zzt_test_state, ZZT_FMT_CHAR, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
    } while (0)

/**
 * @brief Assert char equality.
 */
#define ASSERT_CHAREQ(l, r)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        char ll = l, rr = r;                                                                                           \
        zzt_eq(zzt_test_state, ZZT_FMT_CHAR, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
        return;                                                                                                        \
    } while (0)

/**
 * @brief Expect exact integer equality.
 */
#define EXPECT_INTEQ(l, r)                                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        ZZT_INTMAX ll = l, rr = r;                                                                                     \
        zzt_eq(zzt_test_state, ZZT_FMT_INT, &ll, &rr, #l, #r, __FILE__, __LINE__);                                     \
    } while (0)

/**
 * @brief Assert exact integer equality.
 */
#define ASSERT_INTEQ(l, r)                                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        ZZT_INTMAX ll = l, rr = r;                                                                                     \
        zzt_eq(zzt_test_state, ZZT_FMT_INT, &ll, &rr, #l, #r, __FILE__, __LINE__);                                     \
        return;                                                                                                        \
    } while (0)

/**
 * @brief Expect exact integer equality.
 */
#define EXPECT_UINTEQ(l, r)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        ZZT_UINTMAX ll = l, rr = r;                                                                                    \
        zzt_eq(zzt_test_state, ZZT_FMT_UINT, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
    } while (0)

/**
 * @brief Assert exact integer equality.
 */
#define ASSERT_UINTEQ(l, r)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        ZZT_UINTMAX ll = l, rr = r;                                                                                    \
        zzt_eq(zzt_test_state, ZZT_FMT_UINT, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
        return;                                                                                                        \
    } while (0)

/**
 * @brief Expect exact integer equality, failures are shown in hex.
 */
#define EXPECT_XINTEQ(l, r)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        ZZT_UINTMAX ll = l, rr = r;                                                                                    \
        zzt_eq(zzt_test_state, ZZT_FMT_XINT, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
    } while (0)

/**
 * @brief Assert exact integer equality, failures are shown in hex.
 */
#define ASSERT_XINTEQ(l, r)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        ZZT_UINTMAX ll = l, rr = r;                                                                                    \
        zzt_eq(zzt_test_state, ZZT_FMT_XINT, &ll, &rr, #l, #r, __FILE__, __LINE__);                                    \
        return;                                                                                                        \
    } while (0)

/**
 * @brief Expect string equality.
 */
#define EXPECT_STREQ(l, r)                                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        const char *ll = l, *rr = r;                                                                                   \
        zzt_eq(zzt_test_state, ZZT_FMT_STR, (const void *)ll, (const void *)rr, #l, #r, __FILE__, __LINE__);           \
    } while (0)

/**
 * @brief Assert string equality.
 */
#define ASSERT_STREQ(l, r)                                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        const char *ll = l, *rr = r;                                                                                   \
        zzt_eq(zzt_test_state, ZZT_FMT_STR, (const void *)ll, (const void *)rr, #l, #r, __FILE__, __LINE__);           \
        return;                                                                                                        \
    } while (0)

/**
 * @brief Add a failure, without a return.
 */
#define ADD_FAILURE()                                                                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        zzt_fail(zzt_test_state, __FILE__, __LINE__, "Failure");                                                       \
    } while (0)

/**
 * @brief Signal failure.
 */
#define FAIL()                                                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        zzt_fail(zzt_test_state, __FILE__, __LINE__, "Failure");                                                       \
        return;                                                                                                        \
    } while (0)

/**
 * @brief Signal skip.
 */
#define SKIP()                                                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        zzt_skip(zzt_test_state);                                                                                      \
        return;                                                                                                        \
    } while (0)

/**
 * @brief Add suite of tests to be run when RUN_TESTS is called.
 */
#define ADD_TEST_SUITE(s)                                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        ZZT_SUITENAME(s)();                                                                                            \
        zzt_add_test_suite(&ZZT_SUITEINFO(s));                                                                         \
    } while (0)

/**
 * @brief Run all tests and return code which can be returned from main().
 */
#define RUN_TESTS() (zzt_run_all())

int zzt_strcmp(const char *lhs, const char *rhs);
void zzt_skip(struct zzt_test_state_s *state);
void zzt_fail(struct zzt_test_state_s *state, const char *file, unsigned long line, const char *msgstr);
ZZT_BOOL zzt_eq(struct zzt_test_state_s *state, enum zzt_fmt_e fmt, const void *l, const void *r, const char *ls,
                const char *rs, const char *file, unsigned long line);
void zzt_add_test_suite(struct zzt_test_suite_s *suite);
int zzt_run_all(void);

/******************************************************************************/
#if defined(ZZTEST_IMPLEMENTATION)
/******************************************************************************/

#if defined(_WIN32)
#pragma comment(lib, "WinMM.Lib") /* Timer functions */
#include <Windows.h>
#elif defined(__unix__)
#include <sys/time.h> /* Timer functions. */
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

/******************************************************************************/

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
    return 0; /* oh well... */
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
#elif defined(_MSC_VER) /* FIXME: When was this added? */
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
    else if (REMAIN_() < 5) /* Needs to contain at least "...\0 */
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
#undef WRITE_
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
    case ZZT_FMT_INT:
        zzt_sprintf(buffer, sizeof(buffer), "%" ZZT_PRIiMAX, *((ZZT_INTMAX *)v));
        break;
    case ZZT_FMT_UINT:
        zzt_sprintf(buffer, sizeof(buffer), "%" ZZT_PRIuMAX, *((ZZT_UINTMAX *)v));
        break;
    case ZZT_FMT_XINT:
        zzt_sprintf(buffer, sizeof(buffer), "0x%" ZZT_PRIuMAX, *((ZZT_UINTMAX *)v));
        break;
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

/******************************************************************************/

int zzt_strcmp(const char *lhs, const char *rhs)
{
    return strcmp(lhs, rhs);
}

/******************************************************************************/

void zzt_skip(struct zzt_test_state_s *state)
{
    state->skipped += 1;
}

/******************************************************************************/

void zzt_fail(struct zzt_test_state_s *state, const char *file, unsigned long line, const char *msgstr)
{
    ZZT_PRINTF("%s(%lu): error: %s\n\n", file, line, msgstr);
    state->failed += 1;
}

/******************************************************************************/

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
    else if (fmt == ZZT_FMT_INT)
    {
        isEqual = *((ZZT_INTMAX *)l) == *((ZZT_INTMAX *)r);
    }
    else if (fmt == ZZT_FMT_UINT || fmt == ZZT_FMT_XINT)
    {
        isEqual = *((ZZT_UINTMAX *)l) == *((ZZT_UINTMAX *)r);
    }
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
        return ZZT_TRUE;
    }

    state->failed += 1;

    ZZT_PRINTF("%s(%lu): error: Expected equality of these values:\n", file, line);
    zzt_printv(fmt, l, ls);
    zzt_printv(fmt, r, rs);
    puts("");

    return ZZT_FALSE;
}

/******************************************************************************/

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

/******************************************************************************/

int zzt_run_all(void)
{
    unsigned long passed = 0, failed = 0, skipped = 0;
    unsigned long startAllMs = 0, allMs = 0;
    struct zzt_test_suite_s *suite = g_suitesHead;
    struct zzt_test_s *test = NULL;

#if defined(_WIN32)
    /* Set timer resolution to 1ms. */
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

    return failed != 0;
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

TEST(zztest, assert_bool)
{
    ASSERT_BOOLEQ(ZZT_TRUE, ZZT_FALSE);
    EXPECT_BOOLEQ(ZZT_FALSE, ZZT_TRUE);
}

TEST(zztest, assert_char)
{
    ASSERT_CHAREQ('a', 'b');
    EXPECT_CHAREQ('c', 'd');
}

TEST(zztest, assert_int)
{
    ASSERT_INTEQ(1, 2);
    EXPECT_INTEQ(3, 4);
}

TEST(zztest, assert_uint)
{
    ASSERT_UINTEQ(1, 2);
    EXPECT_UINTEQ(3, 4);
}

TEST(zztest, assert_xint)
{
    ASSERT_XINTEQ(1, 2);
    EXPECT_XINTEQ(3, 4);
}

TEST(zztest, assert_str)
{
    ASSERT_STREQ("foo", "bar");
    EXPECT_STREQ("baz", "plugh");
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
    SUITE_TEST(zztest, assert_bool);
    SUITE_TEST(zztest, assert_char);
    SUITE_TEST(zztest, assert_int);
    SUITE_TEST(zztest, assert_uint);
    SUITE_TEST(zztest, assert_xint);
    SUITE_TEST(zztest, assert_str);
}

int main()
{
    ADD_TEST_SUITE(zztest);
    return RUN_TESTS();
}

#endif /* defined(ZZTEST_SELFCHECK) */
#endif /* defined(ZZTEST_IMPLEMENTATION) */
#endif /* !defined(INCLUDE_ZZTEST_H) */
