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

#if !defined(KRBIT_H)
#define KRBIT_H

#include "./krconfig.h"

#include "./krbool.h"
#include "./krint.h"

//------------------------------------------------------------------------------

#if (KR_MSC_VER >= 1300) // FIXME: Not in VC6, unsure when introduced.
#include <intrin.h>
#define KR_MSC_HAS_INTRIN_ (1)
#else // (KR_MSC_VER >= 1300)
#define KR_MSC_HAS_INTRIN_ (0)
#endif // (KR_MSC_VER >= 1300)

KR_CONSTEXPR int kr_countl_zero32(uint32_t x) KR_NOEXCEPT;
KR_CONSTEXPR int kr_popcount32(uint32_t x) KR_NOEXCEPT;
#if defined(UINT64_MAX)
KR_CONSTEXPR int kr_countl_zero64(uint64_t x) KR_NOEXCEPT;
KR_CONSTEXPR int kr_popcount64(uint64_t x) KR_NOEXCEPT;
#endif // defined(UINT64_MAX)

/**
 * @brief Byteswap a 16-bit value.
 */
KR_CONSTEXPR uint16_t kr_byteswap16(uint16_t x)
{
    return KR_CASTS(uint16_t, (x & 0xFF00) >> 8) | //
           KR_CASTS(uint16_t, (x & 0x00FF) << 8);  //
}

/**
 * @brief Byteswap a 32-bit value.
 */
KR_CONSTEXPR uint32_t kr_byteswap32(uint32_t x)
{
    return ((x & 0xFF000000) >> 24) | //
           ((x & 0x00FF0000) >> 8) |  //
           ((x & 0x0000FF00) << 8) |  //
           ((x & 0x000000FF) << 24);  //
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

#if (KR_MSC_HAS_INTRIN_)
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
#else  // (KR_MSC_HAS_INTRIN_)
#define kr_bswap16(x) (kr_byteswap16(x))
#define kr_bswap32(x) (kr_byteswap32(x))
#if defined(UINT64_MAX)
#define kr_bswap64(x) (kr_byteswap64(x))
#endif // defined(UINT64_MAX)
#endif // (KR_MSC_HAS_INTRIN_)

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

#if defined(UINT64_MAX)

KR_CONSTEXPR bool kr_has_single_bit64(uint64_t x) KR_NOEXCEPT
{
    return x && !(x & (x - 1));
}

#endif // defined(UINT64_MAX)

//------------------------------------------------------------------------------

/**
 * @brief Round up to the nearest power of two.
 *
 * @link http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2Float
 */
KR_CONSTEXPR uint32_t kr_bit_ceil32(uint32_t x) KR_NOEXCEPT
{
    if (x <= 1)
    {
        return 1;
    }

    x -= 1;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x += 1;
    return x;
}

#if defined(UINT64_MAX)

/**
 * @brief Round up to the nearest power of two.
 *
 * @link http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2Float
 */
KR_CONSTEXPR uint64_t kr_bit_ceil64(uint64_t x) KR_NOEXCEPT
{
    if (x <= 1)
    {
        return 1;
    }

    x -= 1;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    x += 1;
    return x;
}

#endif // defined(UINT64_MAX)

//------------------------------------------------------------------------------

/**
 * @brief Round down to the nearest power of two.
 *
 * @link https://www.amazon.com/Hackers-Delight-2nd-Henry-Warren-dp-0321842685/dp/0321842685
 */
KR_CONSTEXPR uint32_t kr_bit_floor32(uint32_t x) KR_NOEXCEPT
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x - (x >> 1);
}

#if defined(UINT64_MAX)

/**
 * @brief Round down to the nearest power of two.
 *
 * @link https://www.amazon.com/Hackers-Delight-2nd-Henry-Warren-dp-0321842685/dp/0321842685
 */
KR_CONSTEXPR uint64_t kr_bit_floor64(uint64_t x) KR_NOEXCEPT
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x - (x >> 1);
}

