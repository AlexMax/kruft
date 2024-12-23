//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "zztest.h"

#include "krbit.h"
#include "krint.h"

#pragma warning(push)
#pragma warning(disable : 4127)

//------------------------------------------------------------------------------

TEST(bit, kr_byteswap16)
{
    EXPECT_UINTEQ(0x2301, kr_byteswap16(0x0123));
}

TEST(bit, kr_bswap16_MACRO)
{
    EXPECT_UINTEQ(0x2301, kr_bswap16(0x0123));
}

TEST(bit, kr_byteswap32)
{
    EXPECT_UINTEQ(0x67452301, kr_byteswap32(0x01234567));
}

TEST(bit, kr_bswap32_MACRO)
{
    EXPECT_UINTEQ(0x67452301, kr_bswap32(0x01234567));
}

TEST(bit, kr_byteswap64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  // !defined(UINT64_MAX)
    EXPECT_UINT64EQ(UINT64_C(0xEFCDAB8967452301), kr_byteswap64(UINT64_C(0x0123456789ABCDEF)));
#endif // !defined(UINT64_MAX)
}

TEST(bit, kr_bswap64_MACRO)
{
    EXPECT_UINT64EQ(UINT64_C(0xEFCDAB8967452301), kr_bswap64(UINT64_C(0x0123456789ABCDEF)));
}

//------------------------------------------------------------------------------

TEST(bit, kr_has_single_bit8)
{
    EXPECT_UINTEQ(false, kr_has_single_bit8(0x00));
    EXPECT_UINTEQ(false, kr_has_single_bit8(0xFF));
    EXPECT_UINTEQ(true, kr_has_single_bit8(0x80));
}

TEST(bit, kr_has_single_bit16)
{
    EXPECT_UINTEQ(false, kr_has_single_bit16(0x00));
    EXPECT_UINTEQ(false, kr_has_single_bit16(0xFF));
    EXPECT_UINTEQ(true, kr_has_single_bit16(0x80));
}

TEST(bit, kr_has_single_bit32)
{
    EXPECT_UINTEQ(false, kr_has_single_bit32(0x00));
    EXPECT_UINTEQ(false, kr_has_single_bit32(0xFF));
    EXPECT_UINTEQ(true, kr_has_single_bit32(0x80));
}

TEST(bit, kr_has_single_bit64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  // !defined(UINT64_MAX)
    EXPECT_UINTEQ(false, kr_has_single_bit64(0x00));
    EXPECT_UINTEQ(false, kr_has_single_bit64(0xFF));
    EXPECT_UINTEQ(true, kr_has_single_bit64(0x80));
#endif // !defined(UINT64_MAX)
}

//------------------------------------------------------------------------------

TEST(bit, kr_bit_ceil32)
{
    EXPECT_UINTEQ(1, kr_bit_ceil32(0));
    EXPECT_UINTEQ(1, kr_bit_ceil32(1));
    EXPECT_UINTEQ(2, kr_bit_ceil32(2));
    EXPECT_UINTEQ(4, kr_bit_ceil32(3));
    EXPECT_UINTEQ(4, kr_bit_ceil32(4));
    EXPECT_UINTEQ(8, kr_bit_ceil32(5));
    EXPECT_UINTEQ(INT32_MAX + UINT32_C(1), kr_bit_ceil32(INT32_MAX));
}

TEST(bit, kr_bit_ceil64)
{
    EXPECT_UINT64EQ(1, kr_bit_ceil64(0));
    EXPECT_UINT64EQ(1, kr_bit_ceil64(1));
    EXPECT_UINT64EQ(2, kr_bit_ceil64(2));
    EXPECT_UINT64EQ(4, kr_bit_ceil64(3));
    EXPECT_UINT64EQ(4, kr_bit_ceil64(4));
    EXPECT_UINT64EQ(8, kr_bit_ceil64(5));
    EXPECT_UINT64EQ(INT32_MAX + UINT64_C(1), kr_bit_ceil64(INT32_MAX));
    EXPECT_UINT64EQ(INT64_MAX + UINT64_C(1), kr_bit_ceil64(INT64_MAX));
}

