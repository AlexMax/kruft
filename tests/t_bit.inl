/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "zztest.h"

#include "krbit.h"
#include "krbltin.h"
#include "krint.h"

#pragma warning(push)
#pragma warning(disable : 4127)

/******************************************************************************/

TEST(bit, kr_bitreverse8)
{
    EXPECT_UINTEQ(0x35u, kr_bitreverse8(0xacu));
}

TEST(bit, kr_bitreverse16)
{
    EXPECT_UINTEQ(0x0f35u, kr_bitreverse16(0xacf0u));
}

TEST(bit, kr_bitreverse32)
{
    EXPECT_UINTEQ(0x00ff0f35u, kr_bitreverse32(0xacf0ff00u));
}

TEST(bit, kr_bitreverse64)
{
    EXPECT_UINTEQ(0x0000ffff00ff0f35u, kr_bitreverse64(0xacf0ff00ffff0000u));
}

/******************************************************************************/

TEST(bit, kr_byteswap16)
{
    EXPECT_UINTEQ(0x2301, kr_byteswap16(0x0123));
}

TEST(bit, kr_byteswap32)
{
    EXPECT_UINTEQ(0x67452301, kr_byteswap32(0x01234567));
}

TEST(bit, kr_byteswap64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_UINTEQ(UINT64_C(0xEFCDAB8967452301), kr_byteswap64(0x0123456789ABCDEF));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bit, kr_has_single_bit8)
{
    EXPECT_BOOLEQ(false, kr_has_single_bit8(0x00));
    EXPECT_BOOLEQ(false, kr_has_single_bit8(0xFF));
    EXPECT_BOOLEQ(true, kr_has_single_bit8(0x80));
}

TEST(bit, kr_has_single_bit16)
{
    EXPECT_BOOLEQ(false, kr_has_single_bit16(0x00));
    EXPECT_BOOLEQ(false, kr_has_single_bit16(0xFF));
    EXPECT_BOOLEQ(true, kr_has_single_bit16(0x80));
}

TEST(bit, kr_has_single_bit32)
{
    EXPECT_BOOLEQ(false, kr_has_single_bit32(0x00));
    EXPECT_BOOLEQ(false, kr_has_single_bit32(0xFF));
    EXPECT_BOOLEQ(true, kr_has_single_bit32(0x80));
}

TEST(bit, kr_has_single_bit64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_BOOLEQ(false, kr_has_single_bit64(0x00));
    EXPECT_BOOLEQ(false, kr_has_single_bit64(0xFF));
    EXPECT_BOOLEQ(true, kr_has_single_bit64(0x80));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bit, kr_bit_ceil8)
{
    EXPECT_UINTEQ(1, kr_bit_ceil8(0));
    EXPECT_UINTEQ(1, kr_bit_ceil8(1));
    EXPECT_UINTEQ(2, kr_bit_ceil8(2));
    EXPECT_UINTEQ(4, kr_bit_ceil8(3));
    EXPECT_UINTEQ(4, kr_bit_ceil8(4));
    EXPECT_UINTEQ(8, kr_bit_ceil8(5));
    EXPECT_UINTEQ(INT8_MAX + UINT8_C(1), kr_bit_ceil8(INT8_MAX));
}

TEST(bit, kr_bit_ceil16)
{
    EXPECT_UINTEQ(1, kr_bit_ceil16(0));
    EXPECT_UINTEQ(1, kr_bit_ceil16(1));
    EXPECT_UINTEQ(2, kr_bit_ceil16(2));
    EXPECT_UINTEQ(4, kr_bit_ceil16(3));
    EXPECT_UINTEQ(4, kr_bit_ceil16(4));
    EXPECT_UINTEQ(8, kr_bit_ceil16(5));
    EXPECT_UINTEQ(INT16_MAX + UINT16_C(1), kr_bit_ceil16(INT16_MAX));
}

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
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_UINTEQ(1, kr_bit_ceil64(0));
    EXPECT_UINTEQ(1, kr_bit_ceil64(1));
    EXPECT_UINTEQ(2, kr_bit_ceil64(2));
    EXPECT_UINTEQ(4, kr_bit_ceil64(3));
    EXPECT_UINTEQ(4, kr_bit_ceil64(4));
    EXPECT_UINTEQ(8, kr_bit_ceil64(5));
    EXPECT_UINTEQ(INT32_MAX + UINT64_C(1), kr_bit_ceil64(INT32_MAX));
    EXPECT_UINTEQ(INT64_MAX + UINT64_C(1), kr_bit_ceil64(INT64_MAX));
