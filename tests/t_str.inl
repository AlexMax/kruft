//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "zztest.h"

#include "krstr.h"

TEST(str, kr_strscpy)
{
    ptrdiff_t len;
    char buffer[8];

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "abcd", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcd");
    EXPECT_ISIZEEQ(len, 4);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "abcdefg", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_ISIZEEQ(len, 7);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "", sizeof(buffer));
    EXPECT_STREQ(buffer, "");
    EXPECT_ISIZEEQ(len, 0);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "abcdefghijkl", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_ISIZEEQ(len, -1);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "abcd", 0);
    EXPECT_CHAREQ(buffer[0], '\xff');
    EXPECT_ISIZEEQ(len, 0);
}

TEST(str, kr_strscat)
{
    ptrdiff_t len;
    char buffer[8];

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strscpy(buffer, "abc", sizeof(buffer));
    len = kr_strscat(buffer, "def", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdef");
    EXPECT_ISIZEEQ(len, 6);

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strscpy(buffer, "abc", sizeof(buffer));
    len = kr_strscat(buffer, "defghi", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_ISIZEEQ(len, -1);

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strscpy(buffer, "abc", sizeof(buffer));
    len = kr_strscat(buffer, "", sizeof(buffer));
    EXPECT_STREQ(buffer, "abc");
    EXPECT_ISIZEEQ(len, 3);

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strscpy(buffer, "abc", sizeof(buffer));
    len = kr_strscat(buffer, "def", 0);
    EXPECT_STREQ(buffer, "abc");
    EXPECT_ISIZEEQ(len, -1);
}

TEST(str, kr_strlcpy)
{
    size_t len;
    char buffer[8];

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "abcd", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcd");
    EXPECT_SIZEEQ(len, 4);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "abcdefg", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_SIZEEQ(len, 7);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "", sizeof(buffer));
    EXPECT_STREQ(buffer, "");
    EXPECT_SIZEEQ(len, 0);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "abcdefghijkl", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_SIZEEQ(len, 12);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "abcd", 0);
    EXPECT_CHAREQ(buffer[0], '\xff');
    EXPECT_SIZEEQ(len, 0);
}

TEST(str, kr_strlcat)
{
    size_t len;
    char buffer[8];

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strlcpy(buffer, "abc", sizeof(buffer));
    len = kr_strlcat(buffer, "def", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdef");
    EXPECT_SIZEEQ(len, 6);

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strlcpy(buffer, "abc", sizeof(buffer));
    len = kr_strlcat(buffer, "defghi", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_SIZEEQ(len, 9);

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strlcpy(buffer, "abc", sizeof(buffer));
    len = kr_strlcat(buffer, "", sizeof(buffer));
    EXPECT_STREQ(buffer, "abc");
    EXPECT_SIZEEQ(len, 3);

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strlcpy(buffer, "abc", sizeof(buffer));
    len = kr_strlcat(buffer, "def", 0);
    EXPECT_STREQ(buffer, "abc");
    EXPECT_SIZEEQ(len, 0);
}

TEST(str, kr_stpecpy)
{
    char buffer[8];
    char *end = buffer + sizeof(buffer);
    char *res = NULL;

    memset(buffer, 0xFF, sizeof(buffer));
    res = buffer;
    res = kr_stpecpy(res, end, "abc");
    EXPECT_STREQ(buffer, "abc");
    EXPECT_TRUE(res == buffer + 3);
    res = kr_stpecpy(res, end, "def");
    EXPECT_STREQ(buffer, "abcdef");
    EXPECT_TRUE(res == buffer + 6);
    res = kr_stpecpy(res, end, "ghi");
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_TRUE(res == NULL);
}

SUITE(str)
{
    SUITE_TEST(str, kr_strscpy);
    SUITE_TEST(str, kr_strscat);
    SUITE_TEST(str, kr_strlcpy);
    SUITE_TEST(str, kr_strlcat);
    SUITE_TEST(str, kr_stpecpy);
}