#endif // defined(UINT64_MAX)

//------------------------------------------------------------------------------

/**
 * @brief Count minimum number of bits needed to represent value.
 */
KR_CONSTEXPR int kr_bit_width32(uint32_t x) KR_NOEXCEPT
{
    return 32 - kr_countl_zero32(x);
}

#if defined(UINT64_MAX)

/**
 * @brief Count minimum number of bits needed to represent value.
 */
KR_CONSTEXPR int kr_bit_width64(uint64_t x) KR_NOEXCEPT
{
    return 64 - kr_countl_zero64(x);
}

#endif // defined(UINT64_MAX)

//------------------------------------------------------------------------------

KR_CONSTEXPR uint8_t kr_rotl8(uint8_t x, int c) KR_NOEXCEPT
{
    return KR_CASTS(uint8_t, x << c) | KR_CASTS(uint8_t, x >> (-c & 0x07));
}

KR_CONSTEXPR uint16_t kr_rotl16(uint16_t x, int c) KR_NOEXCEPT
{
    return KR_CASTS(uint16_t, x << c) | KR_CASTS(uint16_t, x >> (-c & 0x0F));
}

KR_CONSTEXPR uint32_t kr_rotl32(uint32_t x, int c) KR_NOEXCEPT
{
    return (x << c) | (x >> (-c & 0x1F));
}

#if defined(UINT64_MAX)

KR_CONSTEXPR uint64_t kr_rotl64(uint64_t x, int c) KR_NOEXCEPT
{
    return (x << c) | (x >> (-c & 0x3F));
}

#endif // #if defined(UINT64_MAX)

#if (KR_MSC_HAS_INTRIN_)
#define kr_rol8(x, c) (_rotl8((x), (c)))
#define kr_rol16(x, c) (_rotl16((x), (c)))
#define kr_rol32(x, c) (_rotl((x), (c)))
#if defined(UINT64_MAX)
#define kr_rol64(x, c) (_rotl64((x), (c)))
#endif // defined(UINT64_MAX)
#else  // (KR_MSC_HAS_INTRIN_)
#define kr_rol8(x, c) (kr_rotl8((x), (c)))
#define kr_rol16(x, c) (kr_rotl16((x), (c)))
#define kr_rol32(x, c) (kr_rotl32((x), (c)))
#if defined(UINT64_MAX)
#define kr_rol64(x, c) (kr_rotl64((x), (c)))
#endif // #if defined(UINT64_MAX)
#endif // (KR_MSC_HAS_INTRIN_)

//------------------------------------------------------------------------------

KR_CONSTEXPR uint8_t kr_rotr8(uint8_t x, int c) KR_NOEXCEPT
{
    return KR_CASTS(uint8_t, x >> c) | KR_CASTS(uint8_t, x << (-c & 0x07));
}

KR_CONSTEXPR uint16_t kr_rotr16(uint16_t x, int c) KR_NOEXCEPT
{
    return KR_CASTS(uint16_t, x >> c) | KR_CASTS(uint16_t, x << (-c & 0x0F));
}

KR_CONSTEXPR uint32_t kr_rotr32(uint32_t x, int c) KR_NOEXCEPT
{
    return (x >> c) | (x << (-c & 0x1F));
}

#if defined(UINT64_MAX)

KR_CONSTEXPR uint64_t kr_rotr64(uint64_t x, int c) KR_NOEXCEPT
{
    return (x >> c) | (x << (-c & 0x3F));
}

#endif // defined(UINT64_MAX)

