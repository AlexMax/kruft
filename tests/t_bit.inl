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

//------------------------------------------------------------------------------

TEST(bit, kr_byteswap16)
{
    EXPECT_EQ(0x2301, kr_byteswap16(0x0123));
}

TEST(bit, kr_bswap16_MACRO)
{
    EXPECT_EQ(0x2301, kr_bswap16(0x0123));
}

TEST(bit, kr_byteswap32)
{
    EXPECT_EQ(0x67452301, kr_byteswap32(0x01234567));
}

TEST(bit, kr_bswap32_MACRO)
{
    EXPECT_EQ(0x67452301, kr_bswap32(0x01234567));
}

TEST(bit, kr_byteswap64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  // !defined(UINT64_MAX)
    EXPECT_EQ(UINT64_C(0xEFCDAB8967452301), kr_byteswap64(UINT64_C(0x0123456789ABCDEF)));
#endif // !defined(UINT64_MAX)
}

TEST(bit, kr_bswap64_MACRO)
{
    EXPECT_EQ(UINT64_C(0xEFCDAB8967452301), kr_bswap64(UINT64_C(0x0123456789ABCDEF)));
}

//------------------------------------------------------------------------------

TEST(bit, kr_has_single_bit8)
{
    EXPECT_EQ(false, kr_has_single_bit8(0x00));
    EXPECT_EQ(false, kr_has_single_bit8(0xFF));
    EXPECT_EQ(true, kr_has_single_bit8(0x80));
}

TEST(bit, kr_has_single_bit16)
{
    EXPECT_EQ(false, kr_has_single_bit16(0x00));
    EXPECT_EQ(false, kr_has_single_bit16(0xFF));
    EXPECT_EQ(true, kr_has_single_bit16(0x80));
}

TEST(bit, kr_has_single_bit32)
{
    EXPECT_EQ(false, kr_has_single_bit32(0x00));
    EXPECT_EQ(false, kr_has_single_bit32(0xFF));
    EXPECT_EQ(true, kr_has_single_bit32(0x80));
}

TEST(bit, kr_has_single_bit64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  // !defined(UINT64_MAX)
    EXPECT_EQ(false, kr_has_single_bit64(0x00));
    EXPECT_EQ(false, kr_has_single_bit64(0xFF));
    EXPECT_EQ(true, kr_has_single_bit64(0x80));
#endif // !defined(UINT64_MAX)
}

//------------------------------------------------------------------------------

TEST(bit, kr_rotl32)
{
    EXPECT_EQ(0x0799aa80, kr_rotl32(0x00f33550, 3));
    EXPECT_EQ(0x001e66aa, kr_rotl32(0x00f33550, 29));
    EXPECT_EQ(0x00f33550, kr_rotl32(0x00f33550, 0));
}

TEST(bit, kr_rol32_MACRO)
{
    EXPECT_EQ(0x0799aa80, kr_rol32(0x00f33550, 3));
    EXPECT_EQ(0x001e66aa, kr_rol32(0x00f33550, 29));
    EXPECT_EQ(0x00f33550, kr_rol32(0x00f33550, 0));
}

TEST(bit, kr_rotl64)
{
    EXPECT_EQ(UINT64_C(0x2a99ff800799aa80), kr_rotl64(UINT64_C(0x05533ff000f33550), 3));
    EXPECT_EQ(UINT64_C(0x001e66aa00aa67fe), kr_rotl64(UINT64_C(0x05533ff000f33550), 29));
    EXPECT_EQ(UINT64_C(0x0799aa802a99ff80), kr_rotl64(UINT64_C(0x05533ff000f33550), 35));
    EXPECT_EQ(UINT64_C(0x00aa67fe001e66aa), kr_rotl64(UINT64_C(0x05533ff000f33550), 61));
    EXPECT_EQ(UINT64_C(0x05533ff000f33550), kr_rotl64(UINT64_C(0x05533ff000f33550), 0));
}

