//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "krctype.h"

#include "zztest.h"

#include <ctype.h>

TEST(ctype, kr_isalnum)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isalnum(i);
        bool kr = kr_isalnum((char)i);
        EXPECT_TRUE(std, kr);
    }
}

TEST(ctype, kr_isalpha)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isalpha(i);
        bool kr = kr_isalpha((char)i);
        EXPECT_TRUE(std, kr);
    }
}

TEST(ctype, kr_islower)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = islower(i);
        bool kr = kr_islower((char)i);
        EXPECT_TRUE(std, kr);
    }
}

TEST(ctype, kr_isupper)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isupper(i);
        bool kr = kr_isupper((char)i);
        EXPECT_TRUE(std, kr);
    }
}

TEST(ctype, kr_isdigit)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isdigit(i);
        bool kr = kr_isdigit((char)i);
        EXPECT_TRUE(std, kr);
    }
}

TEST(ctype, kr_isxdigit)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isxdigit(i);
        bool kr = kr_isxdigit((char)i);
        EXPECT_TRUE(std, kr);
    }
}

TEST(ctype, kr_iscntrl)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = iscntrl(i);
        bool kr = kr_iscntrl((char)i);
        EXPECT_TRUE(std, kr);
    }
}

TEST(ctype, kr_isgraph)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isgraph(i);
        bool kr = kr_isgraph((char)i);
        EXPECT_TRUE(std, kr);
    }
}

TEST(ctype, kr_isspace)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isspace(i);
        bool kr = kr_isspace((char)i);
        EXPECT_TRUE(std, kr);
    }
}

TEST(ctype, kr_isblank)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isblank(i);
        bool kr = kr_isblank((char)i);
        EXPECT_TRUE(std, kr);
    }
}

TEST(ctype, kr_isprint)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isprint(i);
        bool kr = kr_isprint((char)i);
        EXPECT_TRUE(std, kr);
    }
}

TEST(ctype, kr_ispunct)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = ispunct(i);
        bool kr = kr_ispunct((char)i);
        EXPECT_TRUE(std, kr);
    }
}

TEST(ctype, kr_tolower)
{
    for (int i = 0; i < 0x100; i++)
    {
        char std = (char)tolower(i);
        char kr = kr_tolower((char)i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_toupper)
{
    for (int i = 0; i < 0x100; i++)
    {
        char std = (char)toupper(i);
        char kr = kr_toupper((char)i);
        EXPECT_EQ(std, kr);
    }
}

EXPORT_TEST_SUITE(ctype) = {
    EXPORT_TEST(ctype, kr_isalnum), EXPORT_TEST(ctype, kr_isalpha), EXPORT_TEST(ctype, kr_islower),
    EXPORT_TEST(ctype, kr_isupper), EXPORT_TEST(ctype, kr_isdigit), EXPORT_TEST(ctype, kr_isxdigit),
    EXPORT_TEST(ctype, kr_iscntrl), EXPORT_TEST(ctype, kr_isgraph), EXPORT_TEST(ctype, kr_isspace),
    EXPORT_TEST(ctype, kr_isblank), EXPORT_TEST(ctype, kr_isprint), EXPORT_TEST(ctype, kr_ispunct),
    EXPORT_TEST(ctype, kr_tolower), EXPORT_TEST(ctype, kr_toupper),
};
EXPORT_TEST_SUITE_COUNT(ctype);
