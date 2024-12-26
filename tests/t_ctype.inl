/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "zztest.h"

#include "krctype.h"

#include <ctype.h>

TEST(ctype, kr_isalnum)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        bool std = isalnum(i);
        bool kr = kr_isalnum((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_isalpha)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        bool std = isalpha(i);
        bool kr = kr_isalpha((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_islower)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        bool std = islower(i);
        bool kr = kr_islower((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_isupper)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        bool std = isupper(i);
        bool kr = kr_isupper((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_isdigit)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        bool std = isdigit(i);
        bool kr = kr_isdigit((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_isxdigit)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        bool std = isxdigit(i);
        bool kr = kr_isxdigit((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_iscntrl)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        bool std = iscntrl(i);
        bool kr = kr_iscntrl((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_isgraph)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        bool std = isgraph(i);
        bool kr = kr_isgraph((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_isspace)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        bool std = isspace(i);
        bool kr = kr_isspace((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_isblank)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        bool std = i == 0x09 || i == 0x20;
        bool kr = kr_isblank((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_isprint)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        bool std = isprint(i);
        bool kr = kr_isprint((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_ispunct)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        bool std = ispunct(i);
        bool kr = kr_ispunct((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_tolower)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        char std = (char)tolower(i);
        char kr = kr_tolower((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

TEST(ctype, kr_toupper)
{
    int i;

    for (i = 0; i < 0x100; i++)
    {
        char std = (char)toupper(i);
        char kr = kr_toupper((char)i);
        EXPECT_BOOLEQ(std, kr);
    }
}

SUITE(ctype)
{
    SUITE_TEST(ctype, kr_isalnum);
    SUITE_TEST(ctype, kr_isalpha);
    SUITE_TEST(ctype, kr_islower);
    SUITE_TEST(ctype, kr_isupper);
    SUITE_TEST(ctype, kr_isdigit);
    SUITE_TEST(ctype, kr_isxdigit);
    SUITE_TEST(ctype, kr_iscntrl);
    SUITE_TEST(ctype, kr_isgraph);
    SUITE_TEST(ctype, kr_isspace);
    SUITE_TEST(ctype, kr_isblank);
    SUITE_TEST(ctype, kr_isprint);
    SUITE_TEST(ctype, kr_ispunct);
    SUITE_TEST(ctype, kr_tolower);
    SUITE_TEST(ctype, kr_toupper);
}