#if (KR_MSC_HAS_INTRIN_)
#define kr_ror8(x, c) (_rotr8((x), (c)))
#define kr_ror16(x, c) (_rotr16((x), (c)))
#define kr_ror32(x, c) (_rotr((x), (c)))
#if defined(UINT64_MAX)
#define kr_ror64(x, c) (_rotr64((x), (c)))
#endif // defined(UINT64_MAX)
#else  // (KR_MSC_HAS_INTRIN_)
#define kr_ror8(x, c) (kr_rotr8((x), (c)))
#define kr_ror16(x, c) (kr_rotr16((x), (c)))
#define kr_ror32(x, c) (kr_rotr32((x), (c)))
#if defined(UINT64_MAX)
#define kr_ror64(x, c) (kr_rotr64((x), (c)))
#endif // defined(UINT64_MAX)
#endif // (KR_MSC_HAS_INTRIN_)

//------------------------------------------------------------------------------

/**
 * @brief Count leading (starting at MSB) zero bits.
 *
 * @link http://aggregate.ee.engr.uky.edu/MAGIC/#Leading%20Zero%20Count
 */
KR_CONSTEXPR int kr_countl_zero32(uint32_t x) KR_NOEXCEPT
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return 32 - kr_popcount32(x);
}

#if defined(UINT64_MAX)

/**
 * @brief Count leading (starting at MSB) zero bits.
 *
 * @link http://aggregate.ee.engr.uky.edu/MAGIC/#Leading%20Zero%20Count
 */
KR_CONSTEXPR int kr_countl_zero64(uint64_t x) KR_NOEXCEPT
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return 64 - kr_popcount64(x);
}

#endif // defined(UINT64_MAX)

#if (KR_GNUC || KR_CLANG) // Prefer __builtin_clz on clang-cl
#define kr_clz32(x) ((x) != 0 ? __builtin_clz(x) : 32)
#if defined(UINT64_MAX)
#define kr_clz64(x) ((x) != 0 ? __builtin_clzll(x) : 64)
#endif // defined(UINT64_MAX)
#elif (KR_MSC_HAS_INTRIN_)
KR_FORCEINLINE int kr_clz32_detail_(unsigned long x)
{
    unsigned long index;
    return _BitScanReverse(&index, x) ? 31 - KR_CASTS(int, index) : 32;
}
#define kr_clz32(x) (kr_clz32_detail_(x))
#if defined(UINT64_MAX)
KR_FORCEINLINE int kr_clz64_detail_(unsigned long long x)
{
    unsigned long index;
    return _BitScanReverse64(&index, x) ? 63 - KR_CASTS(int, index) : 64;
}
#define kr_clz64(x) (kr_clz64_detail_(x))
#endif // defined(UINT64_MAX)
#else  // (KR_GNUC || KR_CLANG)
#define kr_clz32(x) (kr_countl_zero32(x))
#if defined(UINT64_MAX)
#define kr_clz64(x) (kr_countl_zero64(x))
#endif // defined(UINT64_MAX)
#endif // (KR_GNUC || KR_CLANG)

//------------------------------------------------------------------------------

/**
 * @brief Count leading (starting at MSB) one bits.
 */
KR_CONSTEXPR int kr_countl_one32(uint32_t x) KR_NOEXCEPT
{
    x = ~x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return 32 - kr_popcount32(x);
}

#if defined(UINT64_MAX)

/**
 * @brief Count leading (starting at MSB) one bits.
 */
KR_CONSTEXPR int kr_countl_one64(uint64_t x) KR_NOEXCEPT
{
    x = ~x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return 64 - kr_popcount64(x);
}

#endif // defined(UINT64_MAX)

#if (KR_GNUC || KR_CLANG) // Prefer __builtin_clz on clang-cl
#define kr_clo32(x) ((x) != 0xFFFFFFFF ? __builtin_clz(~KR_CASTS(uint32_t, (x))) : 32)
#if defined(UINT64_MAX)
#define kr_clo64(x) ((x) != 0xFFFFFFFFFFFFFFFF ? __builtin_clzll(~KR_CASTS(uint64_t, (x))) : 64)
#endif // defined(UINT64_MAX)
#elif (KR_MSC_HAS_INTRIN_)
#define kr_clo32(x) (kr_clz32_detail_(~KR_CASTS(uint32_t, x)))
#if defined(UINT64_MAX)
#define kr_clo64(x) (kr_clz64_detail_(~KR_CASTS(uint64_t, x)))
#endif // defined(UINT64_MAX)
#else  // (KR_GNUC || KR_CLANG)
#define kr_clo32(x) (kr_countl_one32(x))
#if defined(UINT64_MAX)
#define kr_clo64(x) (kr_countl_one64(x))
#endif // defined(UINT64_MAX)
#endif // (KR_GNUC || KR_CLANG)