TEST(bit, kr_rol64_MACRO)
{
    EXPECT_EQ(UINT64_C(0x2a99ff800799aa80), kr_rol64(UINT64_C(0x05533ff000f33550), 3));
    EXPECT_EQ(UINT64_C(0x001e66aa00aa67fe), kr_rol64(UINT64_C(0x05533ff000f33550), 29));
    EXPECT_EQ(UINT64_C(0x0799aa802a99ff80), kr_rol64(UINT64_C(0x05533ff000f33550), 35));
    EXPECT_EQ(UINT64_C(0x00aa67fe001e66aa), kr_rol64(UINT64_C(0x05533ff000f33550), 61));
    EXPECT_EQ(UINT64_C(0x05533ff000f33550), kr_rol64(UINT64_C(0x05533ff000f33550), 0));
}

//------------------------------------------------------------------------------

TEST(bit, kr_rotr32)
{
    EXPECT_EQ(0x001e66aa, kr_rotr32(0x00f33550, 3));
    EXPECT_EQ(0x0799aa80, kr_rotr32(0x00f33550, 29));
    EXPECT_EQ(0x00f33550, kr_rotr32(0x00f33550, 0));
}

TEST(bit, kr_ror32_MACRO)
{
    EXPECT_EQ(0x001e66aa, kr_ror32(0x00f33550, 3));
    EXPECT_EQ(0x0799aa80, kr_ror32(0x00f33550, 29));
    EXPECT_EQ(0x00f33550, kr_ror32(0x00f33550, 0));
}

TEST(bit, kr_rotr64)
{
    EXPECT_EQ(UINT64_C(0x00aa67fe001e66aa), kr_rotr64(UINT64_C(0x05533ff000f33550), 3));
    EXPECT_EQ(UINT64_C(0x0799aa802a99ff80), kr_rotr64(UINT64_C(0x05533ff000f33550), 29));
    EXPECT_EQ(UINT64_C(0x001e66aa00aa67fe), kr_rotr64(UINT64_C(0x05533ff000f33550), 35));
    EXPECT_EQ(UINT64_C(0x2a99ff800799aa80), kr_rotr64(UINT64_C(0x05533ff000f33550), 61));
    EXPECT_EQ(UINT64_C(0x05533ff000f33550), kr_rotr64(UINT64_C(0x05533ff000f33550), 0));
}

TEST(bit, kr_ror64_MACRO)
{
    EXPECT_EQ(UINT64_C(0x00aa67fe001e66aa), kr_ror64(UINT64_C(0x05533ff000f33550), 3));
    EXPECT_EQ(UINT64_C(0x0799aa802a99ff80), kr_ror64(UINT64_C(0x05533ff000f33550), 29));
    EXPECT_EQ(UINT64_C(0x001e66aa00aa67fe), kr_ror64(UINT64_C(0x05533ff000f33550), 35));
    EXPECT_EQ(UINT64_C(0x2a99ff800799aa80), kr_ror64(UINT64_C(0x05533ff000f33550), 61));
    EXPECT_EQ(UINT64_C(0x05533ff000f33550), kr_ror64(UINT64_C(0x05533ff000f33550), 0));
}

//------------------------------------------------------------------------------

TEST(bit, kr_countl_zero32)
{
    EXPECT_EQ(0, kr_countl_zero32(0x80000000));
    EXPECT_EQ(16, kr_countl_zero32(0x00008000));
    EXPECT_EQ(32, kr_countl_zero32(0x00000000));
}

TEST(bit, kr_clz32_MACRO)
{
    EXPECT_EQ(0, kr_clz32(0x80000000));
    EXPECT_EQ(16, kr_clz32(0x00008000));
    EXPECT_EQ(32, kr_clz32(0x00000000));
}

//------------------------------------------------------------------------------

TEST(bit, kr_countl_one32)
{
    EXPECT_EQ(0, kr_countl_one32(0x00000000));
    EXPECT_EQ(16, kr_countl_one32(0xFFFF7FFF));
    EXPECT_EQ(32, kr_countl_one32(0xFFFFFFFF));
}

TEST(bit, kr_clo32_MACRO)
{
    EXPECT_EQ(0, kr_clo32(UINT32_C(0x00000000)));
    EXPECT_EQ(16, kr_clo32(UINT32_C(0xFFFF7FFF)));
    EXPECT_EQ(32, kr_clo32(UINT32_C(0xFFFFFFFF)));
}

//------------------------------------------------------------------------------

