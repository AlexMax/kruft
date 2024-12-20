//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#define ZZTEST_IMPLEMENTATION
#include "zztest.h"

#include <stdio.h>

#include "t_bit.inl"
#include "t_ctype.inl"
#include "t_int.inl"
#include "t_lib.inl"
#include "t_serial.inl"
#include "t_str.inl"

int main()
{
    RUN_TESTS();
    RUN_TEST_SUITE(bit);
    RUN_TEST_SUITE(ctype);
    RUN_TEST_SUITE(int);
    RUN_TEST_SUITE(lib);
    RUN_TEST_SUITE(serial);
    RUN_TEST_SUITE(str);
    return RUN_TESTS_RESULT();
}
