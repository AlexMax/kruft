//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

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
    SUCCEED();

    ptr2 = kr_reallocarray(NULL, SIZE_MAX, 8);
    if (ptr2 != NULL)
    {
        ADD_FAILURE();
        goto done;
    }
    SUCCEED();

    ptr3 = kr_reallocarray(NULL, 8, SIZE_MAX);
    if (ptr3 != NULL)
    {
        ADD_FAILURE();
        goto done;
    }
    SUCCEED();

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
    SUCCEED();

done:
    free(ptr1);
    free(ptr2);
    free(ptr3);
    free(ptr4);
}

EXPORT_TEST_SUITE(lib) = {
    EXPORT_TEST(lib, kr_reallocarray),
};
