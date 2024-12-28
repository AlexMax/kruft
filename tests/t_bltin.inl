/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "zztest.h"

#include "krbltin.h"

/******************************************************************************/

TEST(bltin, kr_rbit8_MACRO)
{
    EXPECT_UINTEQ(0x35u, kr_rbit8(0xacu));
}

TEST(bltin, kr_rbit16_MACRO)
{
    EXPECT_UINTEQ(0x0f35u, kr_rbit16(0xacf0u));
}

TEST(bltin, kr_rbit32_MACRO)
{
    EXPECT_UINTEQ(0x00ff0f35u, kr_rbit32(0xacf0ff00u));
}

TEST(bltin, kr_rbit64_MACRO)
{
    EXPECT_UINT64EQ(0x0000ffff00ff0f35u, kr_rbit64(0xacf0ff00ffff0000u));
}

/******************************************************************************/

TEST(bltin, kr_bswap16_MACRO)
{
    EXPECT_UINTEQ(0x2301, kr_bswap16(0x0123));
}

TEST(bltin, kr_bswap32_MACRO)
{
    EXPECT_UINTEQ(0x67452301, kr_bswap32(0x01234567));
}

TEST(bltin, kr_bswap64_MACRO)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_UINT64EQ(UINT64_C(0xEFCDAB8967452301), kr_bswap64(0x0123456789ABCDEF));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bltin, kr_rol8_MACRO)
{
    EXPECT_XINTEQ(0xa6u, kr_rol8(0xd4, 3));
    EXPECT_XINTEQ(0x9au, kr_rol8(0xd4, 5));
    EXPECT_XINTEQ(0xd4u, kr_rol8(0xd4, 0));
}

TEST(bltin, kr_rol16_MACRO)
{
    EXPECT_XINTEQ(0xe6a1, kr_rol16(0x3cd4, 3));
    EXPECT_XINTEQ(0x879a, kr_rol16(0x3cd4, 13));
    EXPECT_XINTEQ(0x3cd4, kr_rol16(0x3cd4, 0));
}

TEST(bltin, kr_rol32_MACRO)
{
    EXPECT_XINTEQ(0x0799aa80, kr_rol32(0x00f33550, 3));
    EXPECT_XINTEQ(0x001e66aa, kr_rol32(0x00f33550, 29));
    EXPECT_XINTEQ(0x00f33550, kr_rol32(0x00f33550, 0));
}

TEST(bltin, kr_rol64_MACRO)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_XINT64EQ(UINT64_C(0x2a99ff800799aa80), kr_rol64(0x05533ff000f33550, 3));
    EXPECT_XINT64EQ(UINT64_C(0x001e66aa00aa67fe), kr_rol64(0x05533ff000f33550, 29));
    EXPECT_XINT64EQ(UINT64_C(0x0799aa802a99ff80), kr_rol64(0x05533ff000f33550, 35));
    EXPECT_XINT64EQ(UINT64_C(0x00aa67fe001e66aa), kr_rol64(0x05533ff000f33550, 61));
    EXPECT_XINT64EQ(UINT64_C(0x05533ff000f33550), kr_rol64(0x05533ff000f33550, 0));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bltin, kr_ror8_MACRO)
{
    EXPECT_XINTEQ(0x9au, kr_ror8(0xd4, 3));
    EXPECT_XINTEQ(0xa6u, kr_ror8(0xd4, 5));
    EXPECT_XINTEQ(0xd4u, kr_ror8(0xd4, 0));
}

TEST(bltin, kr_ror16_MACRO)
{
    EXPECT_XINTEQ(0x879a, kr_ror16(0x3cd4, 3));
    EXPECT_XINTEQ(0xe6a1, kr_ror16(0x3cd4, 13));
    EXPECT_XINTEQ(0x3cd4, kr_ror16(0x3cd4, 0));
}

TEST(bltin, kr_ror32_MACRO)
{
    EXPECT_XINTEQ(0x001e66aa, kr_ror32(0x00f33550, 3));
    EXPECT_XINTEQ(0x0799aa80, kr_ror32(0x00f33550, 29));
    EXPECT_XINTEQ(0x00f33550, kr_ror32(0x00f33550, 0));
}

TEST(bltin, kr_ror64_MACRO)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_XINT64EQ(UINT64_C(0x00aa67fe001e66aa), kr_ror64(0x05533ff000f33550, 3));
    EXPECT_XINT64EQ(UINT64_C(0x0799aa802a99ff80), kr_ror64(0x05533ff000f33550, 29));
    EXPECT_XINT64EQ(UINT64_C(0x001e66aa00aa67fe), kr_ror64(0x05533ff000f33550, 35));
    EXPECT_XINT64EQ(UINT64_C(0x2a99ff800799aa80), kr_ror64(0x05533ff000f33550, 61));
    EXPECT_XINT64EQ(UINT64_C(0x05533ff000f33550), kr_ror64(0x05533ff000f33550, 0));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bltin, kr_clz32_MACRO)
{
    EXPECT_INTEQ(0, kr_clz32(0x80000000));
    EXPECT_INTEQ(16, kr_clz32(0x00008000));
    EXPECT_INTEQ(32, kr_clz32(0x00000000));
}

