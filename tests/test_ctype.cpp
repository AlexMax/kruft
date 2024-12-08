//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "krctype.h"

#include "gtest/gtest.h"

TEST(ctype, kr_isalnum)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isalnum(i);
        bool kr = kr_isalnum(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_isalpha)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isalpha(i);
        bool kr = kr_isalpha(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_islower)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = islower(i);
        bool kr = kr_islower(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_isupper)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isupper(i);
        bool kr = kr_isupper(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_isdigit)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isdigit(i);
        bool kr = kr_isdigit(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_isxdigit)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isxdigit(i);
        bool kr = kr_isxdigit(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_iscntrl)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = iscntrl(i);
        bool kr = kr_iscntrl(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_isgraph)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isgraph(i);
        bool kr = kr_isgraph(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_isspace)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isspace(i);
        bool kr = kr_isspace(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_isblank)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isblank(i);
        bool kr = kr_isblank(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_isprint)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = isprint(i);
        bool kr = kr_isprint(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_ispunct)
{
    for (int i = 0; i < 0x100; i++)
    {
        bool std = ispunct(i);
        bool kr = kr_ispunct(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_tolower)
{
    for (int i = 0; i < 0x100; i++)
    {
        char std = tolower(i);
        char kr = kr_tolower(i);
        EXPECT_EQ(std, kr);
    }
}

TEST(ctype, kr_toupper)
{
    for (int i = 0; i < 0x100; i++)
    {
        char std = toupper(i);
        char kr = kr_toupper(i);
        EXPECT_EQ(std, kr);
    }
}
