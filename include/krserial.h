/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

/*
 * Serialization helpers
 */

#if !defined(KRSERIAL_H)
#define KRSERIAL_H

#include "./krconfig.h"

#include "./krbit.h" /* Needed for bswap. */

#if (!KR_CONFIG_NOINCLUDE)
#include <string.h>
#endif /* (!KR_CONFIG_NOINCLUDE) */

KR_INLINE uint16_t kr_load_u16le(void *src);
KR_INLINE uint16_t kr_load_u16be(void *src);
KR_INLINE uint32_t kr_load_u32le(void *src);
KR_INLINE uint32_t kr_load_u32be(void *src);
#if defined(UINT64_MAX)
KR_INLINE uint64_t kr_load_u64le(void *src);
KR_INLINE uint64_t kr_load_u64be(void *src);
#endif /* defined(UINT64_MAX) */

KR_INLINE void kr_store_u16le(void *dest, uint16_t src);
KR_INLINE void kr_store_u16be(void *dest, uint16_t src);
KR_INLINE void kr_store_u32le(void *dest, uint32_t src);
KR_INLINE void kr_store_u32be(void *dest, uint32_t src);
#if defined(UINT64_MAX)
KR_INLINE void kr_store_u64le(void *dest, uint64_t src);
KR_INLINE void kr_store_u64be(void *dest, uint64_t src);
#endif /* defined(UINT64_MAX) */

/******************************************************************************/
#if !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION)
/******************************************************************************/

KR_INLINE uint16_t kr_load_u16le(void *src)
{
    uint16_t rvo;
    memcpy(&rvo, src, sizeof(rvo));
#if (KR_BYTE_ORDER == KR_ORDER_BIG_ENDIAN)
    rvo = kr_bswap16(rvo);
#endif
    return rvo;
}

KR_INLINE uint16_t kr_load_u16be(void *src)
{
    uint16_t rvo;
    memcpy(&rvo, src, sizeof(rvo));
#if (KR_BYTE_ORDER == KR_ORDER_LITTLE_ENDIAN)
    rvo = kr_bswap16(rvo);
#endif
    return rvo;
}

/******************************************************************************/

KR_INLINE uint32_t kr_load_u32le(void *src)
{
    uint32_t rvo;
    memcpy(&rvo, src, sizeof(rvo));
#if (KR_BYTE_ORDER == KR_ORDER_BIG_ENDIAN)
    rvo = kr_bswap32(rvo);
#endif
    return rvo;
}

KR_INLINE uint32_t kr_load_u32be(void *src)
{
    uint32_t rvo;
    memcpy(&rvo, src, sizeof(rvo));
#if (KR_BYTE_ORDER == KR_ORDER_LITTLE_ENDIAN)
    rvo = kr_bswap32(rvo);
#endif
    return rvo;
}

/******************************************************************************/

#if defined(UINT64_MAX)

KR_INLINE uint64_t kr_load_u64le(void *src)
{
    uint64_t rvo;
    memcpy(&rvo, src, sizeof(rvo));
#if (KR_BYTE_ORDER == KR_ORDER_BIG_ENDIAN)
    rvo = kr_bswap64(rvo);
#endif
    return rvo;
}

KR_INLINE uint64_t kr_load_u64be(void *src)
{
    uint64_t rvo;
    memcpy(&rvo, src, sizeof(rvo));
#if (KR_BYTE_ORDER == KR_ORDER_LITTLE_ENDIAN)
    rvo = kr_bswap64(rvo);
#endif
    return rvo;
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_INLINE void kr_store_u16le(void *dest, uint16_t src)
{
#if (KR_BYTE_ORDER == KR_ORDER_BIG_ENDIAN)
    src = kr_bswap16(src);
#endif
    memcpy(dest, &src, sizeof(src));
}

KR_INLINE void kr_store_u16be(void *dest, uint16_t src)
{
#if (KR_BYTE_ORDER == KR_ORDER_LITTLE_ENDIAN)
    src = kr_bswap16(src);
#endif
    memcpy(dest, &src, sizeof(src));
}

/******************************************************************************/

KR_INLINE void kr_store_u32le(void *dest, uint32_t src)
{
#if (KR_BYTE_ORDER == KR_ORDER_BIG_ENDIAN)
    src = kr_bswap32(src);
#endif
    memcpy(dest, &src, sizeof(src));
}

KR_INLINE void kr_store_u32be(void *dest, uint32_t src)
{
#if (KR_BYTE_ORDER == KR_ORDER_LITTLE_ENDIAN)
    src = kr_bswap32(src);
#endif
    memcpy(dest, &src, sizeof(src));
}

/******************************************************************************/

#if defined(UINT64_MAX)

KR_INLINE void kr_store_u64le(void *dest, uint64_t src)
{
#if (KR_BYTE_ORDER == KR_ORDER_BIG_ENDIAN)
    src = kr_bswap64(src);
#endif
    memcpy(dest, &src, sizeof(src));
}

KR_INLINE void kr_store_u64be(void *dest, uint64_t src)
{
#if (KR_BYTE_ORDER == KR_ORDER_LITTLE_ENDIAN)
    src = kr_bswap64(src);
#endif
    memcpy(dest, &src, sizeof(src));
}

#endif /* defined(UINT64_MAX) */

#endif /* !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION) */

#endif /* !defined(KRSERIAL_H) */
