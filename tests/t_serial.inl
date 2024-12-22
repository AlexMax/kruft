//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "zztest.h"

#include "krserial.h"

//------------------------------------------------------------------------------

TEST(serial, kr_load_u16le)
{
    unsigned char buf[2] = {0x88, 0x99};
    EXPECT_UINTEQ(0x9988, kr_load_u16le(buf));
}

TEST(serial, kr_load_u16be)
{
    unsigned char buf[2] = {0x99, 0x88};
    EXPECT_UINTEQ(0x9988, kr_load_u16be(buf));
}

//------------------------------------------------------------------------------

TEST(serial, kr_load_u32le)
{
    unsigned char buf[4] = {0x88, 0x99, 0xaa, 0xbb};
    EXPECT_UINTEQ(0xbbaa9988, kr_load_u32le(buf));
}

TEST(serial, kr_load_u32be)
{
    unsigned char buf[4] = {0xbb, 0xaa, 0x99, 0x88};
    EXPECT_UINTEQ(0xbbaa9988, kr_load_u32be(buf));
}

//------------------------------------------------------------------------------

TEST(serial, kr_load_u64le)
{
#if !defined(UINT64_MAX)
    SKIP();
#else
    unsigned char buf[8] = {0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    EXPECT_UINT64EQ(0xffeeddccbbaa9988, kr_load_u64le(buf));
#endif // !defined(UINT64_MAX)
}

TEST(serial, kr_load_u64be)
{
#if !defined(UINT64_MAX)
    SKIP();
#else
    unsigned char buf[8] = {0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88};
    EXPECT_UINT64EQ(0xffeeddccbbaa9988, kr_load_u64be(buf));
#endif // !defined(UINT64_MAX)
}

//------------------------------------------------------------------------------

TEST(serial, kr_store_u16le)
{
    unsigned i = 0;
    unsigned char buf[2] = {0x00, 0x00};
    kr_store_u16le(buf, 0x9988);

    EXPECT_UINTEQ(0x88, buf[i++]);
    EXPECT_UINTEQ(0x99, buf[i++]);
}

TEST(serial, kr_store_u16be)
{
    unsigned i = 0;
    unsigned char buf[2] = {0x00, 0x00};
    kr_store_u16be(buf, 0x9988);

    EXPECT_UINTEQ(0x99, buf[i++]);
    EXPECT_UINTEQ(0x88, buf[i++]);
}

//------------------------------------------------------------------------------

TEST(serial, kr_store_u32le)
{
    unsigned i = 0;
    unsigned char buf[4] = {0x00, 0x00, 0x00, 0x00};
    kr_store_u32le(buf, 0xbbaa9988);

    EXPECT_UINTEQ(0x88, buf[i++]);
    EXPECT_UINTEQ(0x99, buf[i++]);
    EXPECT_UINTEQ(0xaa, buf[i++]);
    EXPECT_UINTEQ(0xbb, buf[i++]);
}

TEST(serial, kr_store_u32be)
{
    unsigned i = 0;
    unsigned char buf[4] = {0x00, 0x00, 0x00, 0x00};
    kr_store_u32be(buf, 0xbbaa9988);

    EXPECT_UINTEQ(0xbb, buf[i++]);
    EXPECT_UINTEQ(0xaa, buf[i++]);
    EXPECT_UINTEQ(0x99, buf[i++]);
    EXPECT_UINTEQ(0x88, buf[i++]);
}

//------------------------------------------------------------------------------

TEST(serial, kr_store_u64le)
{

#if !defined(UINT64_MAX)
    SKIP();
#else
    unsigned i = 0;
    unsigned char buf[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    kr_store_u64le(buf, 0xffeeddccbbaa9988);

    EXPECT_UINTEQ(0x88, buf[i++]);
    EXPECT_UINTEQ(0x99, buf[i++]);
    EXPECT_UINTEQ(0xaa, buf[i++]);
    EXPECT_UINTEQ(0xbb, buf[i++]);
    EXPECT_UINTEQ(0xcc, buf[i++]);
    EXPECT_UINTEQ(0xdd, buf[i++]);
    EXPECT_UINTEQ(0xee, buf[i++]);
    EXPECT_UINTEQ(0xff, buf[i++]);
#endif // !defined(UINT64_MAX)
}

TEST(serial, kr_store_u64be)
{
#if !defined(UINT64_MAX)
    SKIP();
#else
    unsigned i = 0;
    unsigned char buf[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    kr_store_u64be(buf, 0xffeeddccbbaa9988);

    EXPECT_UINTEQ(0xff, buf[i++]);
    EXPECT_UINTEQ(0xee, buf[i++]);
    EXPECT_UINTEQ(0xdd, buf[i++]);
    EXPECT_UINTEQ(0xcc, buf[i++]);
    EXPECT_UINTEQ(0xbb, buf[i++]);
    EXPECT_UINTEQ(0xaa, buf[i++]);
    EXPECT_UINTEQ(0x99, buf[i++]);
    EXPECT_UINTEQ(0x88, buf[i++]);
#endif // !defined(UINT64_MAX)
}

SUITE(serial)
{
    SUITE_TEST(serial, kr_load_u16le);
    SUITE_TEST(serial, kr_load_u16be);
    SUITE_TEST(serial, kr_load_u32le);
    SUITE_TEST(serial, kr_load_u32be);
    SUITE_TEST(serial, kr_load_u64le);
    SUITE_TEST(serial, kr_load_u64be);
    SUITE_TEST(serial, kr_store_u16le);
    SUITE_TEST(serial, kr_store_u16be);
    SUITE_TEST(serial, kr_store_u32le);
    SUITE_TEST(serial, kr_store_u32be);
    SUITE_TEST(serial, kr_store_u64le);
    SUITE_TEST(serial, kr_store_u64be);
}
