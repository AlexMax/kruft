/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

/*
 * ctype.h functions
 *
 * - These functions accept char and return bool or char.
 * - These functions have no undefined behavior and do not assert.
 * - These functions only deal with ASCII and do not care about locales.
 */

#if !defined(KRCTYPE_H)
#define KRCTYPE_H

#include "./krconfig.h"

#include "./krbool.h"

KR_CONSTEXPR bool kr_isalnum(char ch);
KR_CONSTEXPR bool kr_isalpha(char ch);
KR_CONSTEXPR bool kr_islower(char ch);
KR_CONSTEXPR bool kr_isupper(char ch);
KR_CONSTEXPR bool kr_isdigit(char ch);
KR_CONSTEXPR bool kr_isxdigit(char ch);
KR_CONSTEXPR bool kr_iscntrl(char ch);
KR_CONSTEXPR bool kr_isgraph(char ch);
KR_CONSTEXPR bool kr_isspace(char ch);
KR_CONSTEXPR bool kr_isblank(char ch);
KR_CONSTEXPR bool kr_isprint(char ch);
KR_CONSTEXPR bool kr_ispunct(char ch);
KR_CONSTEXPR char kr_tolower(char ch);
KR_CONSTEXPR char kr_toupper(char ch);

/******************************************************************************/
#if !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION)
/******************************************************************************/

KR_CONSTEXPR bool kr_isalnum(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
        return true;
    }
    else if (ch >= 'a' && ch <= 'z')
    {
        return true;
    }
    return false;
}

KR_CONSTEXPR bool kr_isalpha(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        return true;
    }
    else if (ch >= 'a' && ch <= 'z')
    {
        return true;
    }
    return false;
}

KR_CONSTEXPR bool kr_islower(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return true;
    }
    return false;
}

KR_CONSTEXPR bool kr_isupper(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        return true;
    }
    return false;
}

KR_CONSTEXPR bool kr_isdigit(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    return false;
}

KR_CONSTEXPR bool kr_isxdigit(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    else if (ch >= 'A' && ch <= 'F')
    {
        return true;
    }
    else if (ch >= 'a' && ch <= 'f')
    {
        return true;
    }
    return false;
}

KR_CONSTEXPR bool kr_iscntrl(char ch)
{
    if (ch >= 0x00 && ch <= 0x1f)
    {
        return true;
    }
    else if (ch == 0x7f)
    {
        return true;
    }
    return false;
}

KR_CONSTEXPR bool kr_isgraph(char ch)
{
    if (ch > ' ' && ch <= '~')
    {
        return true;
    }
    return false;
}

KR_CONSTEXPR bool kr_isspace(char ch)
{
    if (ch == ' ' || ch == '\f' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v')
    {
        return true;
    }
    return false;
}

KR_CONSTEXPR bool kr_isblank(char ch)
{
    if (ch == ' ' || ch == '\t')
    {
        return true;
    }
    return false;
}

KR_CONSTEXPR bool kr_isprint(char ch)
{
    if (ch >= ' ' && ch <= '~')
    {
        return true;
    }
    return false;
}

KR_CONSTEXPR bool kr_ispunct(char ch)
{
    if (ch >= 0x21 && ch <= 0x2f)
    {
        return true;
    }
    else if (ch >= 0x3A && ch <= 0x40)
    {
        return true;
    }
    else if (ch >= 0x5b && ch <= 0x60)
    {
        return true;
    }
    else if (ch >= 0x7b && ch <= 0x7e)
    {
        return true;
    }
    return false;
}

KR_CONSTEXPR char kr_tolower(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        return ch + 0x20;
    }
    return ch;
}

KR_CONSTEXPR char kr_toupper(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return ch - 0x20;
    }
    return ch;
}

#endif /* !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION) */

#endif /* !defined(KRCTYPE_H) */
