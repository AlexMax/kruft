//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "krlib.h"

#include "gtest/gtest.h"

TEST(lib, kr_reallocarray)
{
    void *ptr1 = nullptr, *ptr2 = nullptr, *ptr3 = nullptr, *ptr4 = nullptr;

    ptr1 = kr_reallocarray(nullptr, 8, 16);
    if (ptr1 == nullptr)
    {
        ADD_FAILURE();
        goto done;
    }
    SUCCEED();

    ptr2 = kr_reallocarray(nullptr, SIZE_MAX, 8);
    if (ptr2 != nullptr)
    {
        ADD_FAILURE();
        goto done;
    }
    SUCCEED();

    ptr3 = kr_reallocarray(nullptr, 8, SIZE_MAX);
    if (ptr3 != nullptr)
    {
        ADD_FAILURE();
        goto done;
    }
    SUCCEED();

    ptr4 = kr_reallocarray(ptr1, 8, 4);
    if (ptr4 == nullptr)
    {
        ADD_FAILURE();
        goto done;
    }
    else
    {
        ptr1 = nullptr;
    }
    SUCCEED();

done:
    free(ptr1);
    free(ptr2);
    free(ptr3);
    free(ptr4);
}