TEST(bit, kr_bit_floor32)
{
    EXPECT_UINTEQ(0, kr_bit_floor32(0));
    EXPECT_UINTEQ(1, kr_bit_floor32(1));
    EXPECT_UINTEQ(2, kr_bit_floor32(2));
    EXPECT_UINTEQ(2, kr_bit_floor32(3));
    EXPECT_UINTEQ(4, kr_bit_floor32(4));
    EXPECT_UINTEQ(4, kr_bit_floor32(5));
    EXPECT_UINTEQ(INT32_MAX + UINT32_C(1), kr_bit_floor32(UINT32_MAX));
}

TEST(bit, kr_bit_floor64)
{
    EXPECT_UINT64EQ(0, kr_bit_floor64(0));
    EXPECT_UINT64EQ(1, kr_bit_floor64(1));
    EXPECT_UINT64EQ(2, kr_bit_floor64(2));
    EXPECT_UINT64EQ(2, kr_bit_floor64(3));
    EXPECT_UINT64EQ(4, kr_bit_floor64(4));
    EXPECT_UINT64EQ(4, kr_bit_floor64(5));
    EXPECT_UINT64EQ(INT32_MAX + UINT64_C(1), kr_bit_floor64(UINT32_MAX));
    EXPECT_UINT64EQ(INT64_MAX + UINT64_C(1), kr_bit_floor64(UINT64_MAX));
}

TEST(bit, kr_bit_width32)
{
    EXPECT_UINTEQ(0, kr_bit_width32(0));
    EXPECT_UINTEQ(1, kr_bit_width32(1));
    EXPECT_UINTEQ(2, kr_bit_width32(2));
    EXPECT_UINTEQ(2, kr_bit_width32(3));
    EXPECT_UINTEQ(3, kr_bit_width32(4));
    EXPECT_UINTEQ(32, kr_bit_width32(UINT32_MAX));
}

TEST(bit, kr_bit_width64)
{
    EXPECT_UINT64EQ(0, kr_bit_width64(0));
    EXPECT_UINT64EQ(1, kr_bit_width64(1));
    EXPECT_UINT64EQ(2, kr_bit_width64(2));
    EXPECT_UINT64EQ(2, kr_bit_width64(3));
    EXPECT_UINT64EQ(3, kr_bit_width64(4));
    EXPECT_UINT64EQ(32, kr_bit_width64(UINT32_MAX));
    EXPECT_UINT64EQ(64, kr_bit_width64(UINT64_MAX));
}

//------------------------------------------------------------------------------

TEST(bit, kr_rotl16)
{
    EXPECT_XINTEQ(0xe6a1, kr_rotl16(0x3cd4, 3));
    EXPECT_XINTEQ(0x879a, kr_rotl16(0x3cd4, 13));
    EXPECT_XINTEQ(0x3cd4, kr_rotl16(0x3cd4, 0));
}

TEST(bit, kr_rol16_MACRO)
{
    EXPECT_XINTEQ(0xe6a1, kr_rol16(0x3cd4, 3));
    EXPECT_XINTEQ(0x879a, kr_rol16(0x3cd4, 13));
    EXPECT_XINTEQ(0x3cd4, kr_rol16(0x3cd4, 0));
}

TEST(bit, kr_rotl32)
{
    EXPECT_XINTEQ(0x0799aa80, kr_rotl32(0x00f33550, 3));
    EXPECT_XINTEQ(0x001e66aa, kr_rotl32(0x00f33550, 29));
    EXPECT_XINTEQ(0x00f33550, kr_rotl32(0x00f33550, 0));
}

TEST(bit, kr_rol32_MACRO)
{
    EXPECT_XINTEQ(0x0799aa80, kr_rol32(0x00f33550, 3));
    EXPECT_XINTEQ(0x001e66aa, kr_rol32(0x00f33550, 29));
    EXPECT_XINTEQ(0x00f33550, kr_rol32(0x00f33550, 0));
}

