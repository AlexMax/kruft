//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "zztest.h"

#include "krint.h"

#pragma warning(push)
#pragma warning(disable : 4127)

TEST(int, types)
{
    EXPECT_INTEQ(sizeof(int8_t), 1);
    EXPECT_INTEQ(sizeof(uint8_t), 1);

    EXPECT_INTEQ(sizeof(int16_t), 2);
    EXPECT_INTEQ(sizeof(uint16_t), 2);

    EXPECT_INTEQ(sizeof(int32_t), 4);
    EXPECT_INTEQ(sizeof(uint32_t), 4);

    EXPECT_INTEQ(sizeof(int64_t), 8);
    EXPECT_INTEQ(sizeof(uint64_t), 8);
}

TEST(int, ranges)
{
    {
        int8_t smin = INT8_MIN;
        EXPECT_INTEQ(smin, -128);

        int8_t smax = INT8_MAX;
        EXPECT_INTEQ(smax, 127);

        uint8_t umax = UINT8_MAX;
        EXPECT_UINTEQ(umax, 255);
    }

    {
        int16_t smin = INT16_MIN;
        EXPECT_INTEQ(smin, -32767 - 1);

        int16_t smax = INT16_MAX;
        EXPECT_INTEQ(smax, 32767);

        uint16_t umax = UINT16_MAX;
        EXPECT_UINTEQ(umax, 65535);
    }

    {
        int32_t smin = INT32_MIN;
        EXPECT_INTEQ(smin, -2147483647 - 1);

        int32_t smax = INT32_MAX;
        EXPECT_INTEQ(smax, 2147483647);

        uint32_t umax = UINT32_MAX;
        EXPECT_UINTEQ(umax, UINT32_C(4294967295));
    }

    {
        int64_t smin = INT64_MIN;
        EXPECT_INT64EQ(smin, -9223372036854775807 - 1);

        int64_t smax = INT64_MAX;
        EXPECT_INT64EQ(smax, 9223372036854775807);

        uint64_t umax = UINT64_MAX;
        EXPECT_UINT64EQ(umax, UINT64_C(18446744073709551615));
    }
}

SUITE(int)
{
    SUITE_TEST(int, types);
    SUITE_TEST(int, ranges);
}

#pragma warning(pop)
