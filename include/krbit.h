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

#include "./krdef.h"

#include "./krbool.h"
#include "./krint.h"

#if (KR_MSC_VER && !KR_CLANG)
#define KR_ORDER_LITTLE_ENDIAN (1)
#define KR_ORDER_BIG_ENDIAN (0)
#define KR_BYTE_ORDER (KR_ORDER_LITTLE_ENDIAN)
#else
#define KR_ORDER_LITTLE_ENDIAN (__ORDER_LITTLE_ENDIAN__)
#define KR_ORDER_BIG_ENDIAN (__ORDER_BIG_ENDIAN__)
#define KR_BYTE_ORDER (__BYTE_ORDER__)
#endif

//------------------------------------------------------------------------------

/**
 * @brief Byteswap a 16-bit value.
 */
#define kr_byteswap16(x) ((((x) & UINT16_C(0xFF00)) >> UINT16_C(8)) | (((x) & UINT16_C(0x00FF)) << UINT16_C(8)))

/**
 * @brief Byteswap a 32-bit value.
 */
#define kr_byteswap32(x)                                                                                               \
    (((x) & UINT32_C(0xFF000000)) >> UINT32_C(24) | (((x) & UINT32_C(0x00FF0000)) >> UINT32_C(8)) |                    \
     ((x) & UINT32_C(0x0000FF00)) << UINT32_C(8) | (((x) & UINT32_C(0x000000FF)) << UINT32_C(24)))

#if defined(UINT64_MAX)

/**
 * @brief Byteswap a 64-bit value.
 */
#define kr_byteswap64(x)                                                                                               \
    (((x) & UINT64_C(0xFF00000000000000)) >> UINT64_C(56) | ((x) & UINT64_C(0x00FF000000000000)) >> UINT64_C(40) |     \
     ((x) & UINT64_C(0x0000FF0000000000)) >> UINT64_C(24) | (((x) & UINT64_C(0x000000FF00000000)) >> UINT64_C(8)) |    \
     ((x) & UINT64_C(0x00000000FF000000)) << UINT64_C(8) | (((x) & UINT64_C(0x0000000000FF0000)) << UINT64_C(24)) |    \
     ((x) & UINT64_C(0x000000000000FF00)) << UINT64_C(40) | (((x) & UINT64_C(0x00000000000000FF)) << UINT64_C(56)))

#endif // defined(UINT64_MAX)

#if (KR_MSC_VER)
#define kr_bswap16(x) (_byteswap_ushort(x))
#define kr_bswap32(x) (_byteswap_ulong(x))
#if defined(UINT64_MAX)
#define kr_bswap64(x) (_byteswap_uint64(x))
#endif
#elif (KR_GNUC)
#define kr_bswap16(x) (__builtin_bswap16(x))
#define kr_bswap32(x) (__builtin_bswap32(x))
#if defined(UINT64_MAX)
#define kr_bswap64(x) (__builtin_bswap64(x))
#endif
#else

KR_CONSTEXPR uint16_t kr_bswap16(uint16_t x)
{
    return kr_byteswap16(x);
}

KR_CONSTEXPR uint32_t kr_bswap32(uint32_t x)
{
    return kr_byteswap32(x);
}

#if defined(UINT64_MAX)

KR_CONSTEXPR uint64_t kr_bswap64(uint64_t x)
{
    return kr_byteswap64(x);
}

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

//------------------------------------------------------------------------------

KR_CONSTEXPR uint8_t kr_rotl8(uint16_t x, int c) KR_NOEXCEPT
{
}

KR_CONSTEXPR uint16_t kr_rotl16(uint16_t x, int c) KR_NOEXCEPT
{
}

KR_CONSTEXPR uint32_t kr_rotl32(uint32_t x, int c) KR_NOEXCEPT
{
}

KR_CONSTEXPR uint32_t kr_rotl64(uint32_t x, int c) KR_NOEXCEPT
{
}

//------------------------------------------------------------------------------

KR_CONSTEXPR uint8_t kr_rotr8(uint16_t x, int c) KR_NOEXCEPT
{
}

KR_CONSTEXPR uint16_t kr_rotr16(uint16_t x, int c) KR_NOEXCEPT
{
}

KR_CONSTEXPR uint32_t kr_rotr32(uint32_t x, int c) KR_NOEXCEPT
{
}

KR_CONSTEXPR uint32_t kr_rotr64(uint32_t x, int c) KR_NOEXCEPT
{
}

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
        return sizeof(x) * CHAR_BIT;
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