TEST(bit, kr_rotl64)
{
    EXPECT_XINT64EQ(UINT64_C(0x2a99ff800799aa80), kr_rotl64(UINT64_C(0x05533ff000f33550), 3));
    EXPECT_XINT64EQ(UINT64_C(0x001e66aa00aa67fe), kr_rotl64(UINT64_C(0x05533ff000f33550), 29));
    EXPECT_XINT64EQ(UINT64_C(0x0799aa802a99ff80), kr_rotl64(UINT64_C(0x05533ff000f33550), 35));
    EXPECT_XINT64EQ(UINT64_C(0x00aa67fe001e66aa), kr_rotl64(UINT64_C(0x05533ff000f33550), 61));
    EXPECT_XINT64EQ(UINT64_C(0x05533ff000f33550), kr_rotl64(UINT64_C(0x05533ff000f33550), 0));
}

TEST(bit, kr_rol64_MACRO)
{
    EXPECT_XINT64EQ(UINT64_C(0x2a99ff800799aa80), kr_rol64(UINT64_C(0x05533ff000f33550), 3));
    EXPECT_XINT64EQ(UINT64_C(0x001e66aa00aa67fe), kr_rol64(UINT64_C(0x05533ff000f33550), 29));
    EXPECT_XINT64EQ(UINT64_C(0x0799aa802a99ff80), kr_rol64(UINT64_C(0x05533ff000f33550), 35));
    EXPECT_XINT64EQ(UINT64_C(0x00aa67fe001e66aa), kr_rol64(UINT64_C(0x05533ff000f33550), 61));
    EXPECT_XINT64EQ(UINT64_C(0x05533ff000f33550), kr_rol64(UINT64_C(0x05533ff000f33550), 0));
}

//------------------------------------------------------------------------------

TEST(bit, kr_rotr16)
{
    EXPECT_XINTEQ(0x879a, kr_rotr16(0x3cd4, 3));
    EXPECT_XINTEQ(0xe6a1, kr_rotr16(0x3cd4, 13));
    EXPECT_XINTEQ(0x3cd4, kr_rotr16(0x3cd4, 0));
}

TEST(bit, kr_ror16_MACRO)
{
    EXPECT_XINTEQ(0x879a, kr_ror16(0x3cd4, 3));
    EXPECT_XINTEQ(0xe6a1, kr_ror16(0x3cd4, 13));
    EXPECT_XINTEQ(0x3cd4, kr_ror16(0x3cd4, 0));
}

TEST(bit, kr_rotr32)
{
    EXPECT_XINTEQ(0x001e66aa, kr_rotr32(0x00f33550, 3));
    EXPECT_XINTEQ(0x0799aa80, kr_rotr32(0x00f33550, 29));
    EXPECT_XINTEQ(0x00f33550, kr_rotr32(0x00f33550, 0));
}

TEST(bit, kr_ror32_MACRO)
{
    EXPECT_XINTEQ(0x001e66aa, kr_ror32(0x00f33550, 3));
    EXPECT_XINTEQ(0x0799aa80, kr_ror32(0x00f33550, 29));
    EXPECT_XINTEQ(0x00f33550, kr_ror32(0x00f33550, 0));
}

TEST(bit, kr_rotr64)
{
    EXPECT_XINT64EQ(UINT64_C(0x00aa67fe001e66aa), kr_rotr64(UINT64_C(0x05533ff000f33550), 3));
    EXPECT_XINT64EQ(UINT64_C(0x0799aa802a99ff80), kr_rotr64(UINT64_C(0x05533ff000f33550), 29));
    EXPECT_XINT64EQ(UINT64_C(0x001e66aa00aa67fe), kr_rotr64(UINT64_C(0x05533ff000f33550), 35));
    EXPECT_XINT64EQ(UINT64_C(0x2a99ff800799aa80), kr_rotr64(UINT64_C(0x05533ff000f33550), 61));
    EXPECT_XINT64EQ(UINT64_C(0x05533ff000f33550), kr_rotr64(UINT64_C(0x05533ff000f33550), 0));
}

