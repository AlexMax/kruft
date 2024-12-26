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
    EXPECT_SIZEEQ(CHAR_WIDTH, sizeof(char) * CHAR_BIT);
    EXPECT_SIZEEQ(SCHAR_WIDTH, sizeof(signed char) * CHAR_BIT);
    EXPECT_SIZEEQ(UCHAR_WIDTH, sizeof(unsigned char) * CHAR_BIT);
}

TEST(limits, short)
{
    EXPECT_SIZEEQ(SHRT_WIDTH, sizeof(short) * CHAR_BIT);
    EXPECT_SIZEEQ(USHRT_WIDTH, sizeof(unsigned short) * CHAR_BIT);
}

TEST(limits, int)
{
    EXPECT_SIZEEQ(INT_WIDTH, sizeof(int) * CHAR_BIT);
    EXPECT_SIZEEQ(UINT_WIDTH, sizeof(unsigned int) * CHAR_BIT);
}

TEST(limits, long)
{
    EXPECT_SIZEEQ(LONG_WIDTH, sizeof(long) * CHAR_BIT);
    EXPECT_SIZEEQ(ULONG_WIDTH, sizeof(unsigned long) * CHAR_BIT);
}

TEST(limits, longlong)
{
#if !defined(ULLONG_MAX)
    SKIP();
#else
    long long i = LLONG_MIN;
    EXPECT_INT64EQ(i, LLONG_MIN);

    i = LLONG_MAX;
    EXPECT_INT64EQ(i, LLONG_MAX);

    unsigned long long u = ULLONG_MAX;
    EXPECT_UINT64EQ(u, ULLONG_MAX);

    EXPECT_SIZEEQ(LLONG_WIDTH, sizeof(long long) * CHAR_BIT);
    EXPECT_SIZEEQ(ULLONG_WIDTH, sizeof(unsigned long long) * CHAR_BIT);
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