#endif /* !defined(UINT64_MAX) */
}

TEST(bit, kr_bit_floor8)
{
    EXPECT_UINTEQ(0, kr_bit_floor8(0));
    EXPECT_UINTEQ(1, kr_bit_floor8(1));
    EXPECT_UINTEQ(2, kr_bit_floor8(2));
    EXPECT_UINTEQ(2, kr_bit_floor8(3));
    EXPECT_UINTEQ(4, kr_bit_floor8(4));
    EXPECT_UINTEQ(4, kr_bit_floor8(5));
    EXPECT_UINTEQ(INT8_MAX + UINT8_C(1), kr_bit_floor8(UINT8_MAX));
}

TEST(bit, kr_bit_floor16)
{
    EXPECT_UINTEQ(0, kr_bit_floor16(0));
    EXPECT_UINTEQ(1, kr_bit_floor16(1));
    EXPECT_UINTEQ(2, kr_bit_floor16(2));
    EXPECT_UINTEQ(2, kr_bit_floor16(3));
    EXPECT_UINTEQ(4, kr_bit_floor16(4));
    EXPECT_UINTEQ(4, kr_bit_floor16(5));
    EXPECT_UINTEQ(INT16_MAX + UINT16_C(1), kr_bit_floor16(UINT16_MAX));
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
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_UINTEQ(0, kr_bit_floor64(0));
    EXPECT_UINTEQ(1, kr_bit_floor64(1));
    EXPECT_UINTEQ(2, kr_bit_floor64(2));
    EXPECT_UINTEQ(2, kr_bit_floor64(3));
    EXPECT_UINTEQ(4, kr_bit_floor64(4));
    EXPECT_UINTEQ(4, kr_bit_floor64(5));
    EXPECT_UINTEQ(INT32_MAX + UINT64_C(1), kr_bit_floor64(UINT32_MAX));
    EXPECT_UINTEQ(INT64_MAX + UINT64_C(1), kr_bit_floor64(UINT64_MAX));
#endif /* !defined(UINT64_MAX) */
}

TEST(bit, kr_bit_width8)
{
    EXPECT_UINTEQ(0, kr_bit_width8(0));
    EXPECT_UINTEQ(1, kr_bit_width8(1));
    EXPECT_UINTEQ(2, kr_bit_width8(2));
    EXPECT_UINTEQ(2, kr_bit_width8(3));
    EXPECT_UINTEQ(3, kr_bit_width8(4));
    EXPECT_UINTEQ(8, kr_bit_width8(UINT8_MAX));
}

TEST(bit, kr_bit_width16)
{
    EXPECT_UINTEQ(0, kr_bit_width16(0));
    EXPECT_UINTEQ(1, kr_bit_width16(1));
    EXPECT_UINTEQ(2, kr_bit_width16(2));
    EXPECT_UINTEQ(2, kr_bit_width16(3));
    EXPECT_UINTEQ(3, kr_bit_width16(4));
    EXPECT_UINTEQ(16, kr_bit_width16(UINT16_MAX));
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
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_UINTEQ(0, kr_bit_width64(0));
    EXPECT_UINTEQ(1, kr_bit_width64(1));
    EXPECT_UINTEQ(2, kr_bit_width64(2));
    EXPECT_UINTEQ(2, kr_bit_width64(3));
    EXPECT_UINTEQ(3, kr_bit_width64(4));
    EXPECT_UINTEQ(32, kr_bit_width64(UINT32_MAX));
    EXPECT_UINTEQ(64, kr_bit_width64(UINT64_MAX));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bit, kr_rotate_left8)
{
    EXPECT_XINTEQ(0xa6u, kr_rotate_left8(0xd4, 3));
    EXPECT_XINTEQ(0x9au, kr_rotate_left8(0xd4, 5));
    EXPECT_XINTEQ(0xd4u, kr_rotate_left8(0xd4, 0));
}

TEST(bit, kr_rotate_left16)
{
    EXPECT_XINTEQ(0xe6a1, kr_rotate_left16(0x3cd4, 3));
    EXPECT_XINTEQ(0x879a, kr_rotate_left16(0x3cd4, 13));
    EXPECT_XINTEQ(0x3cd4, kr_rotate_left16(0x3cd4, 0));
}

