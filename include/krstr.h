/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(KRSTR_H)
#define KRSTR_H

#include "./krconfig.h"

#if (!KR_CONFIG_NOINCLUDE)
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

KR_CONSTEXPR size_t kr_strlen(const char *str);
KR_CONSTEXPR size_t kr_strnlen(const char *str, size_t len);
KR_INLINE int kr_strcmp(const char *lhs, const char *rhs);
KR_CONSTEXPR ptrdiff_t kr_strscpy(char *KR_RESTRICT dest, const char *KR_RESTRICT src, size_t destLen);
KR_CONSTEXPR ptrdiff_t kr_strscat(char *KR_RESTRICT dest, const char *KR_RESTRICT src, size_t destLen);
KR_CONSTEXPR size_t kr_strlcpy(char *KR_RESTRICT dest, const char *KR_RESTRICT src, size_t destLen);
KR_CONSTEXPR size_t kr_strlcat(char *KR_RESTRICT dest, const char *KR_RESTRICT src, size_t destLen);
KR_CONSTEXPR char *kr_stpecpy(char *dest, char *destEnd, const char *KR_RESTRICT src);

/**
 * @brief Return the length (span) of the passed string `str` that consists
 *        only of the characters in the string `chars.`
 *
 * @param str String to check.
 * @param chars Characters to check for.
 * @return Length of substring that consists only of `chars` characters,
 *         strlen(`str`) if the entire string matches, or 0 if none of the
 *         string matches.
 */
KR_CONSTEXPR size_t kr_strspn(const char *str, const char *chars);

/**
 * @brief Return the length (span) of the passed string `str` that consists
 *        only of the characters not in the string `chars`.
 *
 * @param str String to check.
 * @param chars Characters to check for.
 * @return Length of substring that does not consist of `chars` characters,
 *         strlen(`str`) if the entire string lacks them.
 */
KR_CONSTEXPR size_t kr_strcspn(const char *str, const char *chars);

/**
 * @brief Scan string for a token that is split by one of the characters
 *        in string `delim`.
 *
 * @param str String to start the scan inside.  Must be NULL on all calls
 *            after the first if multiple tokens are desired.
 * @param delim A list of characters that split tokens.
 * @param ptr Pointer to context pointer.  If multiple tokens are desired,
 *            this parameter must not change across multiple calls.
 * @return A token found inside the scanned string, or NULL if no more tokens
 *         were found.
 */
KR_CONSTEXPR char *kr_strtok_r(char *KR_RESTRICT str, const char *KR_RESTRICT delim, char **KR_RESTRICT ptr);

KR_NODISCARD char *kr_strdup(const char *str);
KR_NODISCARD char *kr_strndup(const char *str, size_t len);

/******************************************************************************/
#if !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION)
/******************************************************************************/

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

/******************************************************************************/

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

/******************************************************************************/

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

/******************************************************************************/

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

/******************************************************************************/

KR_CONSTEXPR char *kr_stpecpy(char *dest, char *destEnd, const char *KR_RESTRICT src)
{
    ptrdiff_t len = 0;

    if (dest == NULL)
    {
        return NULL;
    }

    len = kr_strscpy(dest, src, KR_CASTS(size_t, destEnd - dest));
    if (len == -1)
    {
        return NULL;
    }

    return dest + len;
}

/******************************************************************************/

KR_CONSTEXPR size_t kr_strspn(const char *str, const char *chars)
{
    const char *s = str;
    const char *ch = NULL;

    for (; *s != '\0'; s++)
    {
        bool found = false;
        for (ch = chars; *ch != '\0'; ch++)
        {
            if (*s == *ch)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return KR_CASTS(size_t, s - str);
        }
    }

    return KR_CASTS(size_t, s - str);
}

KR_CONSTEXPR size_t kr_strcspn(const char *str, const char *chars)
{
    const char *s = str;
    const char *ch = NULL;

    for (; *s != '\0'; s++)
    {
        bool found = false;
        for (ch = chars; *ch != '\0'; ch++)
        {
            if (*s == *ch)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            return KR_CASTS(size_t, s - str);
        }
    }

    return KR_CASTS(size_t, s - str);
}

/******************************************************************************/

KR_CONSTEXPR char *kr_strtok_r(char *KR_RESTRICT str, const char *KR_RESTRICT delim, char **KR_RESTRICT ptr)
{
    char *tok = NULL;

    if (str == NULL)
    {
        if (*ptr == NULL)
        {
            return NULL;
        }

        // Resuming a previous tokenization.
        str = *ptr;
    }

    // First, munch all delim chars.
    str += kr_strspn(str, delim);
    if (*str == '\0')
    {
        // Could not find another token.
        return NULL;
    }

    // Munch a token.
    tok = str;
    str += kr_strcspn(str, delim);
    if (*str == '\0')
    {
        // Found the last token.
        *ptr = NULL;
        return tok;
    }

    // Null the end and set our next starting point.
    *str = '\0';
    *ptr = str + 1;
    return tok;
}

/******************************************************************************/

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

#endif /* !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION) */

#endif /* !defined(KRSTR_H) */
