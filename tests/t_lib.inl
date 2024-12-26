/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "zztest.h"

#include "krlib.h"

#include "krint.h"

TEST(lib, kr_reallocarray)
{
    void *ptr1 = NULL, *ptr2 = NULL, *ptr3 = NULL, *ptr4 = NULL;

    ptr1 = kr_reallocarray(NULL, 8, 16);
    if (ptr1 == NULL)
    {
        ADD_FAILURE();
        goto done;
    }

    ptr2 = kr_reallocarray(NULL, SIZE_MAX, 8);
    if (ptr2 != NULL)
    {
        ADD_FAILURE();
        goto done;
    }

    ptr3 = kr_reallocarray(NULL, 8, SIZE_MAX);
    if (ptr3 != NULL)
    {
        ADD_FAILURE();
        goto done;
    }

    ptr4 = kr_reallocarray(ptr1, 8, 4);
    if (ptr4 == NULL)
    {
        ADD_FAILURE();
        goto done;
    }
    else
    {
        ptr1 = NULL;
    }

done:
    KR_FREE(ptr1);
    KR_FREE(ptr2);
    KR_FREE(ptr3);
    KR_FREE(ptr4);
}

SUITE(lib)
{
    SUITE_TEST(lib, kr_reallocarray);
}
