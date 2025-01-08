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

/**
 * @brief Get length of string.
 *
 * @param str String to calculate length of.
 * @return Number of characters in string, not including the null terminator.
 */
KR_CONSTEXPR size_t kr_strlen(const char *str);

/**
 * @brief Get length of string up to a certain length.
 *
 * @param str String to calculate length of.
 * @param len Number of bytes to check.
 * @return Number of characters in string, or len if null terminator was
 *         not found.
 */
KR_CONSTEXPR size_t kr_strnlen(const char *str, size_t len);

/**
 * @brief Compare strings lexographically.
 *
 * @param lhs First string to compare.
 * @param rhs Second string to compare.
 * @return 0 if identical, <0 if lhs comes before rhs, >0 if rhs comes before
 *         lhs.
 */
KR_INLINE int kr_strcmp(const char *lhs, const char *rhs);

/**
 * @brief Copy string from src to dest.
 *
 * @details This function should be preferred over strlcpy if you are copying
 *          a string to a fixed-size location that you cannot grow to make
 *          bigger.
 *
 * @param dest Destination buffer to copy to.
 * @param src Source string to copy.
 * @param destLen Destination buffer size.
 * @return Length of resulting string, or <0 if truncation occurred.
 */
KR_CONSTEXPR ptrdiff_t kr_strscpy(char *KR_RESTRICT dest, const char *KR_RESTRICT src, size_t destLen);

/**
 * @brief Concatenate string on destination buffer containing existing string.
 *
 * @param dest Destination buffer to copy to.  Must contain existing string.
 * @param src Source string to copy.
 * @param destLen Destination buffer size.
 * @return Length of resulting string, or <0 if truncation occurred.
 */
KR_CONSTEXPR ptrdiff_t kr_strscat(char *KR_RESTRICT dest, const char *KR_RESTRICT src, size_t destLen);

/**
 * @brief Copy string from src to dest.
 *
 * @details This function should be preferred if you intend to reallocate
 *          the destination buffer to a proper size.
 *
 * @param dest Destination buffer to copy to.
 * @param src Source string to copy.
 * @param destLen Destination buffer size.
 * @return Length of desired string, >= destLen if truncation occurred.
 */
KR_CONSTEXPR size_t kr_strlcpy(char *KR_RESTRICT dest, const char *KR_RESTRICT src, size_t destLen);

/**
 * @brief Concatenate string on destination buffer containing existing string.
 *
 * @param dest Destination buffer to copy to.  Must contain existing string.
 * @param src Source string to copy.
 * @param destLen Destination buffer size.
 * @return Length of desired string, >= destLen if truncation occurred.
 */
KR_CONSTEXPR size_t kr_strlcat(char *KR_RESTRICT dest, const char *KR_RESTRICT src, size_t destLen);

/**
 * @brief Chain-copy string to destination buffer.
 *
 * @details Prefer this function to strcpy/strcat, as it does not require
 *          locating the existing end of string repeatedly.
 *
 * @param dest Destination buffer to copy to.  Passing NULL is a no-op.
 * @param destEnd Pointer to end of destination buffer.
 * @param src Source string to copy.
 * @return New end of destination buffer, or NULL if truncation occurred.
 *         Can be passed to subsequent invocations of kr_stpecpy without
 *         checking the result.
 */
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

/**
 * @brief Duplicate string with malloc().
 *
 * @param str String to duplicate.
 * @return Allocated string that can be freed with free().
 */
KR_NODISCARD char *kr_strdup(const char *str);

/**
 * @brief Duplicate string with malloc() up to len characters.
 *
 * @param str String to duplicate.
 * @param len Maximum number of characters to copy.
 * @return Allocated string that can be freed with free().
 */
KR_NODISCARD char *kr_strndup(const char *str, size_t len);

/**
 * @brief Copy a buffer of bytes up to - and including - a given byte, or
 *        copies the
 *
 * @param dest Destination buffer.
 * @param src Source buffer.
 * @param ch Byte to stop at.  Converted to unsigned char.
 * @param destLen Length of destination buffer.
 * @return If ch was found, return next byte after ch in destination buffer.
 *         Otherwise, NULL.
 */
KR_INLINE void *kr_memccpy(void *KR_RESTRICT dest, const void *KR_RESTRICT src, int ch, size_t destLen);

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

/******************************************************************************/

KR_INLINE void *kr_memccpy(void *KR_RESTRICT dest, const void *KR_RESTRICT src, int ch, size_t destLen)
{
    unsigned char *destCh = KR_CASTS(unsigned char *, dest);
    const unsigned char *curCh = KR_CASTS(const unsigned char *, src);
    const unsigned char *endCh = curCh + destLen;

    for (; curCh != endCh; destCh++, curCh++)
    {
        *destCh = *curCh;
        if (*curCh == KR_CASTS(unsigned char, ch))
        {
            return KR_CASTS(void *, destCh + 1);
        }
    }

    return NULL;
}

#endif /* !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION) */

#endif /* !defined(KRSTR_H) */
