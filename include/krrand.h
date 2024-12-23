//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

//
// Deterministic PRNG that gives consistent results across platforms.
//
// Uses Bob Jenkins's Small Fast PRNG, also known as jsf:
//  <http://burtleburtle.net/bob/rand/smallprng.html>
//
// The 16-bit variant is by Melissa E. O'Neill:
//  <https://www.pcg-random.org/posts/bob-jenkins-small-prng-passes-practrand.html>
//
// jsf is well studied, has variations that work at all integer sizes, and
// comes with a recommended seeding routine out of the box.
//

#pragma once

#include "./krconfig.h"

#include "./krbit.h" // bit rotation
#include "./krint.h"

//------------------------------------------------------------------------------

struct kr_jsf8_ctx_s
{
    uint8_t a, b, c, d;
};

struct kr_jsf16_ctx_s
{
    uint16_t a, b, c, d;
};

struct kr_jsf32_ctx_s
{
    uint32_t a, b, c, d;
};

struct kr_jsf64_ctx_s
{
    uint64_t a, b, c, d;
};

KR_CONSTEXPR uint8_t kr_jsf8_rand(struct kr_jsf8_ctx_s *x)
{
    uint8_t e = x->a - kr_rotl8(x->b, 1);
    x->a = x->b ^ kr_rotl8(x->c, 4);
    x->b = x->c + x->d;
    x->c = x->d + e;
    x->d = e + x->a;
    return x->d;
}

KR_CONSTEXPR void kr_jsf8_srand(struct kr_jsf8_ctx_s *x, uint8_t seed)
{
    int i = 0;

    x->a = 0xed, x->b = x->c = x->d = seed;
    for (i = 0; i < 20; i++)
    {
        (void)kr_jsf8_rand(x);
    }
}

KR_CONSTEXPR uint16_t kr_jsf16_rand(struct kr_jsf16_ctx_s *x)
{
    uint16_t e = x->a - kr_rotl16(x->b, 13);
    x->a = x->b ^ kr_rotl16(x->c, 8);
    x->b = x->c + x->d;
    x->c = x->d + e;
    x->d = e + x->a;
    return x->d;
}

KR_CONSTEXPR void kr_jsf16_srand(struct kr_jsf16_ctx_s *x, uint16_t seed)
{
    int i = 0;

    x->a = 0x5eed, x->b = x->c = x->d = seed;
    for (i = 0; i < 20; i++)
    {
        (void)kr_jsf16_rand(x);
    }
}

KR_CONSTEXPR uint32_t kr_jsf32_rand(struct kr_jsf32_ctx_s *x)
{
    uint32_t e = x->a - kr_rotl32(x->b, 27);
    x->a = x->b ^ kr_rotl32(x->c, 17);
    x->b = x->c + x->d;
    x->c = x->d + e;
    x->d = e + x->a;
    return x->d;
}

KR_CONSTEXPR void kr_jsf32_srand(struct kr_jsf32_ctx_s *x, uint32_t seed)
{
    int i = 0;

    x->a = 0xf1ea5eed, x->b = x->c = x->d = seed;
    for (i = 0; i < 20; i++)
    {
        (void)kr_jsf32_rand(x);
    }
}

KR_CONSTEXPR uint64_t kr_jsf64_rand(struct kr_jsf64_ctx_s *x)
{
    uint64_t e = x->a - kr_rotl64(x->b, 7);
    x->a = x->b ^ kr_rotl64(x->c, 13);
    x->b = x->c + kr_rotl64(x->d, 37);
    x->c = x->d + e;
    x->d = e + x->a;
    return x->d;
}

KR_CONSTEXPR void kr_jsf64_srand(struct kr_jsf64_ctx_s *x, uint64_t seed)
{
    int i = 0;

    x->a = 0xf1ea5eed, x->b = x->c = x->d = seed;
    for (i = 0; i < 20; i++)
    {
        (void)kr_jsf64_rand(x);
    }
}
