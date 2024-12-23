//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include "./krconfig.h"

#if (!KR_CONFIG_NOINCLUDE)
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

KR_CONSTEXPR size_t kr_strlen(const char *str)
{
    size_t i = 0;

    for (i = 0;; i++)
    {
        if (str[i] == '\0')
        {
            return i;
        }
    }
}

KR_CONSTEXPR size_t kr_strnlen(const char *str, size_t len)
{
    size_t i = 0;

    for (i = 0; i < len; i++)
    {
        if (str[i] == '\0')
        {
            return i;
        }
    }
    return len;
}

KR_INLINE int kr_strcmp(const char *lhs, const char *rhs)
{
    for (;; lhs++, rhs++)
    {
        if (*lhs != *rhs || *lhs == '\0')
        {
            break;
        }
    }
    return *(KR_CASTR(const unsigned char *, lhs)) - *(KR_CASTR(const unsigned char *, rhs));
}

KR_CONSTEXPR ptrdiff_t kr_strscpy(char *KR_RESTRICT dest, const char *KR_RESTRICT src, size_t destLen)
{
    size_t i = 0;

    if (destLen == 0)
    {
        return 0;
    }

    i = 0;
    for (; i < destLen; i++)
    {
        dest[i] = src[i];
        if (src[i] == '\0')
        {
            return KR_CASTS(ptrdiff_t, i);
        }
    }

    dest[i - 1] = '\0';
    return -1;
}

KR_CONSTEXPR ptrdiff_t kr_strscat(char *KR_RESTRICT dest, const char *KR_RESTRICT src, size_t destLen)
{
    ptrdiff_t len = 0;

    size_t tail = kr_strnlen(dest, destLen);
    if (tail == destLen)
    {
        return -1;
    }

    len = kr_strscpy(dest + tail, src, destLen - tail);
    if (len < 0)
    {
        return -1;
    }

    return KR_CASTS(ptrdiff_t, tail) + len;
}

KR_CONSTEXPR size_t kr_strlcpy(char *KR_RESTRICT dest, const char *KR_RESTRICT src, size_t destLen)
{
    size_t i = 0;

    if (destLen == 0)
    {
        return 0;
    }

    i = 0;
    for (; i < destLen; i++)
    {
        dest[i] = src[i];
        if (src[i] == '\0')
        {
            return i;
        }
    }

    dest[i - 1] = '\0';
    for (;; i++)
    {
        if (src[i] == '\0')
        {
            return i;
        }
    }
}

KR_CONSTEXPR size_t kr_strlcat(char *KR_RESTRICT dest, const char *KR_RESTRICT src, size_t destLen)
{
    size_t tail = kr_strnlen(dest, destLen);
    if (tail == destLen)
    {
        return destLen;
    }

    return kr_strlcpy(dest + tail, src, destLen - tail) + tail;
}

KR_CONSTEXPR char *kr_stpecpy(char *dest, char *srcEnd, const char *KR_RESTRICT src)
{
    ptrdiff_t len = 0;

    if (dest == NULL)
    {
        return NULL;
    }

    len = kr_strscpy(dest, src, KR_CASTS(size_t, srcEnd - dest));
    if (len == -1)
    {
        return NULL;
    }

    return dest + len;
}

KR_NODISCARD char *kr_strdup(const char *str)
{
    size_t strl = kr_strlen(str);
    char *dup = KR_CASTS(char *, KR_MALLOC(strl + 1));
    if (dup == NULL)
    {
        return NULL;
    }

    memcpy(dup, str, strl + 1);
    return dup;
}

KR_NODISCARD char *kr_strndup(const char *str, size_t len)
{
    size_t strl = kr_strnlen(str, len);
    char *dup = KR_CASTS(char *, KR_MALLOC(strl + 1));
    if (dup == NULL)
    {
        return NULL;
    }

    memcpy(dup, str, strl);
    dup[strl] = '\0';
    return dup;
}
