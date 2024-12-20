//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

//
// Bit-manipulation functions, C++20's <bit> for all.
//
// This header is allowed to break the "no cleverness" rule, since these
// functions generally need to be as fast as possible.  That said, the
// individual functions should still allow for easy copy-pasting.
//

#pragma once

#include "./krconfig.h"

#include "./krbool.h"
#include "./krint.h"

//------------------------------------------------------------------------------

/**
 * @brief Byteswap a 16-bit value.
 */
KR_CONSTEXPR uint16_t kr_byteswap16(uint16_t x)
{
    return ((x & UINT16_C(0xFF00)) >> UINT16_C(8)) | //
           ((x & UINT16_C(0x00FF)) << UINT16_C(8));  //
}

/**
 * @brief Byteswap a 32-bit value.
 */
KR_CONSTEXPR uint32_t kr_byteswap32(uint32_t x)
{
    return ((x & UINT32_C(0xFF000000)) >> UINT32_C(24)) | //
           ((x & UINT32_C(0x00FF0000)) >> UINT32_C(8)) |  //
           ((x & UINT32_C(0x0000FF00)) << UINT32_C(8)) |  //
           ((x & UINT32_C(0x000000FF)) << UINT32_C(24));  //
}

#if defined(UINT64_MAX)

/**
 * @brief Byteswap a 64-bit value.
 */
KR_CONSTEXPR uint64_t kr_byteswap64(uint64_t x)
{
    return ((x & UINT64_C(0xFF00000000000000)) >> UINT64_C(56)) | //
           ((x & UINT64_C(0x00FF000000000000)) >> UINT64_C(40)) | //
           ((x & UINT64_C(0x0000FF0000000000)) >> UINT64_C(24)) | //
           ((x & UINT64_C(0x000000FF00000000)) >> UINT64_C(8)) |  //
           ((x & UINT64_C(0x00000000FF000000)) << UINT64_C(8)) |  //
           ((x & UINT64_C(0x0000000000FF0000)) << UINT64_C(24)) | //
           ((x & UINT64_C(0x000000000000FF00)) << UINT64_C(40)) | //
           ((x & UINT64_C(0x00000000000000FF)) << UINT64_C(56));  //
}

#endif // defined(UINT64_MAX)

#if (KR_MSC_VER)
#define kr_bswap16(x) (_byteswap_ushort(x))
#define kr_bswap32(x) (_byteswap_ulong(x))
#if defined(UINT64_MAX)
#define kr_bswap64(x) (_byteswap_uint64(x))
#endif // defined(UINT64_MAX)
#elif (KR_GNUC)
#define kr_bswap16(x) (__builtin_bswap16(x))
#define kr_bswap32(x) (__builtin_bswap32(x))
#if defined(UINT64_MAX)
#define kr_bswap64(x) (__builtin_bswap64(x))
#endif // defined(UINT64_MAX)
#else
#define kr_bswap16(x) (kr_byteswap16(x))
#define kr_bswap32(x) (kr_byteswap32(x))
#if defined(UINT64_MAX)
#define kr_bswap64(x) (kr_byteswap64(x))
#endif // defined(UINT64_MAX)
#endif

//------------------------------------------------------------------------------

KR_CONSTEXPR bool kr_has_single_bit8(uint8_t x) KR_NOEXCEPT
{
    return x && !(x & (x - 1));
}

KR_CONSTEXPR bool kr_has_single_bit16(uint16_t x) KR_NOEXCEPT
{
    return x && !(x & (x - 1));
}

KR_CONSTEXPR bool kr_has_single_bit32(uint32_t x) KR_NOEXCEPT
{
    return x && !(x & (x - 1));
}

KR_CONSTEXPR bool kr_has_single_bit64(uint64_t x) KR_NOEXCEPT
{
    return x && !(x & (x - 1));
}

#if 0

//------------------------------------------------------------------------------

KR_CONSTEXPR bool kr_bit_ceil(uint32_t x) KR_NOEXCEPT
{
}

//------------------------------------------------------------------------------

KR_CONSTEXPR bool kr_bit_floor(uint32_t x) KR_NOEXCEPT
{
}

//------------------------------------------------------------------------------

KR_CONSTEXPR bool kr_bit_width(uint32_t x) KR_NOEXCEPT
{
}

#endif

//------------------------------------------------------------------------------

KR_CONSTEXPR uint32_t kr_rotl32(uint32_t x, int c) KR_NOEXCEPT
{
    return (x << c) | (x >> (-c & 0x1F));
}

KR_CONSTEXPR uint64_t kr_rotl64(uint64_t x, int c) KR_NOEXCEPT
{
    return (x << c) | (x >> (-c & 0x3F));
}

#if (KR_MSC_VER)
#define kr_rol32(x, c) (_rotl((x), (c)))
#define kr_rol64(x, c) (_rotl64((x), (c)))
#else
#define kr_rol32(x, c) (kr_rotl32((x), (c)))
#define kr_rol64(x, c) (kr_rotl64((x), (c)))
#endif

//------------------------------------------------------------------------------

KR_CONSTEXPR uint32_t kr_rotr32(uint32_t x, int c) KR_NOEXCEPT
{
    return (x >> c) | (x << (-c & 0x1F));
}