TEST(bit, kr_rotate_left32)
{
    EXPECT_XINTEQ(0x0799aa80, kr_rotate_left32(0x00f33550, 3));
    EXPECT_XINTEQ(0x001e66aa, kr_rotate_left32(0x00f33550, 29));
    EXPECT_XINTEQ(0x00f33550, kr_rotate_left32(0x00f33550, 0));
}

TEST(bit, kr_rotate_left64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_XINTEQ(UINT64_C(0x2a99ff800799aa80), kr_rotate_left64(0x05533ff000f33550, 3));
    EXPECT_XINTEQ(UINT64_C(0x001e66aa00aa67fe), kr_rotate_left64(0x05533ff000f33550, 29));
    EXPECT_XINTEQ(UINT64_C(0x0799aa802a99ff80), kr_rotate_left64(0x05533ff000f33550, 35));
    EXPECT_XINTEQ(UINT64_C(0x00aa67fe001e66aa), kr_rotate_left64(0x05533ff000f33550, 61));
    EXPECT_XINTEQ(UINT64_C(0x05533ff000f33550), kr_rotate_left64(0x05533ff000f33550, 0));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bit, kr_rotate_right8)
{
    EXPECT_XINTEQ(0x9au, kr_rotate_right8(0xd4, 3));
    EXPECT_XINTEQ(0xa6u, kr_rotate_right8(0xd4, 5));
    EXPECT_XINTEQ(0xd4u, kr_rotate_right8(0xd4, 0));
}

TEST(bit, kr_rotate_right16)
{
    EXPECT_XINTEQ(0x879a, kr_rotate_right16(0x3cd4, 3));
    EXPECT_XINTEQ(0xe6a1, kr_rotate_right16(0x3cd4, 13));
    EXPECT_XINTEQ(0x3cd4, kr_rotate_right16(0x3cd4, 0));
}

TEST(bit, kr_rotate_right32)
{
    EXPECT_XINTEQ(0x001e66aa, kr_rotate_right32(0x00f33550, 3));
    EXPECT_XINTEQ(0x0799aa80, kr_rotate_right32(0x00f33550, 29));
    EXPECT_XINTEQ(0x00f33550, kr_rotate_right32(0x00f33550, 0));
}

TEST(bit, kr_rotate_right64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_XINTEQ(UINT64_C(0x00aa67fe001e66aa), kr_rotate_right64(0x05533ff000f33550, 3));
    EXPECT_XINTEQ(UINT64_C(0x0799aa802a99ff80), kr_rotate_right64(0x05533ff000f33550, 29));
    EXPECT_XINTEQ(UINT64_C(0x001e66aa00aa67fe), kr_rotate_right64(0x05533ff000f33550, 35));
    EXPECT_XINTEQ(UINT64_C(0x2a99ff800799aa80), kr_rotate_right64(0x05533ff000f33550, 61));
    EXPECT_XINTEQ(UINT64_C(0x05533ff000f33550), kr_rotate_right64(0x05533ff000f33550, 0));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bit, kr_leading_zeros8)
{
    EXPECT_UINTEQ(0, kr_leading_zeros8(0x80));
    EXPECT_UINTEQ(4, kr_leading_zeros8(0x08));
    EXPECT_UINTEQ(8, kr_leading_zeros8(0x00));
}

TEST(bit, kr_leading_zeros16)
{
    EXPECT_UINTEQ(0, kr_leading_zeros16(0x8000));
    EXPECT_UINTEQ(8, kr_leading_zeros16(0x0080));
    EXPECT_UINTEQ(16, kr_leading_zeros16(0x0000));
}

TEST(bit, kr_leading_zeros32)
{
    EXPECT_UINTEQ(0, kr_leading_zeros32(0x80000000));
    EXPECT_UINTEQ(16, kr_leading_zeros32(0x00008000));
    EXPECT_UINTEQ(32, kr_leading_zeros32(0x00000000));
}

