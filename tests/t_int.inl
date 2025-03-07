/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "zztest.h"

#include "krint.h"

#pragma warning(push)
#pragma warning(disable : 4127)

TEST(int, int8)
{
    int8_t smin = INT8_MIN, smax = INT8_MAX;
    uint8_t umax = UINT8_MAX;

    EXPECT_UINTEQ(sizeof(int8_t), 1);
    EXPECT_UINTEQ(sizeof(uint8_t), 1);

    EXPECT_INTEQ(smin, -128);
    EXPECT_INTEQ(smax, 127);
    EXPECT_UINTEQ(umax, 255);
}

TEST(int, int16)
{
    int16_t smin = INT16_MIN, smax = INT16_MAX;
    uint16_t umax = UINT16_MAX;

    EXPECT_UINTEQ(sizeof(int16_t), 2);
    EXPECT_UINTEQ(sizeof(uint16_t), 2);

    EXPECT_INTEQ(smin, -32767 - 1);
    EXPECT_INTEQ(smax, 32767);
    EXPECT_UINTEQ(umax, 65535);
}

TEST(int, int32)
{
    int32_t smin = INT32_MIN, smax = INT32_MAX;
    uint32_t umax = UINT32_MAX;

    EXPECT_UINTEQ(sizeof(int32_t), 4);
    EXPECT_UINTEQ(sizeof(uint32_t), 4);

    EXPECT_INTEQ(smin, -2147483647 - 1);
    EXPECT_INTEQ(smax, 2147483647);
    EXPECT_UINTEQ(umax, UINT32_C(4294967295));

    EXPECT_UINTEQ(UINT32_MAX, UINT32_C(0) - 1);
}

TEST(int, int64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    int64_t smin = INT64_MIN, smax = INT64_MAX;
    uint64_t umax = UINT64_MAX;

    EXPECT_UINTEQ(sizeof(int64_t), 8);
    EXPECT_UINTEQ(sizeof(uint64_t), 8);

    EXPECT_INTEQ(smin, -9223372036854775807 - 1);
    EXPECT_INTEQ(smax, 9223372036854775807);
    EXPECT_UINTEQ(umax, UINT64_C(18446744073709551615));

    EXPECT_UINTEQ(UINT64_MAX, UINT64_C(0) - 1);
#endif /* !defined(UINT64_MAX) */
}

TEST(int, size)
{
    size_t x = 0;
    x -= 1;
    EXPECT_UINTEQ(x, SIZE_MAX);
}

SUITE(int)
{
    SUITE_TEST(int, int8);
    SUITE_TEST(int, int16);
    SUITE_TEST(int, int32);
    SUITE_TEST(int, int64);
    SUITE_TEST(int, size);
}

#pragma warning(pop)