TEST(bit, kr_ror64_MACRO)
{
    EXPECT_XINT64EQ(UINT64_C(0x00aa67fe001e66aa), kr_ror64(UINT64_C(0x05533ff000f33550), 3));
    EXPECT_XINT64EQ(UINT64_C(0x0799aa802a99ff80), kr_ror64(UINT64_C(0x05533ff000f33550), 29));
    EXPECT_XINT64EQ(UINT64_C(0x001e66aa00aa67fe), kr_ror64(UINT64_C(0x05533ff000f33550), 35));
    EXPECT_XINT64EQ(UINT64_C(0x2a99ff800799aa80), kr_ror64(UINT64_C(0x05533ff000f33550), 61));
    EXPECT_XINT64EQ(UINT64_C(0x05533ff000f33550), kr_ror64(UINT64_C(0x05533ff000f33550), 0));
}

//------------------------------------------------------------------------------

TEST(bit, kr_countl_zero32)
{
    EXPECT_UINT64EQ(0, kr_countl_zero32(0x80000000));
    EXPECT_UINT64EQ(16, kr_countl_zero32(0x00008000));
    EXPECT_UINT64EQ(32, kr_countl_zero32(0x00000000));
}

TEST(bit, kr_clz32_MACRO)
{
    EXPECT_UINTEQ(0, kr_clz32(0x80000000));
    EXPECT_UINTEQ(16, kr_clz32(0x00008000));
    EXPECT_UINTEQ(32, kr_clz32(0x00000000));
}

TEST(bit, kr_countl_zero64)
{
    EXPECT_INTEQ(0, kr_countl_zero64(0x8000000000000000));
    EXPECT_INTEQ(16, kr_countl_zero64(0x0000800000000000));
    EXPECT_INTEQ(32, kr_countl_zero64(0x0000000080000000));
    EXPECT_INTEQ(48, kr_countl_zero64(0x0000000000008000));
    EXPECT_INTEQ(64, kr_countl_zero64(0x0000000000000000));
}

TEST(bit, kr_clz64_MACRO)
{
    EXPECT_INTEQ(0, kr_clz64(0x8000000000000000));
    EXPECT_INTEQ(16, kr_clz64(0x0000800000000000));
    EXPECT_INTEQ(32, kr_clz64(0x0000000080000000));
    EXPECT_INTEQ(48, kr_clz64(0x0000000000008000));
    EXPECT_INTEQ(64, kr_clz64(0x0000000000000000));
}

//------------------------------------------------------------------------------

TEST(bit, kr_countl_one32)
{
    EXPECT_INTEQ(0, kr_countl_one32(0x00000000));
    EXPECT_INTEQ(16, kr_countl_one32(0xFFFF7FFF));
    EXPECT_INTEQ(32, kr_countl_one32(0xFFFFFFFF));
}

TEST(bit, kr_clo32_MACRO)
{
    EXPECT_INTEQ(0, kr_clo32(UINT32_C(0x00000000)));
    EXPECT_INTEQ(16, kr_clo32(UINT32_C(0xFFFF7FFF)));
    EXPECT_INTEQ(32, kr_clo32(UINT32_C(0xFFFFFFFF)));
}

TEST(bit, kr_countl_one64)
{
    EXPECT_INTEQ(0, kr_countl_one64(0x0000000000000000));
    EXPECT_INTEQ(16, kr_countl_one64(0xFFFF7FFFFFFFFFFF));
    EXPECT_INTEQ(32, kr_countl_one64(0xFFFFFFFF7FFFFFFF));
    EXPECT_INTEQ(48, kr_countl_one64(0xFFFFFFFFFFFF7FFF));
    EXPECT_INTEQ(64, kr_countl_one64(0xFFFFFFFFFFFFFFFF));
}

TEST(bit, kr_clo64_MACRO)
{
    EXPECT_INTEQ(0, kr_clo64(0x0000000000000000));
    EXPECT_INTEQ(16, kr_clo64(0xFFFF7FFFFFFFFFFF));
    EXPECT_INTEQ(32, kr_clo64(0xFFFFFFFF7FFFFFFF));
    EXPECT_INTEQ(48, kr_clo64(0xFFFFFFFFFFFF7FFF));
    EXPECT_INTEQ(64, kr_clo64(0xFFFFFFFFFFFFFFFF));
}

//------------------------------------------------------------------------------

