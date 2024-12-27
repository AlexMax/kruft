/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

/*
 * Bit-manipulation functions, C++20's <bit> for all.
 *
 * This header is allowed to break the "no cleverness" rule, since these
 * functions generally need to be as fast as possible.  That said, the
 * individual functions should still allow for easy copy-pasting.
 */

#if !defined(KRBIT_H)
#define KRBIT_H

#include "./krconfig.h"

#include "./krbool.h"
#include "./krint.h"

/**
 * @brief Byteswap a 16-bit value.
 */
KR_CONSTEXPR uint16_t kr_byteswap16(uint16_t x);

/**
 * @brief Byteswap a 32-bit value.
 */
KR_CONSTEXPR uint32_t kr_byteswap32(uint32_t x);

/**
 * @brief Byteswap a 64-bit value.
 */
KR_CONSTEXPR uint64_t kr_byteswap64(uint64_t x);

KR_CONSTEXPR bool kr_has_single_bit8(uint8_t x) KR_NOEXCEPT;
KR_CONSTEXPR bool kr_has_single_bit16(uint16_t x) KR_NOEXCEPT;
KR_CONSTEXPR bool kr_has_single_bit32(uint32_t x) KR_NOEXCEPT;
KR_CONSTEXPR bool kr_has_single_bit64(uint64_t x) KR_NOEXCEPT;

/**
 * @brief Round up to the nearest power of two.
 *
 * @link http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2Float
 */
KR_CONSTEXPR uint32_t kr_bit_ceil32(uint32_t x) KR_NOEXCEPT;

/**
 * @brief Round up to the nearest power of two.
 *
 * @link http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2Float
 */
KR_CONSTEXPR uint64_t kr_bit_ceil64(uint64_t x) KR_NOEXCEPT;

/**
 * @brief Round down to the nearest power of two.
 *
 * @link https://www.amazon.com/Hackers-Delight-2nd-Henry-Warren-dp-0321842685/dp/0321842685
 */
KR_CONSTEXPR uint32_t kr_bit_floor32(uint32_t x) KR_NOEXCEPT;

/**
 * @brief Round down to the nearest power of two.
 *
 * @link https://www.amazon.com/Hackers-Delight-2nd-Henry-Warren-dp-0321842685/dp/0321842685
 */
KR_CONSTEXPR uint64_t kr_bit_floor64(uint64_t x) KR_NOEXCEPT;

/**
 * @brief Count minimum number of bits needed to represent value.
 */
KR_CONSTEXPR int kr_bit_width32(uint32_t x) KR_NOEXCEPT;

/**
 * @brief Count minimum number of bits needed to represent value.
 */
KR_CONSTEXPR int kr_bit_width64(uint64_t x) KR_NOEXCEPT;

KR_CONSTEXPR uint8_t kr_rotl8(uint8_t x, int c) KR_NOEXCEPT;
KR_CONSTEXPR uint16_t kr_rotl16(uint16_t x, int c) KR_NOEXCEPT;
KR_CONSTEXPR uint32_t kr_rotl32(uint32_t x, int c) KR_NOEXCEPT;
KR_CONSTEXPR uint64_t kr_rotl64(uint64_t x, int c) KR_NOEXCEPT;

KR_CONSTEXPR uint8_t kr_rotr8(uint8_t x, int c) KR_NOEXCEPT;
KR_CONSTEXPR uint16_t kr_rotr16(uint16_t x, int c) KR_NOEXCEPT;
KR_CONSTEXPR uint32_t kr_rotr32(uint32_t x, int c) KR_NOEXCEPT;
KR_CONSTEXPR uint64_t kr_rotr64(uint64_t x, int c) KR_NOEXCEPT;

/**
 * @brief Count leading (starting at MSB) zero bits.
 *
 * @link http://aggregate.ee.engr.uky.edu/MAGIC/#Leading%20Zero%20Count
 */
KR_CONSTEXPR int kr_countl_zero32(uint32_t x) KR_NOEXCEPT;

/**
 * @brief Count leading (starting at MSB) zero bits.
 *
 * @link http://aggregate.ee.engr.uky.edu/MAGIC/#Leading%20Zero%20Count
 */
KR_CONSTEXPR int kr_countl_zero64(uint64_t x) KR_NOEXCEPT;

/**
 * @brief Count leading (starting at MSB) one bits.
 */
KR_CONSTEXPR int kr_countl_one32(uint32_t x) KR_NOEXCEPT;

/**
 * @brief Count leading (starting at MSB) one bits.
 */
KR_CONSTEXPR int kr_countl_one64(uint64_t x) KR_NOEXCEPT;

/**
 * @brief Count trailing (starting at LSB) zero bits.
 */
KR_CONSTEXPR int kr_countr_zero32(uint32_t x) KR_NOEXCEPT;

/**
 * @brief Count trailing (starting at LSB) zero bits.
 */
