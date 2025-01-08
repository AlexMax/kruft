/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "zztest.h"

#include "krstr.h"

TEST(str, kr_strcmp)
{
    EXPECT_TRUE(0 == kr_strcmp("abc", "abc"));
    EXPECT_TRUE(0 > kr_strcmp("abc", "def"));
    EXPECT_TRUE(0 < kr_strcmp("def", "abc"));
}

TEST(str, kr_strscpy)
{
    ptrdiff_t len;
    char buffer[8];

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "abcd", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcd");
    EXPECT_INTEQ(len, 4);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "abcdefg", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_INTEQ(len, 7);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "", sizeof(buffer));
    EXPECT_STREQ(buffer, "");
    EXPECT_INTEQ(len, 0);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "abcdefghijkl", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_INTEQ(len, -1);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strscpy(buffer, "abcd", 0);
    EXPECT_CHAREQ(buffer[0], '\xff');
    EXPECT_INTEQ(len, 0);
}

TEST(str, kr_strscat)
{
    ptrdiff_t len;
    char buffer[8];

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strscpy(buffer, "abc", sizeof(buffer));
    len = kr_strscat(buffer, "def", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdef");
    EXPECT_INTEQ(len, 6);

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strscpy(buffer, "abc", sizeof(buffer));
    len = kr_strscat(buffer, "defghi", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_INTEQ(len, -1);

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strscpy(buffer, "abc", sizeof(buffer));
    len = kr_strscat(buffer, "", sizeof(buffer));
    EXPECT_STREQ(buffer, "abc");
    EXPECT_INTEQ(len, 3);

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strscpy(buffer, "abc", sizeof(buffer));
    len = kr_strscat(buffer, "def", 0);
    EXPECT_STREQ(buffer, "abc");
    EXPECT_INTEQ(len, -1);
}

TEST(str, kr_strlcpy)
{
    size_t len;
    char buffer[8];

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "abcd", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcd");
    EXPECT_UINTEQ(len, 4);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "abcdefg", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_UINTEQ(len, 7);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "", sizeof(buffer));
    EXPECT_STREQ(buffer, "");
    EXPECT_UINTEQ(len, 0);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "abcdefghijkl", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_UINTEQ(len, 12);

    memset(buffer, 0xFF, sizeof(buffer));
    len = kr_strlcpy(buffer, "abcd", 0);
    EXPECT_CHAREQ(buffer[0], '\xff');
    EXPECT_UINTEQ(len, 0);
}

TEST(str, kr_strlcat)
{
    size_t len;
    char buffer[8];

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strlcpy(buffer, "abc", sizeof(buffer));
    len = kr_strlcat(buffer, "def", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdef");
    EXPECT_UINTEQ(len, 6);

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strlcpy(buffer, "abc", sizeof(buffer));
    len = kr_strlcat(buffer, "defghi", sizeof(buffer));
    EXPECT_STREQ(buffer, "abcdefg");
    EXPECT_UINTEQ(len, 9);

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strlcpy(buffer, "abc", sizeof(buffer));
    len = kr_strlcat(buffer, "", sizeof(buffer));
    EXPECT_STREQ(buffer, "abc");
    EXPECT_UINTEQ(len, 3);

    memset(buffer, 0xFF, sizeof(buffer));
    kr_strlcpy(buffer, "abc", sizeof(buffer));
    len = kr_strlcat(buffer, "def", 0);
    EXPECT_STREQ(buffer, "abc");
    EXPECT_UINTEQ(len, 0);
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

TEST(str, kr_strspn)
{
    EXPECT_UINTEQ(3, kr_strspn("plugh", "plu"));
    EXPECT_UINTEQ(3, kr_strspn("plugh", "ulp"));
    EXPECT_UINTEQ(5, kr_strspn("plugh", "plugh"));
    EXPECT_UINTEQ(0, kr_strspn("plugh", "xyz"));
    EXPECT_UINTEQ(0, kr_strspn("plugh", ""));
    EXPECT_UINTEQ(0, kr_strspn("", "xyz"));
}

TEST(str, kr_strcspn)
{
    EXPECT_UINTEQ(3, kr_strcspn("plugh", "ghxyz"));
    EXPECT_UINTEQ(3, kr_strcspn("plugh", "zyxhg"));
    EXPECT_UINTEQ(5, kr_strcspn("plugh", "xyz"));
    EXPECT_UINTEQ(0, kr_strcspn("plugh", "plugh"));
    EXPECT_UINTEQ(5, kr_strcspn("plugh", ""));
    EXPECT_UINTEQ(0, kr_strcspn("", "xyz"));
}

TEST(str, kr_strtok_r)
{
    char *r = NULL, *ptr = NULL;
    char buffer[32];

    {
        kr_strscpy(buffer, "foo/bar\\baz//\\plugh", sizeof(buffer));

        r = kr_strtok_r(buffer, "/\\", &ptr);
        EXPECT_STREQ(r, "foo");

        r = kr_strtok_r(NULL, "/\\", &ptr);
        EXPECT_STREQ(r, "bar");

        r = kr_strtok_r(NULL, "/\\", &ptr);
        EXPECT_STREQ(r, "baz");

        r = kr_strtok_r(NULL, "/\\", &ptr);
        EXPECT_STREQ(r, "plugh");

        r = kr_strtok_r(NULL, "/\\", &ptr);
        EXPECT_TRUE(r == NULL);
    }

    {
        kr_strscpy(buffer, "//foo\\", sizeof(buffer));

        r = kr_strtok_r(buffer, "/\\", &ptr);
        EXPECT_STREQ(r, "foo");

        r = kr_strtok_r(NULL, "/\\", &ptr);
        EXPECT_TRUE(r == NULL);
    }
}

TEST(str, kr_memccpy)
{
    char *ptr = NULL;
    char buffer[32];

    memset(buffer, 0x00, sizeof(buffer));
    ptr = KR_CASTS(char *, kr_memccpy(buffer, "The quick brown fox", (int)'b', 20));
    EXPECT_INTEQ(ptr - buffer, 11);
    *ptr = '\0';
    EXPECT_STREQ(buffer, "The quick b");

    memset(buffer, 0x00, sizeof(buffer));
    ptr = KR_CASTS(char *, kr_memccpy(buffer, "The quick brown fox", (int)'y', 21));
    EXPECT_TRUE(ptr == NULL);
    EXPECT_STREQ(buffer, "The quick brown fox");
}

SUITE(str)
{
    SUITE_TEST(str, kr_strcmp);
    SUITE_TEST(str, kr_strscpy);
    SUITE_TEST(str, kr_strscat);
    SUITE_TEST(str, kr_strlcpy);
    SUITE_TEST(str, kr_strlcat);
    SUITE_TEST(str, kr_stpecpy);
    SUITE_TEST(str, kr_strspn);
    SUITE_TEST(str, kr_strcspn);
    SUITE_TEST(str, kr_strtok_r);
    SUITE_TEST(str, kr_memccpy);
}