TEST(bit, kr_leading_zeros64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_UINTEQ(0, kr_leading_zeros64(0x8000000000000000));
    EXPECT_UINTEQ(16, kr_leading_zeros64(0x0000800000000000));
    EXPECT_UINTEQ(32, kr_leading_zeros64(0x0000000080000000));
    EXPECT_UINTEQ(48, kr_leading_zeros64(0x0000000000008000));
    EXPECT_UINTEQ(64, kr_leading_zeros64(0x0000000000000000));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bit, kr_leading_ones8)
{
    EXPECT_UINTEQ(0, kr_leading_ones8(0x00));
    EXPECT_UINTEQ(4, kr_leading_ones8(0xF7));
    EXPECT_UINTEQ(8, kr_leading_ones8(0xFF));
}

TEST(bit, kr_leading_ones16)
{
    EXPECT_UINTEQ(0, kr_leading_ones16(0x0000));
    EXPECT_UINTEQ(8, kr_leading_ones16(0xFF7F));
    EXPECT_UINTEQ(16, kr_leading_ones16(0xFFFF));
}

TEST(bit, kr_leading_ones32)
{
    EXPECT_UINTEQ(0, kr_leading_ones32(0x00000000));
    EXPECT_UINTEQ(16, kr_leading_ones32(0xFFFF7FFF));
    EXPECT_UINTEQ(32, kr_leading_ones32(0xFFFFFFFF));
}

TEST(bit, kr_leading_ones64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_UINTEQ(0, kr_leading_ones64(0x0000000000000000));
    EXPECT_UINTEQ(16, kr_leading_ones64(0xFFFF7FFFFFFFFFFF));
    EXPECT_UINTEQ(32, kr_leading_ones64(0xFFFFFFFF7FFFFFFF));
    EXPECT_UINTEQ(48, kr_leading_ones64(0xFFFFFFFFFFFF7FFF));
    EXPECT_UINTEQ(64, kr_leading_ones64(0xFFFFFFFFFFFFFFFF));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bit, kr_trailing_zeros8)
{
    EXPECT_UINTEQ(0, kr_trailing_zeros8(0xFF));
    EXPECT_UINTEQ(4, kr_trailing_zeros8(0x10));
    EXPECT_UINTEQ(8, kr_trailing_zeros8(0x00));
}

TEST(bit, kr_trailing_zeros16)
{
    EXPECT_UINTEQ(0, kr_trailing_zeros16(0xFFFF));
    EXPECT_UINTEQ(8, kr_trailing_zeros16(0x0100));
    EXPECT_UINTEQ(16, kr_trailing_zeros16(0x0000));
}

TEST(bit, kr_trailing_zeros32)
{
    EXPECT_UINTEQ(0, kr_trailing_zeros32(0xFFFFFFFF));
    EXPECT_UINTEQ(16, kr_trailing_zeros32(0x00010000));
    EXPECT_UINTEQ(32, kr_trailing_zeros32(0x00000000));
}

TEST(bit, kr_trailing_zeros64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_UINTEQ(0, kr_trailing_zeros64(0xFFFFFFFFFFFFFFFF));
    EXPECT_UINTEQ(16, kr_trailing_zeros64(0x0000000000010000));
    EXPECT_UINTEQ(32, kr_trailing_zeros64(0x0000000100000000));
    EXPECT_UINTEQ(48, kr_trailing_zeros64(0x0001000000000000));
    EXPECT_UINTEQ(64, kr_trailing_zeros64(0x0000000000000000));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bit, kr_trailing_ones8)
{
    EXPECT_UINTEQ(0, kr_trailing_ones8(0x00));
    EXPECT_UINTEQ(4, kr_trailing_ones8(0xEF));
    EXPECT_UINTEQ(8, kr_trailing_ones8(0xFF));
}

TEST(bit, kr_trailing_ones16)
{
    EXPECT_UINTEQ(0, kr_trailing_ones16(0x0000));
    EXPECT_UINTEQ(8, kr_trailing_ones16(0xFEFF));
    EXPECT_UINTEQ(16, kr_trailing_ones16(0xFFFF));
}

TEST(bit, kr_trailing_ones32)
{
    EXPECT_UINTEQ(0, kr_trailing_ones32(0x00000000));
    EXPECT_UINTEQ(16, kr_trailing_ones32(0xFFFEFFFF));
    EXPECT_UINTEQ(32, kr_trailing_ones32(0xFFFFFFFF));
}