//------------------------------------------------------------------------------

/**
 * @brief Count trailing (starting at LSB) zero bits.
 */
KR_CONSTEXPR int kr_countr_zero32(uint32_t x) KR_NOEXCEPT
{
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    x |= x << 8;
    x |= x << 16;
    return 32 - kr_popcount32(x);
}

#if defined(UINT64_MAX)

/**
 * @brief Count trailing (starting at LSB) zero bits.
 */
KR_CONSTEXPR int kr_countr_zero64(uint64_t x) KR_NOEXCEPT
{
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    x |= x << 8;
    x |= x << 16;
    x |= x << 32;
    return 64 - kr_popcount64(x);
}

#endif // defined(UINT64_MAX)

#if (KR_GNUC || KR_CLANG) // Prefer __builtin_ctz on clang-cl
#define kr_ctz32(x) ((x) != 0 ? __builtin_ctz(x) : 32)
#if defined(UINT64_MAX)
#define kr_ctz64(x) ((x) != 0 ? __builtin_ctzll(x) : 64)
#endif // defined(UINT64_MAX)
#elif (KR_MSC_HAS_INTRIN_)
KR_FORCEINLINE int kr_ctz32_detail_(unsigned long x)
{
    unsigned long index;
    return _BitScanForward(&index, x) ? KR_CASTS(int, index) : 32;
}
#define kr_ctz32(x) (kr_ctz32_detail_(x))
#if defined(UINT64_MAX)
KR_FORCEINLINE int kr_ctz64_detail_(unsigned long long x)
{
    unsigned long index;
    return _BitScanForward64(&index, x) ? KR_CASTS(int, index) : 64;
}
#define kr_ctz64(x) (kr_ctz64_detail_(x))
#endif // defined(UINT64_MAX)
#else  // (KR_GNUC || KR_CLANG)
#define kr_ctz32(x) (kr_countr_zero32(x))
#if defined(UINT64_MAX)
#define kr_ctz64(x) (kr_countr_zero64(x))
#endif // defined(UINT64_MAX)
#endif // (KR_GNUC || KR_CLANG)

//------------------------------------------------------------------------------

/**
 * @brief Count trailing (starting at LSB) one bits.
 */
KR_CONSTEXPR int kr_countr_one32(uint32_t x) KR_NOEXCEPT
{
    x = ~x;
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    x |= x << 8;
    x |= x << 16;
    return 32 - kr_popcount32(x);
}

#if defined(UINT64_MAX)

/**
 * @brief Count trailing (starting at LSB) one bits.
 */
KR_CONSTEXPR int kr_countr_one64(uint64_t x) KR_NOEXCEPT
{
    x = ~x;
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    x |= x << 8;
    x |= x << 16;
    x |= x << 32;
    return 64 - kr_popcount64(x);
}

#endif // defined(UINT64_MAX)

