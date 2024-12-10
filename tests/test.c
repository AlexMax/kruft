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
