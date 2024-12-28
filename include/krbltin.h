/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

/*
 * Compiler builtin shims.
 *
 * These macros expand to a compiler built-in if available, or a fallback
 * implementation if not.
 */

#if !defined(KRBLTIN_H)
#define KRBLTIN_H

#include "krbit.h"

#if (KR_MSC_VER >= 1300) /* FIXME: Not in VC6, unsure when introduced. */
#include <intrin.h>
#define KR_MSC_HAS_INTRIN_ (1)
#else /* (KR_MSC_VER >= 1300) */
#define KR_MSC_HAS_INTRIN_ (0)
#endif /* (KR_MSC_VER >= 1300) */

/******************************************************************************/

#if (KR_CLANG)
#define kr_rbit8(x) (__builtin_bitreverse8(x))
#define kr_rbit16(x) (__builtin_bitreverse16(x))
#define kr_rbit32(x) (__builtin_bitreverse32(x))
#if defined(UINT64_MAX)
#define kr_rbit64(x) (__builtin_bitreverse64(x))
#endif /* defined(UINT64_MAX) */
#else
#define kr_rbit8(x) (kr_bitreverse8(x))
#define kr_rbit16(x) (kr_bitreverse16(x))
#define kr_rbit32(x) (kr_bitreverse32(x))
#if defined(UINT64_MAX)
#define kr_rbit64(x) (kr_bitreverse64(x))
#endif /* defined(UINT64_MAX) */
#endif /* (KR_CLANG) */

/******************************************************************************/

#if (KR_GNUC || KR_CLANG)
#define kr_bswap16(x) (__builtin_bswap16(x))
#define kr_bswap32(x) (__builtin_bswap32(x))
#if defined(UINT64_MAX)
#define kr_bswap64(x) (__builtin_bswap64(x))
#endif /* defined(UINT64_MAX) */
#elif (KR_MSC_HAS_INTRIN_)
#define kr_bswap16(x) (_byteswap_ushort(x))
#define kr_bswap32(x) (_byteswap_ulong(x))
#if defined(UINT64_MAX)
#define kr_bswap64(x) (_byteswap_uint64(x))
#endif /* defined(UINT64_MAX) */
#else
#define kr_bswap16(x) (kr_byteswap16(x))
#define kr_bswap32(x) (kr_byteswap32(x))
#if defined(UINT64_MAX)
#define kr_bswap64(x) (kr_byteswap64(x))
#endif /* defined(UINT64_MAX) */
#endif

/******************************************************************************/

#if (KR_CLANG)
#define kr_rol8(x, c) (__builtin_rotateleft8((x), (c)))
#define kr_rol16(x, c) (__builtin_rotateleft16((x), (c)))
#define kr_rol32(x, c) (__builtin_rotateleft32((x), (c)))
#if defined(UINT64_MAX)
#define kr_rol64(x, c) (__builtin_rotateleft64((x), (c)))
#endif /* defined(UINT64_MAX) */
#elif (KR_MSC_HAS_INTRIN_)
#define kr_rol8(x, c) (_rotl8((x), (c)))
#define kr_rol16(x, c) (_rotl16((x), (c)))
#define kr_rol32(x, c) (_rotl((x), (c)))
#if defined(UINT64_MAX)
#define kr_rol64(x, c) (_rotl64((x), (c)))
#endif /* defined(UINT64_MAX) */
#else
#define kr_rol8(x, c) (kr_rotl8((x), (c)))
#define kr_rol16(x, c) (kr_rotl16((x), (c)))
#define kr_rol32(x, c) (kr_rotl32((x), (c)))
#if defined(UINT64_MAX)
#define kr_rol64(x, c) (kr_rotl64((x), (c)))
#endif /* #if defined(UINT64_MAX) */
#endif

/******************************************************************************/

#if (KR_CLANG)
#define kr_ror8(x, c) (__builtin_rotateright8((x), (c)))
#define kr_ror16(x, c) (__builtin_rotateright16((x), (c)))
#define kr_ror32(x, c) (__builtin_rotateright32((x), (c)))
#if defined(UINT64_MAX)
#define kr_ror64(x, c) (__builtin_rotateright64((x), (c)))
#endif /* defined(UINT64_MAX) */
#elif (KR_MSC_HAS_INTRIN_)
#define kr_ror8(x, c) (_rotr8((x), (c)))
#define kr_ror16(x, c) (_rotr16((x), (c)))
#define kr_ror32(x, c) (_rotr((x), (c)))
#if defined(UINT64_MAX)
#define kr_ror64(x, c) (_rotr64((x), (c)))
#endif /* defined(UINT64_MAX) */
#else
#define kr_ror8(x, c) (kr_rotr8((x), (c)))
#define kr_ror16(x, c) (kr_rotr16((x), (c)))
#define kr_ror32(x, c) (kr_rotr32((x), (c)))
#if defined(UINT64_MAX)
#define kr_ror64(x, c) (kr_rotr64((x), (c)))
#endif /* defined(UINT64_MAX) */
#endif

