//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "zztest.h"

#include "krbit.h"

#pragma warning(push)
#pragma warning(disable : 4127)

TEST(bit, kr_byteswap16_MACRO)
{
    uint16_t x = kr_byteswap16(0x0123);
    EXPECT_EQ(x, 0x2301);

    EXPECT_EQ(kr_byteswap16(0x0123), 0x2301);
}

TEST(bit, kr_bswap16_MACRO)
{
    EXPECT_EQ(kr_bswap16(0x0123), 0x2301);
}

TEST(bit, kr_byteswap32_MACRO)
{
    uint32_t x = kr_byteswap32(0x01234567);
    EXPECT_EQ(x, 0x67452301);

    EXPECT_EQ(kr_byteswap32(0x01234567), 0x67452301);
}

TEST(bit, kr_bswap32_MACRO)
{
    EXPECT_EQ(kr_bswap32(0x01234567), 0x67452301);
}

TEST(bit, kr_byteswap64_MACRO)
{
    uint64_t x = kr_byteswap64(UINT64_C(0x0123456789ABCDEF));
    EXPECT_EQ(x, UINT64_C(0xEFCDAB8967452301));

    EXPECT_EQ(kr_byteswap64(UINT64_C(0x0123456789ABCDEF)), UINT64_C(0xEFCDAB8967452301));
}

TEST(bit, kr_bswap64_MACRO)
{
    EXPECT_EQ(kr_bswap64(UINT64_C(0x0123456789ABCDEF)), UINT64_C(0xEFCDAB8967452301));
}

//------------------------------------------------------------------------------

TEST(bit, kr_has_single_bit8)
{
    EXPECT_EQ(kr_has_single_bit8(0x00), false);
    EXPECT_EQ(kr_has_single_bit8(0xFF), false);
    EXPECT_EQ(kr_has_single_bit8(0x80), true);
}

TEST(bit, kr_has_single_bit16)
{
    EXPECT_EQ(kr_has_single_bit16(0x00), false);
    EXPECT_EQ(kr_has_single_bit16(0xFF), false);
    EXPECT_EQ(kr_has_single_bit16(0x80), true);
}

TEST(bit, kr_has_single_bit32)
{
    EXPECT_EQ(kr_has_single_bit32(0x00), false);
    EXPECT_EQ(kr_has_single_bit32(0xFF), false);
    EXPECT_EQ(kr_has_single_bit32(0x80), true);
}

TEST(bit, kr_has_single_bit64)
{
    EXPECT_EQ(kr_has_single_bit64(0x00), false);
    EXPECT_EQ(kr_has_single_bit64(0xFF), false);
    EXPECT_EQ(kr_has_single_bit64(0x80), true);
}

//------------------------------------------------------------------------------

TEST(bit, kr_countl_zero32)
{
    EXPECT_EQ(kr_countl_zero32(0x80000000), 0);
    EXPECT_EQ(kr_countl_zero32(0x00008000), 16);
    EXPECT_EQ(kr_countl_zero32(0x00000000), 32);
}

//------------------------------------------------------------------------------

TEST(bit, kr_clz32_MACRO)
{
    EXPECT_EQ(kr_clz32(0x80000000), 0);
    EXPECT_EQ(kr_clz32(0x00008000), 16);
    EXPECT_EQ(kr_clz32(0x00000000), 32);
}

//------------------------------------------------------------------------------

TEST(bit, kr_countl_one32)
{
    EXPECT_EQ(kr_countl_one32(0x00000000), 0);
    EXPECT_EQ(kr_countl_one32(0xFFFF7FFF), 16);
    EXPECT_EQ(kr_countl_one32(0xFFFFFFFF), 32);
}

//------------------------------------------------------------------------------

TEST(bit, kr_clo32_MACRO)
{
    EXPECT_EQ(kr_clo32(0x00000000), 0);
    EXPECT_EQ(kr_clo32(0xFFFF7FFF), 16);
    EXPECT_EQ(kr_clo32(0xFFFFFFFF), 32);
}

