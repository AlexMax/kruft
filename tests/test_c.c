//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "zztest.h"

#include <stdio.h>

int main()
{
    RUN_TESTS();
    RUN_TEST_SUITE(ctype);
    RUN_TEST_SUITE(lib);
    RUN_TEST_SUITE(str);
    return RUN_TESTS_RESULT();
}