TEST(bit, kr_trailing_ones64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_UINTEQ(0, kr_trailing_ones64(0x0000000000000000));
    EXPECT_UINTEQ(16, kr_trailing_ones64(0xFFFFFFFFFFFEFFFF));
    EXPECT_UINTEQ(32, kr_trailing_ones64(0xFFFFFFFEFFFFFFFF));
    EXPECT_UINTEQ(48, kr_trailing_ones64(0xFFFEFFFFFFFFFFFF));
    EXPECT_UINTEQ(64, kr_trailing_ones64(0xFFFFFFFFFFFFFFFF));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bit, kr_count_ones8)
{
    EXPECT_UINTEQ(5, kr_count_ones8(0xe6));
}

TEST(bit, kr_count_ones16)
{
    EXPECT_UINTEQ(6, kr_count_ones16(0x04c7));
}

TEST(bit, kr_count_ones32)
{
    EXPECT_UINTEQ(6, kr_count_ones32(0x04c7));
    EXPECT_UINTEQ(12, kr_count_ones32(0x04c704c7));
}

TEST(bit, kr_count_ones64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_UINTEQ(6, kr_count_ones64(0x04c7));
    EXPECT_UINTEQ(12, kr_count_ones64(0x04c704c7));
    EXPECT_UINTEQ(24, kr_count_ones64(0x04c704c704c704c7));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

SUITE(bit)
{
    SUITE_TEST(bit, kr_bitreverse8);
    SUITE_TEST(bit, kr_bitreverse16);
    SUITE_TEST(bit, kr_bitreverse32);
    SUITE_TEST(bit, kr_bitreverse64);
    SUITE_TEST(bit, kr_byteswap16);
    SUITE_TEST(bit, kr_byteswap32);
    SUITE_TEST(bit, kr_byteswap64);
    SUITE_TEST(bit, kr_has_single_bit8);
    SUITE_TEST(bit, kr_has_single_bit16);
    SUITE_TEST(bit, kr_has_single_bit32);
    SUITE_TEST(bit, kr_has_single_bit64);
    SUITE_TEST(bit, kr_bit_ceil8);
    SUITE_TEST(bit, kr_bit_ceil16);
    SUITE_TEST(bit, kr_bit_ceil32);
    SUITE_TEST(bit, kr_bit_ceil64);
    SUITE_TEST(bit, kr_bit_floor8);
    SUITE_TEST(bit, kr_bit_floor16);
    SUITE_TEST(bit, kr_bit_floor32);
    SUITE_TEST(bit, kr_bit_floor64);
    SUITE_TEST(bit, kr_bit_width8);
    SUITE_TEST(bit, kr_bit_width16);
    SUITE_TEST(bit, kr_bit_width32);
    SUITE_TEST(bit, kr_bit_width64);
    SUITE_TEST(bit, kr_rotate_left8);
    SUITE_TEST(bit, kr_rotate_left16);
    SUITE_TEST(bit, kr_rotate_left32);
    SUITE_TEST(bit, kr_rotate_left64);
    SUITE_TEST(bit, kr_rotate_right8);
    SUITE_TEST(bit, kr_rotate_right16);
    SUITE_TEST(bit, kr_rotate_right32);
    SUITE_TEST(bit, kr_rotate_right64);
    SUITE_TEST(bit, kr_leading_zeros8);
    SUITE_TEST(bit, kr_leading_zeros16);
    SUITE_TEST(bit, kr_leading_zeros32);
    SUITE_TEST(bit, kr_leading_zeros64);
    SUITE_TEST(bit, kr_leading_ones8);
    SUITE_TEST(bit, kr_leading_ones16);
    SUITE_TEST(bit, kr_leading_ones32);
    SUITE_TEST(bit, kr_leading_ones64);
    SUITE_TEST(bit, kr_trailing_zeros8);
    SUITE_TEST(bit, kr_trailing_zeros16);
    SUITE_TEST(bit, kr_trailing_zeros32);
    SUITE_TEST(bit, kr_trailing_zeros64);
    SUITE_TEST(bit, kr_trailing_ones8);
    SUITE_TEST(bit, kr_trailing_ones16);
    SUITE_TEST(bit, kr_trailing_ones32);
    SUITE_TEST(bit, kr_trailing_ones64);
    SUITE_TEST(bit, kr_count_ones8);
    SUITE_TEST(bit, kr_count_ones16);
    SUITE_TEST(bit, kr_count_ones32);
    SUITE_TEST(bit, kr_count_ones64);
}

#pragma warning(pop)