/******************************************************************************/

#if (KR_GNUC || KR_CLANG) /* Prefer __builtin_clz on clang-cl */
#define kr_clz32(x) ((x) != 0 ? __builtin_clz(x) : 32)
#if defined(UINT64_MAX)
#define kr_clz64(x) ((x) != 0 ? __builtin_clzll(x) : 64)
#endif /* defined(UINT64_MAX) */
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
#endif /* defined(UINT64_MAX) */
#else
#define kr_clz32(x) (kr_countl_zero32(x))
#if defined(UINT64_MAX)
#define kr_clz64(x) (kr_countl_zero64(x))
#endif /* defined(UINT64_MAX) */
#endif

/******************************************************************************/

#if (KR_GNUC || KR_CLANG) /* Prefer __builtin_clz on clang-cl */
#define kr_clo32(x) ((x) != 0xFFFFFFFF ? __builtin_clz(~KR_CASTS(uint32_t, (x))) : 32)
#if defined(UINT64_MAX)
#define kr_clo64(x) ((x) != 0xFFFFFFFFFFFFFFFF ? __builtin_clzll(~KR_CASTS(uint64_t, (x))) : 64)
#endif /* defined(UINT64_MAX) */
#elif (KR_MSC_HAS_INTRIN_)
#define kr_clo32(x) (kr_clz32_detail_(~KR_CASTS(uint32_t, x)))
#if defined(UINT64_MAX)
#define kr_clo64(x) (kr_clz64_detail_(~KR_CASTS(uint64_t, x)))
#endif /* defined(UINT64_MAX) */
#else
#define kr_clo32(x) (kr_countl_one32(x))
#if defined(UINT64_MAX)
#define kr_clo64(x) (kr_countl_one64(x))
#endif /* defined(UINT64_MAX) */
#endif

/******************************************************************************/

#if (KR_GNUC || KR_CLANG) /* Prefer __builtin_ctz on clang-cl */
#define kr_ctz32(x) ((x) != 0 ? __builtin_ctz(x) : 32)
#if defined(UINT64_MAX)
#define kr_ctz64(x) ((x) != 0 ? __builtin_ctzll(x) : 64)
#endif /* defined(UINT64_MAX) */
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
#endif /* defined(UINT64_MAX) */
#else
#define kr_ctz32(x) (kr_countr_zero32(x))
#if defined(UINT64_MAX)
#define kr_ctz64(x) (kr_countr_zero64(x))
#endif /* defined(UINT64_MAX) */
#endif

/******************************************************************************/

#if (KR_GNUC || KR_CLANG) /* Prefer __builtin_ctz on clang-cl */
#define kr_cto32(x) ((x) != UINT32_C(0xFFFFFFFF) ? __builtin_ctz(~KR_CASTS(uint32_t, (x))) : 32)
#if defined(UINT64_MAX)
#define kr_cto64(x) ((x) != UINT64_C(0xFFFFFFFFFFFFFFFF) ? __builtin_ctzll(~KR_CASTS(uint64_t, (x))) : 64)
#endif /* defined(UINT64_MAX) */
#elif (KR_MSC_HAS_INTRIN_)
#define kr_cto32(x) (kr_ctz32_detail_(~KR_CASTS(uint32_t, x)))
#if defined(UINT64_MAX)
#define kr_cto64(x) (kr_ctz64_detail_(~KR_CASTS(uint64_t, x)))
#endif /* defined(UINT64_MAX) */
#else
#define kr_cto32(x) (kr_countr_one32(x))
#if defined(UINT64_MAX)
#define kr_cto64(x) (kr_countr_one64(x))
#endif /* defined(UINT64_MAX) */
#endif

/******************************************************************************/

#if (KR_GNUC || KR_CLANG)
#define kr_popcnt16(x) (__builtin_popcount(x))
#define kr_popcnt32(x) (__builtin_popcount(x))
#if defined(UINT64_MAX)
#define kr_popcnt64(x) (__builtin_popcountll(x))
#endif /* defined(UINT64_MAX) */
#elif (KR_MSC_HAS_INTRIN_)
#define kr_popcnt16(x) (KR_CASTS(int, __popcnt16(x)))
#define kr_popcnt32(x) (KR_CASTS(int, __popcnt(x)))
#if defined(UINT64_MAX)
#define kr_popcnt64(x) (KR_CASTS(int, __popcnt64(x)))
#endif /* defined(UINT64_MAX) */
#else
#define kr_popcnt16(x) (kr_popcount16(x))
#define kr_popcnt32(x) (kr_popcount32(x))
#if defined(UINT64_MAX)
#define kr_popcnt64(x) (kr_popcount64(x))
#endif /* defined(UINT64_MAX) */
#endif

#undef KR_MSC_HAS_INTRIN_

#endif /* !defined(KRBLTIN_H) */