TEST(bit, kr_countr_zero32)
{
    EXPECT_INTEQ(0, kr_countr_zero32(0xFFFFFFFF));
    EXPECT_INTEQ(16, kr_countr_zero32(0x00010000));
    EXPECT_INTEQ(32, kr_countr_zero32(0x00000000));
}

TEST(bit, kr_ctz32_MACRO)
{
    EXPECT_INTEQ(0, kr_ctz32(0xFFFFFFFF));
    EXPECT_INTEQ(16, kr_ctz32(0x00010000));
    EXPECT_INTEQ(32, kr_ctz32(0x00000000));
}

TEST(bit, kr_countr_zero64)
{
    EXPECT_INTEQ(0, kr_countr_zero64(0xFFFFFFFFFFFFFFFF));
    EXPECT_INTEQ(16, kr_countr_zero64(0x0000000000010000));
    EXPECT_INTEQ(32, kr_countr_zero64(0x0000000100000000));
    EXPECT_INTEQ(48, kr_countr_zero64(0x0001000000000000));
    EXPECT_INTEQ(64, kr_countr_zero64(0x0000000000000000));
}

TEST(bit, kr_ctz64_MACRO)
{
    EXPECT_INTEQ(0, kr_ctz64(0xFFFFFFFFFFFFFFFF));
    EXPECT_INTEQ(16, kr_ctz64(0x0000000000010000));
    EXPECT_INTEQ(32, kr_ctz64(0x0000000100000000));
    EXPECT_INTEQ(48, kr_ctz64(0x0001000000000000));
    EXPECT_INTEQ(64, kr_ctz64(0x0000000000000000));
}

//------------------------------------------------------------------------------

TEST(bit, kr_countr_one32)
{
    EXPECT_INTEQ(0, kr_countr_one32(0x00000000));
    EXPECT_INTEQ(16, kr_countr_one32(0xFFFEFFFF));
    EXPECT_INTEQ(32, kr_countr_one32(0xFFFFFFFF));
}

TEST(bit, kr_cto32_MACRO)
{
    EXPECT_INTEQ(0, kr_cto32(UINT32_C(0x00000000)));
    EXPECT_INTEQ(16, kr_cto32(UINT32_C(0xFFFEFFFF)));
    EXPECT_INTEQ(32, kr_cto32(UINT32_C(0xFFFFFFFF)));
}

TEST(bit, kr_countr_one64)
{
    EXPECT_INTEQ(0, kr_countr_one64(UINT64_C(0x0000000000000000)));
    EXPECT_INTEQ(16, kr_countr_one64(UINT64_C(0xFFFFFFFFFFFEFFFF)));
    EXPECT_INTEQ(32, kr_countr_one64(UINT64_C(0xFFFFFFFEFFFFFFFF)));
    EXPECT_INTEQ(48, kr_countr_one64(UINT64_C(0xFFFEFFFFFFFFFFFF)));
    EXPECT_INTEQ(64, kr_countr_one64(UINT64_C(0xFFFFFFFFFFFFFFFF)));
}

TEST(bit, kr_cto64_MACRO)
{
    EXPECT_INTEQ(0, kr_cto64(UINT64_C(0x0000000000000000)));
    EXPECT_INTEQ(16, kr_cto64(UINT64_C(0xFFFFFFFFFFFEFFFF)));
    EXPECT_INTEQ(32, kr_cto64(UINT64_C(0xFFFFFFFEFFFFFFFF)));
    EXPECT_INTEQ(48, kr_cto64(UINT64_C(0xFFFEFFFFFFFFFFFF)));
    EXPECT_INTEQ(64, kr_cto64(UINT64_C(0xFFFFFFFFFFFFFFFF)));
}

//------------------------------------------------------------------------------

TEST(bit, kr_popcount16)
{
    EXPECT_INTEQ(6, kr_popcount16(0x04c7));
}

TEST(bit, kr_popcnt16_MACRO)
{
    EXPECT_INTEQ(6, kr_popcnt16(0x04c7));
}

TEST(bit, kr_popcount32)
{
    EXPECT_INTEQ(6, kr_popcount32(0x04c7));
    EXPECT_INTEQ(12, kr_popcount32(0x04c704c7));
}