KR_CONSTEXPR int kr_countr_zero64(uint64_t x) KR_NOEXCEPT;

/**
 * @brief Count trailing (starting at LSB) one bits.
 */
KR_CONSTEXPR int kr_countr_one32(uint32_t x) KR_NOEXCEPT;

/**
 * @brief Count trailing (starting at LSB) one bits.
 */
KR_CONSTEXPR int kr_countr_one64(uint64_t x) KR_NOEXCEPT;

/**
 * @brief Count number of set bits in an integer.
 *
 * @link https://graphics.stanford.edu/%7Eseander/bithacks.html#CountBitsSetParallel
 */
KR_CONSTEXPR int kr_popcount16(uint16_t x) KR_NOEXCEPT;

/**
 * @brief Count number of set bits in an integer.
 *
 * @link https://graphics.stanford.edu/%7Eseander/bithacks.html#CountBitsSetParallel
 */
KR_CONSTEXPR int kr_popcount32(uint32_t x) KR_NOEXCEPT;

/**
 * @brief Count number of set bits in an integer.
 *
 * @link https://graphics.stanford.edu/%7Eseander/bithacks.html#CountBitsSetParallel
 */
KR_CONSTEXPR int kr_popcount64(uint64_t x) KR_NOEXCEPT;

/******************************************************************************/
#if !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION)
/******************************************************************************/

KR_CONSTEXPR uint16_t kr_byteswap16(uint16_t x)
{
    return KR_CASTS(uint16_t, (x & 0xFF00) >> 8) | /**/
           KR_CASTS(uint16_t, (x & 0x00FF) << 8);  /**/
}

KR_CONSTEXPR uint32_t kr_byteswap32(uint32_t x)
{
    return ((x & 0xFF000000) >> 24) | /**/
           ((x & 0x00FF0000) >> 8) |  /**/
           ((x & 0x0000FF00) << 8) |  /**/
           ((x & 0x000000FF) << 24);  /**/
}

#if defined(UINT64_MAX)

KR_CONSTEXPR uint64_t kr_byteswap64(uint64_t x)
{
    return ((x & UINT64_C(0xFF00000000000000)) >> UINT64_C(56)) | /**/
           ((x & UINT64_C(0x00FF000000000000)) >> UINT64_C(40)) | /**/
           ((x & UINT64_C(0x0000FF0000000000)) >> UINT64_C(24)) | /**/
           ((x & UINT64_C(0x000000FF00000000)) >> UINT64_C(8)) |  /**/
           ((x & UINT64_C(0x00000000FF000000)) << UINT64_C(8)) |  /**/
           ((x & UINT64_C(0x0000000000FF0000)) << UINT64_C(24)) | /**/
           ((x & UINT64_C(0x000000000000FF00)) << UINT64_C(40)) | /**/
           ((x & UINT64_C(0x00000000000000FF)) << UINT64_C(56));  /**/
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

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

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

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

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

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

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR int kr_bit_width32(uint32_t x) KR_NOEXCEPT
{
    return 32 - kr_countl_zero32(x);
}

#if defined(UINT64_MAX)

KR_CONSTEXPR int kr_bit_width64(uint64_t x) KR_NOEXCEPT
{
    return 64 - kr_countl_zero64(x);
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

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

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

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

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

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

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

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

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

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

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

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

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR int kr_popcount16(uint16_t x) KR_NOEXCEPT
{
    x = x - ((x >> 1) & UINT16_C(0x5555));
    x = (x & UINT16_C(0x3333)) + ((x >> 2) & UINT16_C(0x3333));
    x = (x + (x >> 4)) & UINT16_C(0x0f0f);
    return KR_CASTS(uint16_t, x * UINT16_C(0x0101)) >> 8;
}

KR_CONSTEXPR int kr_popcount32(uint32_t x) KR_NOEXCEPT
{
    x = x - ((x >> 1) & UINT32_C(0x55555555));
    x = (x & UINT32_C(0x33333333)) + ((x >> 2) & UINT32_C(0x33333333));
    x = (x + (x >> 4)) & UINT32_C(0x0f0f0f0f);
    return KR_CASTS(uint32_t, x * UINT32_C(0x01010101)) >> 24;
}

#if defined(UINT64_MAX)

KR_CONSTEXPR int kr_popcount64(uint64_t x) KR_NOEXCEPT
{
    x = x - ((x >> 1) & UINT64_C(0x5555555555555555));
    x = (x & UINT64_C(0x3333333333333333)) + ((x >> 2) & UINT64_C(0x3333333333333333));
    x = (x + (x >> 4)) & UINT64_C(0x0f0f0f0f0f0f0f0f);
    return KR_CASTS(uint64_t, x * UINT64_C(0x0101010101010101)) >> 56;
}

#endif /* defined(UINT64_MAX) */

#endif /* !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION) */

#endif /* !defined(KRBIT_H) */