TEST(bltin, kr_clz64_MACRO)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_INTEQ(0, kr_clz64(0x8000000000000000));
    EXPECT_INTEQ(16, kr_clz64(0x0000800000000000));
    EXPECT_INTEQ(32, kr_clz64(0x0000000080000000));
    EXPECT_INTEQ(48, kr_clz64(0x0000000000008000));
    EXPECT_INTEQ(64, kr_clz64(0x0000000000000000));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bltin, kr_clo32_MACRO)
{
    EXPECT_INTEQ(0, kr_clo32(0x00000000));
    EXPECT_INTEQ(16, kr_clo32(0xFFFF7FFF));
    EXPECT_INTEQ(32, kr_clo32(0xFFFFFFFF));
}

TEST(bltin, kr_clo64_MACRO)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_INTEQ(0, kr_clo64(0x0000000000000000));
    EXPECT_INTEQ(16, kr_clo64(0xFFFF7FFFFFFFFFFF));
    EXPECT_INTEQ(32, kr_clo64(0xFFFFFFFF7FFFFFFF));
    EXPECT_INTEQ(48, kr_clo64(0xFFFFFFFFFFFF7FFF));
    EXPECT_INTEQ(64, kr_clo64(0xFFFFFFFFFFFFFFFF));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bltin, kr_ctz32_MACRO)
{
    EXPECT_INTEQ(0, kr_ctz32(0xFFFFFFFF));
    EXPECT_INTEQ(16, kr_ctz32(0x00010000));
    EXPECT_INTEQ(32, kr_ctz32(0x00000000));
}

TEST(bltin, kr_ctz64_MACRO)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_INTEQ(0, kr_ctz64(0xFFFFFFFFFFFFFFFF));
    EXPECT_INTEQ(16, kr_ctz64(0x0000000000010000));
    EXPECT_INTEQ(32, kr_ctz64(0x0000000100000000));
    EXPECT_INTEQ(48, kr_ctz64(0x0001000000000000));
    EXPECT_INTEQ(64, kr_ctz64(0x0000000000000000));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bltin, kr_cto32_MACRO)
{
    EXPECT_INTEQ(0, kr_cto32(0x00000000));
    EXPECT_INTEQ(16, kr_cto32(0xFFFEFFFF));
    EXPECT_INTEQ(32, kr_cto32(0xFFFFFFFF));
}

TEST(bltin, kr_cto64_MACRO)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_INTEQ(0, kr_cto64(0x0000000000000000));
    EXPECT_INTEQ(16, kr_cto64(0xFFFFFFFFFFFEFFFF));
    EXPECT_INTEQ(32, kr_cto64(0xFFFFFFFEFFFFFFFF));
    EXPECT_INTEQ(48, kr_cto64(0xFFFEFFFFFFFFFFFF));
    EXPECT_INTEQ(64, kr_cto64(0xFFFFFFFFFFFFFFFF));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

TEST(bltin, kr_popcnt16_MACRO)
{
    EXPECT_INTEQ(6, kr_popcnt16(0x04c7));
}

TEST(bltin, kr_popcnt32_MACRO)
{
    EXPECT_INTEQ(6, kr_popcnt32(0x04c7));
    EXPECT_INTEQ(12, kr_popcnt32(0x04c704c7));
}

TEST(bltin, kr_popcnt64_MACRO)
{
#if !defined(UINT64_MAX)
    SKIP();
#else  /* !defined(UINT64_MAX) */
    EXPECT_INTEQ(6, kr_popcnt64(0x04c7));
    EXPECT_INTEQ(12, kr_popcnt64(0x04c704c7));
    EXPECT_INTEQ(24, kr_popcnt64(0x04c704c704c704c7));
#endif /* !defined(UINT64_MAX) */
}

/******************************************************************************/

SUITE(bltin)
{
    SUITE_TEST(bltin, kr_rbit8_MACRO);
    SUITE_TEST(bltin, kr_rbit16_MACRO);
    SUITE_TEST(bltin, kr_rbit32_MACRO);
    SUITE_TEST(bltin, kr_rbit64_MACRO);
    SUITE_TEST(bltin, kr_bswap16_MACRO);
    SUITE_TEST(bltin, kr_bswap32_MACRO);
    SUITE_TEST(bltin, kr_bswap64_MACRO);
    SUITE_TEST(bltin, kr_rol8_MACRO);
    SUITE_TEST(bltin, kr_rol16_MACRO);
    SUITE_TEST(bltin, kr_rol32_MACRO);
    SUITE_TEST(bltin, kr_rol64_MACRO);
    SUITE_TEST(bltin, kr_ror8_MACRO);
    SUITE_TEST(bltin, kr_ror16_MACRO);
    SUITE_TEST(bltin, kr_ror32_MACRO);
    SUITE_TEST(bltin, kr_ror64_MACRO);
    SUITE_TEST(bltin, kr_clz32_MACRO);
    SUITE_TEST(bltin, kr_clz64_MACRO);
    SUITE_TEST(bltin, kr_clo32_MACRO);
    SUITE_TEST(bltin, kr_clo64_MACRO);
    SUITE_TEST(bltin, kr_ctz32_MACRO);
    SUITE_TEST(bltin, kr_ctz64_MACRO);
    SUITE_TEST(bltin, kr_cto32_MACRO);
    SUITE_TEST(bltin, kr_cto64_MACRO);
    SUITE_TEST(bltin, kr_popcnt16_MACRO);
    SUITE_TEST(bltin, kr_popcnt32_MACRO);
    SUITE_TEST(bltin, kr_popcnt64_MACRO);
}
