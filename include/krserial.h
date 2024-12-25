//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

//
// Serialization helpers
//

#if !defined(KRSERIAL_H)
#define KRSERIAL_H

#include "./krconfig.h"

#include "./krbit.h" // Needed for bswap.

#if (!KR_CONFIG_NOINCLUDE)
#include <string.h>
#endif // (!KR_CONFIG_NOINCLUDE)

//------------------------------------------------------------------------------

KR_INLINE uint16_t kr_load_u16le(void *in)
{
    uint16_t rvo;
    memcpy(&rvo, in, sizeof(rvo));
#if (KR_BYTE_ORDER == KR_ORDER_BIG_ENDIAN)
    rvo = kr_bswap16(rvo);
#endif
    return rvo;
}

KR_INLINE uint16_t kr_load_u16be(void *in)
{
    uint16_t rvo;
    memcpy(&rvo, in, sizeof(rvo));
#if (KR_BYTE_ORDER == KR_ORDER_LITTLE_ENDIAN)
    rvo = kr_bswap16(rvo);
#endif
    return rvo;
}

//------------------------------------------------------------------------------

KR_INLINE uint32_t kr_load_u32le(void *in)
{
    uint32_t rvo;
    memcpy(&rvo, in, sizeof(rvo));
#if (KR_BYTE_ORDER == KR_ORDER_BIG_ENDIAN)
    rvo = kr_bswap32(rvo);
#endif
    return rvo;
}

KR_INLINE uint32_t kr_load_u32be(void *in)
{
    uint32_t rvo;
    memcpy(&rvo, in, sizeof(rvo));
#if (KR_BYTE_ORDER == KR_ORDER_LITTLE_ENDIAN)
    rvo = kr_bswap32(rvo);
#endif
    return rvo;
}

//------------------------------------------------------------------------------

#if defined(UINT64_MAX)

KR_INLINE uint64_t kr_load_u64le(void *in)
{
    uint64_t rvo;
    memcpy(&rvo, in, sizeof(rvo));
#if (KR_BYTE_ORDER == KR_ORDER_BIG_ENDIAN)
    rvo = kr_bswap64(rvo);
#endif
    return rvo;
}

KR_INLINE uint64_t kr_load_u64be(void *in)
{
    uint64_t rvo;
    memcpy(&rvo, in, sizeof(rvo));
#if (KR_BYTE_ORDER == KR_ORDER_LITTLE_ENDIAN)
    rvo = kr_bswap64(rvo);
#endif
    return rvo;
}

#endif // defined(UINT64_MAX)

//------------------------------------------------------------------------------

KR_INLINE void kr_store_u16le(void *out, uint16_t in)
{
#if (KR_BYTE_ORDER == KR_ORDER_BIG_ENDIAN)
    in = kr_bswap16(in);
#endif
    memcpy(out, &in, sizeof(in));
}

KR_INLINE void kr_store_u16be(void *out, uint16_t in)
{
#if (KR_BYTE_ORDER == KR_ORDER_LITTLE_ENDIAN)
    in = kr_bswap16(in);
#endif
    memcpy(out, &in, sizeof(in));
}

//------------------------------------------------------------------------------

KR_INLINE void kr_store_u32le(void *out, uint32_t in)
{
#if (KR_BYTE_ORDER == KR_ORDER_BIG_ENDIAN)
    in = kr_bswap32(in);
#endif
    memcpy(out, &in, sizeof(in));
}

KR_INLINE void kr_store_u32be(void *out, uint32_t in)
{
#if (KR_BYTE_ORDER == KR_ORDER_LITTLE_ENDIAN)
    in = kr_bswap32(in);
#endif
    memcpy(out, &in, sizeof(in));
}

//------------------------------------------------------------------------------

#if defined(UINT64_MAX)

KR_INLINE void kr_store_u64le(void *out, uint64_t in)
{
#if (KR_BYTE_ORDER == KR_ORDER_BIG_ENDIAN)
    in = kr_bswap64(in);
#endif
    memcpy(out, &in, sizeof(in));
}

KR_INLINE void kr_store_u64be(void *out, uint64_t in)
{
#if (KR_BYTE_ORDER == KR_ORDER_LITTLE_ENDIAN)
    in = kr_bswap64(in);
#endif
    memcpy(out, &in, sizeof(in));
}

#endif // defined(UINT64_MAX)

#endif // !defined(KRSERIAL_H)