//------------------------------------------------------------------------------

TEST(bit, kr_countr_zero32)
{
    EXPECT_EQ(kr_countr_zero32(0xFFFFFFFF), 0);
    EXPECT_EQ(kr_countr_zero32(0x00010000), 16);
    EXPECT_EQ(kr_countr_zero32(0x00000000), 32);
}

//------------------------------------------------------------------------------

TEST(bit, kr_ctz32_MACRO)
{
    EXPECT_EQ(kr_ctz32(0xFFFFFFFF), 0);
    EXPECT_EQ(kr_ctz32(0x00010000), 16);
    EXPECT_EQ(kr_ctz32(0x00000000), 32);
}

//------------------------------------------------------------------------------

TEST(bit, kr_countr_one32)
{
    EXPECT_EQ(kr_countr_one32(0x00000000), 0);
    EXPECT_EQ(kr_countr_one32(0xFFFEFFFF), 16);
    EXPECT_EQ(kr_countr_one32(0xFFFFFFFF), 32);
}

//------------------------------------------------------------------------------

TEST(bit, kr_cto32_MACRO)
{
    EXPECT_EQ(kr_cto32(0x00000000), 0);
    EXPECT_EQ(kr_cto32(0xFFFEFFFF), 16);
    EXPECT_EQ(kr_cto32(0xFFFFFFFF), 32);
}

//------------------------------------------------------------------------------

TEST(bit, kr_popcount16)
{
    EXPECT_EQ(kr_popcount16(0x04c7), 6);
}

TEST(bit, kr_popcnt16_MACRO)
{
    EXPECT_EQ(kr_popcnt16(0x04c7), 6);
}

TEST(bit, kr_popcount32)
{
    EXPECT_EQ(kr_popcount32(0x04c7), 6);
}

TEST(bit, kr_popcnt32_MACRO)
{
    EXPECT_EQ(kr_popcnt32(0x04c7), 6);
}

TEST(bit, kr_popcount64)
{
    EXPECT_EQ(kr_popcount64(0x04c7), 6);
}

TEST(bit, kr_popcnt64_MACRO)
{
    EXPECT_EQ(kr_popcnt64(0x04c7), 6);
}

//------------------------------------------------------------------------------

EXPORT_TEST_SUITE(bit) = {
    EXPORT_TEST(bit, kr_byteswap16_MACRO), EXPORT_TEST(bit, kr_bswap16_MACRO),    EXPORT_TEST(bit, kr_byteswap32_MACRO),
    EXPORT_TEST(bit, kr_bswap32_MACRO),    EXPORT_TEST(bit, kr_byteswap64_MACRO), EXPORT_TEST(bit, kr_bswap64_MACRO),
    EXPORT_TEST(bit, kr_has_single_bit8),  EXPORT_TEST(bit, kr_has_single_bit16), EXPORT_TEST(bit, kr_has_single_bit32),
    EXPORT_TEST(bit, kr_has_single_bit64), EXPORT_TEST(bit, kr_countl_zero32),    EXPORT_TEST(bit, kr_clz32_MACRO),
    EXPORT_TEST(bit, kr_countl_one32),     EXPORT_TEST(bit, kr_clo32_MACRO),      EXPORT_TEST(bit, kr_countr_zero32),
    EXPORT_TEST(bit, kr_ctz32_MACRO),      EXPORT_TEST(bit, kr_countr_one32),     EXPORT_TEST(bit, kr_cto32_MACRO),
    EXPORT_TEST(bit, kr_popcount16),       EXPORT_TEST(bit, kr_popcnt16_MACRO),   EXPORT_TEST(bit, kr_popcount32),
    EXPORT_TEST(bit, kr_popcnt32_MACRO),   EXPORT_TEST(bit, kr_popcount64),       EXPORT_TEST(bit, kr_popcnt64_MACRO),
};

#pragma warning(pop)