TEST(bit, kr_popcnt32_MACRO)
{
    EXPECT_INTEQ(6, kr_popcnt32(0x04c7));
    EXPECT_INTEQ(12, kr_popcnt32(0x04c704c7));
}

TEST(bit, kr_popcount64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  // !defined(UINT64_MAX)
    EXPECT_INTEQ(6, kr_popcount64(0x04c7));
    EXPECT_INTEQ(12, kr_popcount64(0x04c704c7));
    EXPECT_INTEQ(24, kr_popcount64(0x04c704c704c704c7));
#endif // !defined(UINT64_MAX)
}

TEST(bit, kr_popcnt64_MACRO)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  // !defined(UINT64_MAX)
    EXPECT_INTEQ(6, kr_popcnt64(0x04c7));
    EXPECT_INTEQ(12, kr_popcnt64(0x04c704c7));
    EXPECT_INTEQ(24, kr_popcnt64(0x04c704c704c704c7));
#endif // !defined(UINT64_MAX)
}

//------------------------------------------------------------------------------

SUITE(bit)
{
    SUITE_TEST(bit, kr_byteswap16);
    SUITE_TEST(bit, kr_bswap16_MACRO);
    SUITE_TEST(bit, kr_byteswap32);
    SUITE_TEST(bit, kr_bswap32_MACRO);
    SUITE_TEST(bit, kr_byteswap64);
    SUITE_TEST(bit, kr_bswap64_MACRO);
    SUITE_TEST(bit, kr_has_single_bit8);
    SUITE_TEST(bit, kr_has_single_bit16);
    SUITE_TEST(bit, kr_has_single_bit32);
    SUITE_TEST(bit, kr_has_single_bit64);
    SUITE_TEST(bit, kr_bit_ceil32);
    SUITE_TEST(bit, kr_bit_ceil64);
    SUITE_TEST(bit, kr_bit_floor32);
    SUITE_TEST(bit, kr_bit_floor64);
    SUITE_TEST(bit, kr_bit_width32);
    SUITE_TEST(bit, kr_bit_width64);
    SUITE_TEST(bit, kr_rotl16);
    SUITE_TEST(bit, kr_rol16_MACRO);
    SUITE_TEST(bit, kr_rotl32);
    SUITE_TEST(bit, kr_rol32_MACRO);
    SUITE_TEST(bit, kr_rotl64);
    SUITE_TEST(bit, kr_rol64_MACRO);
    SUITE_TEST(bit, kr_rotr16);
    SUITE_TEST(bit, kr_ror16_MACRO);
    SUITE_TEST(bit, kr_rotr32);
    SUITE_TEST(bit, kr_ror32_MACRO);
    SUITE_TEST(bit, kr_rotr64);
    SUITE_TEST(bit, kr_ror64_MACRO);
    SUITE_TEST(bit, kr_countl_zero32);
    SUITE_TEST(bit, kr_clz32_MACRO);
    SUITE_TEST(bit, kr_countl_zero64);
    SUITE_TEST(bit, kr_clz64_MACRO);
    SUITE_TEST(bit, kr_countl_one32);
    SUITE_TEST(bit, kr_clo32_MACRO);
    SUITE_TEST(bit, kr_countl_one64);
    SUITE_TEST(bit, kr_clo64_MACRO);
    SUITE_TEST(bit, kr_countr_zero32);
    SUITE_TEST(bit, kr_ctz32_MACRO);
    SUITE_TEST(bit, kr_countr_zero64);
    SUITE_TEST(bit, kr_ctz64_MACRO);
    SUITE_TEST(bit, kr_countr_one32);
    SUITE_TEST(bit, kr_cto32_MACRO);
    SUITE_TEST(bit, kr_countr_one64);
    SUITE_TEST(bit, kr_cto64_MACRO);
    SUITE_TEST(bit, kr_popcount16);
    SUITE_TEST(bit, kr_popcnt16_MACRO);
    SUITE_TEST(bit, kr_popcount32);
    SUITE_TEST(bit, kr_popcnt32_MACRO);
    SUITE_TEST(bit, kr_popcount64);
    SUITE_TEST(bit, kr_popcnt64_MACRO);
}

#pragma warning(pop)
