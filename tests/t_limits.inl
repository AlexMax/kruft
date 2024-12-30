/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "zztest.h"

#include "krlimits.h"

TEST(limits, char)
{
    EXPECT_UINTEQ(CHAR_WIDTH, sizeof(char) * CHAR_BIT);
    EXPECT_UINTEQ(SCHAR_WIDTH, sizeof(signed char) * CHAR_BIT);
    EXPECT_UINTEQ(UCHAR_WIDTH, sizeof(unsigned char) * CHAR_BIT);
}

TEST(limits, short)
{
    EXPECT_UINTEQ(SHRT_WIDTH, sizeof(short) * CHAR_BIT);
    EXPECT_UINTEQ(USHRT_WIDTH, sizeof(unsigned short) * CHAR_BIT);
}

TEST(limits, int)
{
    EXPECT_UINTEQ(INT_WIDTH, sizeof(int) * CHAR_BIT);
    EXPECT_UINTEQ(UINT_WIDTH, sizeof(unsigned int) * CHAR_BIT);
}

TEST(limits, long)
{
    EXPECT_UINTEQ(LONG_WIDTH, sizeof(long) * CHAR_BIT);
    EXPECT_UINTEQ(ULONG_WIDTH, sizeof(unsigned long) * CHAR_BIT);
}

TEST(limits, longlong)
{
#if !defined(ULLONG_MAX)
    SKIP();
#else
    long long i = LLONG_MIN;
    EXPECT_INTEQ(i, LLONG_MIN);

    i = LLONG_MAX;
    EXPECT_INTEQ(i, LLONG_MAX);

    unsigned long long u = ULLONG_MAX;
    EXPECT_UINTEQ(u, ULLONG_MAX);

    EXPECT_UINTEQ(LLONG_WIDTH, sizeof(long long) * CHAR_BIT);
    EXPECT_UINTEQ(ULLONG_WIDTH, sizeof(unsigned long long) * CHAR_BIT);
#endif
}

SUITE(limits)
{
    SUITE_TEST(limits, char);
    SUITE_TEST(limits, short);
    SUITE_TEST(limits, int);
    SUITE_TEST(limits, long);
    SUITE_TEST(limits, longlong);
}
