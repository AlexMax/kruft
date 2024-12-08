//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "krstr.h"

#include "gtest/gtest.h"

TEST(str, kr_strscpy)
{
    size_t len;
    char buffer[8];

    std::memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "abcd", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcd");
    EXPECT_EQ(len, 4);

    std::memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "abcdefg", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_EQ(len, 7);

    std::memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "", sizeof(buffer));
    EXPECT_STREQ(buffer, "");
    EXPECT_EQ(len, 0);

    std::memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "abcdefghijkl", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_EQ(len, -1);

    std::memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "abcd", 0);
    EXPECT_EQ(buffer[0], '\xff');
    EXPECT_EQ(len, 0);
}

TEST(str, kr_strscat)
{
    ptrdiff_t len;
    char buffer[8];

    std::memset(buffer, 0xFF, sizeof(buffer));
    kr_strscpy(buffer, "abc", sizeof(buffer));
    len = kr_strscat(buffer, "def", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdef");
    EXPECT_EQ(len, 6);

    std::memset(buffer, 0xFF, sizeof(buffer));
    kr_strscpy(buffer, "abc", sizeof(buffer));
    len = kr_strscat(buffer, "defghi", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_EQ(len, -1);

    std::memset(buffer, 0xFF, sizeof(buffer));
    kr_strscpy(buffer, "abc", sizeof(buffer));
    len = kr_strscat(buffer, "", sizeof(buffer));
    EXPECT_STREQ(buffer, "abc");
    EXPECT_EQ(len, 3);

    std::memset(buffer, 0xFF, sizeof(buffer));
    kr_strscpy(buffer, "abc", sizeof(buffer));
    len = kr_strscat(buffer, "def", 0);
    EXPECT_STREQ(buffer, "abc");
    EXPECT_EQ(len, -1);
}

TEST(str, kr_strlcpy)
{
    size_t len;
    char buffer[8];

    std::memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "abcd", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcd");
    EXPECT_EQ(len, 4);

    std::memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "abcdefg", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_EQ(len, 7);

    std::memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "", sizeof(buffer));
    EXPECT_STREQ(buffer, "");
    EXPECT_EQ(len, 0);

    std::memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "abcdefghijkl", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_EQ(len, 12);

    std::memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "abcd", 0);
    EXPECT_EQ(buffer[0], '\xff');
    EXPECT_EQ(len, 0);
}

TEST(str, kr_strlcat)
{
    size_t len;
    char buffer[8];

    std::memset(buffer, 0xFF, sizeof(buffer));
    kr_strlcpy(buffer, "abc", sizeof(buffer));
    len = kr_strlcat(buffer, "def", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdef");
    EXPECT_EQ(len, 6);

    std::memset(buffer, 0xFF, sizeof(buffer));
    kr_strlcpy(buffer, "abc", sizeof(buffer));
    len = kr_strlcat(buffer, "defghi", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_EQ(len, 9);

    std::memset(buffer, 0xFF, sizeof(buffer));
    kr_strlcpy(buffer, "abc", sizeof(buffer));
    len = kr_strlcat(buffer, "", sizeof(buffer));
    EXPECT_STREQ(buffer, "abc");
    EXPECT_EQ(len, 3);

    std::memset(buffer, 0xFF, sizeof(buffer));
    kr_strlcpy(buffer, "abc", sizeof(buffer));
    len = kr_strlcat(buffer, "def", 0);
    EXPECT_STREQ(buffer, "abc");
    EXPECT_EQ(len, 0);
}

TEST(str, kr_stpecpy)
{
    char buffer[8];
    char *end = buffer + sizeof(buffer);
    char *res = nullptr;

    std::memset(buffer, 0xFF, sizeof(buffer));
    res = buffer;
    res = kr_stpecpy(res, end, "abc");
    EXPECT_STREQ(buffer, "abc");
    EXPECT_EQ(res, buffer + 3);
    res = kr_stpecpy(res, end, "def");
    EXPECT_STREQ(buffer, "abcdef");
    EXPECT_EQ(res, buffer + 6);
    res = kr_stpecpy(res, end, "ghi");
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_EQ(res, nullptr);
}
