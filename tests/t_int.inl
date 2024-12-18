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
    EXPECT_EQ(sizeof(int8_t), 1);
    EXPECT_EQ(sizeof(uint8_t), 1);

    EXPECT_EQ(sizeof(int16_t), 2);
    EXPECT_EQ(sizeof(uint16_t), 2);

    EXPECT_EQ(sizeof(int32_t), 4);
    EXPECT_EQ(sizeof(uint32_t), 4);

    EXPECT_EQ(sizeof(int64_t), 8);
    EXPECT_EQ(sizeof(uint64_t), 8);
}

TEST(int, ranges)
{
    {
        int8_t smin = INT8_MIN;
        EXPECT_EQ(smin, -128);

        int8_t smax = INT8_MAX;
        EXPECT_EQ(smax, 127);

        uint8_t umax = UINT8_MAX;
        EXPECT_EQ(umax, 255);
    }

    {
        int16_t smin = INT16_MIN;
        EXPECT_EQ(smin, -32767 - 1);

        int16_t smax = INT16_MAX;
        EXPECT_EQ(smax, 32767);

        uint16_t umax = UINT16_MAX;
        EXPECT_EQ(umax, 65535);
    }

    {
        int32_t smin = INT32_MIN;
        EXPECT_EQ(smin, -2147483647 - 1);

        int32_t smax = INT32_MAX;
        EXPECT_EQ(smax, 2147483647);

        uint32_t umax = UINT32_MAX;
        EXPECT_EQ(umax, 4294967295);
    }

    {
        int64_t smin = INT64_MIN;
        EXPECT_EQ(smin, -9223372036854775807 - 1);

        int64_t smax = INT64_MAX;
        EXPECT_EQ(smax, 9223372036854775807);

        uint64_t umax = UINT64_MAX;
        EXPECT_EQ(umax, UINT64_C(18446744073709551615));
    }
}

EXPORT_TEST_SUITE(int) = {
    EXPORT_TEST(int, types),
    EXPORT_TEST(int, ranges),
};

#pragma warning(pop)