TEST(bit, kr_countr_zero32)
{
    EXPECT_EQ(0, kr_countr_zero32(0xFFFFFFFF));
    EXPECT_EQ(16, kr_countr_zero32(0x00010000));
    EXPECT_EQ(32, kr_countr_zero32(0x00000000));
}

TEST(bit, kr_ctz32_MACRO)
{
    EXPECT_EQ(0, kr_ctz32(0xFFFFFFFF));
    EXPECT_EQ(16, kr_ctz32(0x00010000));
    EXPECT_EQ(32, kr_ctz32(0x00000000));
}

//------------------------------------------------------------------------------

TEST(bit, kr_countr_one32)
{
    EXPECT_EQ(0, kr_countr_one32(0x00000000));
    EXPECT_EQ(16, kr_countr_one32(0xFFFEFFFF));
    EXPECT_EQ(32, kr_countr_one32(0xFFFFFFFF));
}

TEST(bit, kr_cto32_MACRO)
{
    EXPECT_EQ(0, kr_cto32(UINT32_C(0x00000000)));
    EXPECT_EQ(16, kr_cto32(UINT32_C(0xFFFEFFFF)));
    EXPECT_EQ(32, kr_cto32(UINT32_C(0xFFFFFFFF)));
}

//------------------------------------------------------------------------------

TEST(bit, kr_popcount16)
{
    EXPECT_EQ(6, kr_popcount16(0x04c7));
}

TEST(bit, kr_popcnt16_MACRO)
{
    EXPECT_EQ(6, kr_popcnt16(0x04c7));
}

TEST(bit, kr_popcount32)
{
    EXPECT_EQ(6, kr_popcount32(0x04c7));
}

TEST(bit, kr_popcnt32_MACRO)
{
    EXPECT_EQ(6, kr_popcnt32(0x04c7));
}

TEST(bit, kr_popcount64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  // !defined(UINT64_MAX)
    EXPECT_EQ(6, kr_popcount64(0x04c7));
#endif // !defined(UINT64_MAX)
}

TEST(bit, kr_popcnt64_MACRO)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  // !defined(UINT64_MAX)
    EXPECT_EQ(6, kr_popcnt64(0x04c7));
#endif // !defined(UINT64_MAX)
}

//------------------------------------------------------------------------------

EXPORT_TEST_SUITE(bit) = {
    EXPORT_TEST(bit, kr_byteswap16),       EXPORT_TEST(bit, kr_bswap16_MACRO),    EXPORT_TEST(bit, kr_byteswap32),
    EXPORT_TEST(bit, kr_bswap32_MACRO),    EXPORT_TEST(bit, kr_byteswap64),       EXPORT_TEST(bit, kr_bswap64_MACRO),
    EXPORT_TEST(bit, kr_has_single_bit8),  EXPORT_TEST(bit, kr_has_single_bit16), EXPORT_TEST(bit, kr_has_single_bit32),
    EXPORT_TEST(bit, kr_has_single_bit64), EXPORT_TEST(bit, kr_rotl32),           EXPORT_TEST(bit, kr_rol32_MACRO),
    EXPORT_TEST(bit, kr_rotl64),           EXPORT_TEST(bit, kr_rol64_MACRO),      EXPORT_TEST(bit, kr_rotr32),
    EXPORT_TEST(bit, kr_ror32_MACRO),      EXPORT_TEST(bit, kr_rotr64),           EXPORT_TEST(bit, kr_ror64_MACRO),
    EXPORT_TEST(bit, kr_countl_zero32),    EXPORT_TEST(bit, kr_clz32_MACRO),      EXPORT_TEST(bit, kr_countl_one32),
    EXPORT_TEST(bit, kr_clo32_MACRO),      EXPORT_TEST(bit, kr_countr_zero32),    EXPORT_TEST(bit, kr_ctz32_MACRO),
    EXPORT_TEST(bit, kr_countr_one32),     EXPORT_TEST(bit, kr_cto32_MACRO),      EXPORT_TEST(bit, kr_popcount16),
    EXPORT_TEST(bit, kr_popcnt16_MACRO),   EXPORT_TEST(bit, kr_popcount32),       EXPORT_TEST(bit, kr_popcnt32_MACRO),
    EXPORT_TEST(bit, kr_popcount64),       EXPORT_TEST(bit, kr_popcnt64_MACRO),
};

#pragma warning(pop)