#if (KR_GNUC || KR_CLANG) // Prefer __builtin_ctz on clang-cl
#define kr_cto32(x) ((x) != UINT32_C(0xFFFFFFFF) ? __builtin_ctz(~KR_CASTS(uint32_t, (x))) : 32)
#if defined(UINT64_MAX)
#define kr_cto64(x) ((x) != UINT64_C(0xFFFFFFFFFFFFFFFF) ? __builtin_ctzll(~KR_CASTS(uint64_t, (x))) : 64)
#endif // defined(UINT64_MAX)
#elif (KR_MSC_HAS_INTRIN_)
#define kr_cto32(x) (kr_ctz32_detail_(~KR_CASTS(uint32_t, x)))
#if defined(UINT64_MAX)
#define kr_cto64(x) (kr_ctz64_detail_(~KR_CASTS(uint64_t, x)))
#endif // defined(UINT64_MAX)
#else  // (KR_GNUC || KR_CLANG)
#define kr_cto32(x) (kr_countr_one32(x))
#if defined(UINT64_MAX)
#define kr_cto64(x) (kr_countr_one64(x))
#endif // defined(UINT64_MAX)
#endif // (KR_GNUC || KR_CLANG)

//------------------------------------------------------------------------------

/**
 * @brief Count number of set bits in an integer.
 *
 * @link https://graphics.stanford.edu/%7Eseander/bithacks.html#CountBitsSetParallel
 */
KR_CONSTEXPR int kr_popcount16(uint16_t x) KR_NOEXCEPT
{
    x = x - ((x >> 1) & UINT16_C(0x5555));
    x = (x & UINT16_C(0x3333)) + ((x >> 2) & UINT16_C(0x3333));
    x = (x + (x >> 4)) & UINT16_C(0x0f0f);
    return KR_CASTS(uint16_t, x * UINT16_C(0x0101)) >> 8;
}

/**
 * @brief Count number of set bits in an integer.
 *
 * @link https://graphics.stanford.edu/%7Eseander/bithacks.html#CountBitsSetParallel
 */
KR_CONSTEXPR int kr_popcount32(uint32_t x) KR_NOEXCEPT
{
    x = x - ((x >> 1) & UINT32_C(0x55555555));
    x = (x & UINT32_C(0x33333333)) + ((x >> 2) & UINT32_C(0x33333333));
    x = (x + (x >> 4)) & UINT32_C(0x0f0f0f0f);
    return KR_CASTS(uint32_t, x * UINT32_C(0x01010101)) >> 24;
}

#if defined(UINT64_MAX)

/**
 * @brief Count number of set bits in an integer.
 *
 * @link https://graphics.stanford.edu/%7Eseander/bithacks.html#CountBitsSetParallel
 */
KR_CONSTEXPR int kr_popcount64(uint64_t x) KR_NOEXCEPT
{
    x = x - ((x >> 1) & UINT64_C(0x5555555555555555));
    x = (x & UINT64_C(0x3333333333333333)) + ((x >> 2) & UINT64_C(0x3333333333333333));
    x = (x + (x >> 4)) & UINT64_C(0x0f0f0f0f0f0f0f0f);
    return KR_CASTS(uint64_t, x * UINT64_C(0x0101010101010101)) >> 56;
}

#endif // defined(UINT64_MAX)

#if (KR_MSC_HAS_INTRIN_)
#define kr_popcnt16(x) (KR_CASTS(int, __popcnt16(x)))
#define kr_popcnt32(x) (KR_CASTS(int, __popcnt(x)))
#if defined(UINT64_MAX)
#define kr_popcnt64(x) (KR_CASTS(int, __popcnt64(x)))
#endif // defined(UINT64_MAX)
#elif (KR_GNUC)
#define kr_popcnt16(x) (__builtin_popcount(x))
#define kr_popcnt32(x) (__builtin_popcount(x))
#if defined(UINT64_MAX)
#define kr_popcnt64(x) (__builtin_popcountll(x))
#endif // defined(UINT64_MAX)
#else  // (KR_MSC_HAS_INTRIN_)
#define kr_popcnt16(x) (kr_popcount16(x))
#define kr_popcnt32(x) (kr_popcount32(x))
#if defined(UINT64_MAX)
#define kr_popcnt64(x) (kr_popcount64(x))
#endif // defined(UINT64_MAX)
#endif // (KR_MSC_HAS_INTRIN_)

#undef KR_MSC_HAS_INTRIN_

#endif // !defined(KRBIT_H)