KR_CONSTEXPR uint64_t kr_rotr64(uint64_t x, int c) KR_NOEXCEPT
{
    return (x >> c) | (x << (-c & 0x3F));
}

#if (KR_MSC_VER)
#define kr_ror32(x, c) (_rotr((x), (c)))
#define kr_ror64(x, c) (_rotr64((x), (c)))
#else
#define kr_ror32(x, c) (kr_rotr32((x), (c)))
#define kr_ror64(x, c) (kr_rotr64((x), (c)))
#endif

//------------------------------------------------------------------------------

KR_CONSTEXPR int kr_countl_zero32(uint32_t x) KR_NOEXCEPT
{
    int rvo = 0;
    uint32_t mask = 0x80000000;

    for (; mask; mask >>= 1, rvo++)
    {
        if (x & mask)
        {
            return rvo;
        }
    }

    return rvo;
}

#if (KR_GNUC || KR_CLANG) // Prefer __builtin_clz on clang-cl
#define kr_clz32(x) ((x) != 0 ? __builtin_clz(x) : 32)
#elif (KR_MSC_VER)
#include <intrin.h>
KR_FORCEINLINE int kr_clz32_detail_(unsigned long x)
{
    unsigned long index;
    return _BitScanReverse(&index, x) ? 31 - KR_CASTS(int, index) : 32;
}
#define kr_clz32(x) (kr_clz32_detail_(x))
#else
#define kr_clz32(x) (kr_countl_zero32(x))
#endif

//------------------------------------------------------------------------------

KR_CONSTEXPR int kr_countl_one32(uint32_t x) KR_NOEXCEPT
{
    int rvo = 0;
    uint32_t mask = 0x80000000;

    for (; mask; mask >>= 1, rvo++)
    {
        if (!(x & mask))
        {
            return rvo;
        }
    }

    return rvo;
}

#if (KR_GNUC || KR_CLANG) // Prefer __builtin_clz on clang-cl
#define kr_clo32(x) ((x) != 0xFFFFFFFF ? __builtin_clz(~(x)) : 32)
#elif (KR_MSC_VER)
#define kr_clo32(x) (kr_clz32_detail_(~(x)))
#else
#define kr_clo32(x) (kr_countl_one32(x))
#endif

//------------------------------------------------------------------------------

KR_CONSTEXPR int kr_countr_zero32(uint32_t x) KR_NOEXCEPT
{
    if (x == 0)
    {
        return sizeof(x) * 8;
    }

    int rvo = 0;

    for (; x; x >>= 1, rvo++)
    {
        if (x & 0x01)
        {
            return rvo;
        }
    }

    return rvo;
}

#if (KR_GNUC || KR_CLANG) // Prefer __builtin_ctz on clang-cl
#define kr_ctz32(x) ((x) != 0 ? __builtin_ctz(x) : 32)
#elif (KR_MSC_VER)
#include <intrin.h>
KR_FORCEINLINE int kr_ctz32_detail_(unsigned long x)
{
    unsigned long index;
    return _BitScanForward(&index, x) ? KR_CASTS(int, index) : 32;
}
#define kr_ctz32(x) (kr_ctz32_detail_(x))
#else
#define kr_ctz32(x) (kr_countr_zero32(x))
#endif

//------------------------------------------------------------------------------

KR_CONSTEXPR int kr_countr_one32(uint32_t x) KR_NOEXCEPT
{
    int rvo = 0;

    for (; x; x >>= 1, rvo++)
    {
        if (!(x & 0x01))
        {
            return rvo;
        }
    }

    return rvo;
}

#if (KR_GNUC || KR_CLANG) // Prefer __builtin_ctz on clang-cl
#define kr_cto32(x) ((x) != 0xFFFFFFFF ? __builtin_ctz(~(x)) : 32)
#elif (KR_MSC_VER)
#define kr_cto32(x) (kr_ctz32_detail_(~(x)))
#else
#define kr_cto32(x) (kr_countr_zero32(x))
#endif

//------------------------------------------------------------------------------

KR_CONSTEXPR int kr_popcount16(uint16_t x) KR_NOEXCEPT
{
    int rvo = 0;

    for (; x; x >>= 1)
    {
        rvo += x & 0x1;
    }

    return rvo;
}

KR_CONSTEXPR int kr_popcount32(uint32_t x) KR_NOEXCEPT
{
    int rvo = 0;

    for (; x; x >>= 1)
    {
        rvo += x & 0x1;
    }

    return rvo;
}

KR_CONSTEXPR int kr_popcount64(uint64_t x) KR_NOEXCEPT
{
    int rvo = 0;

    for (; x; x >>= 1)
    {
        rvo += x & 0x1;
    }

    return rvo;
}

#if (KR_MSC_VER)
#include <intrin.h>
#define kr_popcnt16(x) (__popcnt16(x))
#define kr_popcnt32(x) (__popcnt(x))
#define kr_popcnt64(x) (__popcnt64(x))
#elif (KR_GNUC)
#define kr_popcnt16(x) (__builtin_popcount(x))
#define kr_popcnt32(x) (__builtin_popcount(x))
#define kr_popcnt64(x) (__builtin_popcountll(x))
#else
#define kr_popcnt16(x) (kr_popcount16(x))
#define kr_popcnt32(x) (kr_popcount32(x))
#define kr_popcnt64(x) (kr_popcount64(x))
#endif
