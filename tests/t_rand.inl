//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "zztest.h"

#include "krrand.h"

TEST(rand, jsf8)
{
    struct kr_jsf8_ctx_s ctx;
    kr_jsf8_srand(&ctx, 201u);

    EXPECT_UINTEQ(241u, kr_jsf8_rand(&ctx));
    EXPECT_UINTEQ(19u, kr_jsf8_rand(&ctx));
    EXPECT_UINTEQ(37u, kr_jsf8_rand(&ctx));
    EXPECT_UINTEQ(167u, kr_jsf8_rand(&ctx));
}

TEST(rand, jsf16)
{
    struct kr_jsf16_ctx_s ctx;
    kr_jsf16_srand(&ctx, 1993);

    EXPECT_UINTEQ(61817, kr_jsf16_rand(&ctx));
    EXPECT_UINTEQ(46200, kr_jsf16_rand(&ctx));
    EXPECT_UINTEQ(53286, kr_jsf16_rand(&ctx));
    EXPECT_UINTEQ(28861, kr_jsf16_rand(&ctx));
}

TEST(rand, jsf32)
{
    struct kr_jsf32_ctx_s ctx;
    kr_jsf32_srand(&ctx, 1993);

    EXPECT_UINTEQ(1323812269, kr_jsf32_rand(&ctx));
    EXPECT_UINTEQ(1220648136, kr_jsf32_rand(&ctx));
    EXPECT_UINTEQ(3832904144, kr_jsf32_rand(&ctx));
    EXPECT_UINTEQ(178104823, kr_jsf32_rand(&ctx));
}

TEST(rand, jsf64)
{
#if !defined(UINT64_MAX)
    SKIP();
#else
    struct kr_jsf64_ctx_s ctx;
    kr_jsf64_srand(&ctx, 1993);

    EXPECT_UINT64EQ(UINT64_C(866240615393628892), kr_jsf64_rand(&ctx));
    EXPECT_UINT64EQ(UINT64_C(4516034199495256649), kr_jsf64_rand(&ctx));
    EXPECT_UINT64EQ(UINT64_C(10153722626954818142), kr_jsf64_rand(&ctx));
    EXPECT_UINT64EQ(UINT64_C(16680399593301785108), kr_jsf64_rand(&ctx));
#endif // !defined(UINT64_MAX)
}

SUITE(rand)
{
    SUITE_TEST(rand, jsf8);
    SUITE_TEST(rand, jsf16);
    SUITE_TEST(rand, jsf32);
    SUITE_TEST(rand, jsf64);
}
