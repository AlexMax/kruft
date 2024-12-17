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
    EXPECT_EQ(sizeof(kr_i8), 1);
    EXPECT_EQ(sizeof(kr_u8), 1);

    EXPECT_EQ(sizeof(kr_i16), 2);
    EXPECT_EQ(sizeof(kr_u16), 2);

    EXPECT_EQ(sizeof(kr_i32), 4);
    EXPECT_EQ(sizeof(kr_u32), 4);

    EXPECT_EQ(sizeof(kr_i64), 8);
    EXPECT_EQ(sizeof(kr_u64), 8);
}

TEST(int, ranges)
{
    {
        kr_i8 smin = KR_I8_MIN;
        EXPECT_EQ(smin, -128);

        kr_i8 smax = KR_I8_MAX;
        EXPECT_EQ(smax, 127);

        kr_u8 umax = KR_U8_MAX;
        EXPECT_EQ(umax, 255);
    }

    {
        kr_i16 smin = KR_I16_MIN;
        EXPECT_EQ(smin, -32768);

        kr_i16 smax = KR_I16_MAX;
        EXPECT_EQ(smax, 32767);

        kr_u16 umax = KR_U16_MAX;
        EXPECT_EQ(umax, 65535);
    }

    {
        kr_i32 smin = KR_I32_MIN;
        EXPECT_EQ(smin, -2147483647 - 1);

        kr_i32 smax = KR_I32_MAX;
        EXPECT_EQ(smax, 2147483647);

        kr_u32 umax = KR_U32_MAX;
        EXPECT_EQ(umax, 4294967295);
    }

    {
        kr_i64 smin = KR_I64_MIN;
        EXPECT_EQ(smin, -9223372036854775807 - 1);

        kr_i64 smax = KR_I64_MAX;
        EXPECT_EQ(smax, 9223372036854775807);

        kr_u64 umax = KR_U64_MAX;
        EXPECT_EQ(umax, 18446744073709551615);
    }
}

EXPORT_TEST_SUITE(int) = {
    EXPORT_TEST(int, types),
    EXPORT_TEST(int, ranges),
};

#pragma warning(pop)
