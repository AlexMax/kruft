/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "krconfig.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>

#define XSTR(a) STR_(a)
#define STR_(a) #a

int main()
{
    printf("=== types ===\n");
    printf("sizeof(char): %lu\n", (unsigned long)sizeof(char));
    printf("sizeof(short): %lu\n", (unsigned long)sizeof(short));
    printf("sizeof(int): %lu\n", (unsigned long)sizeof(int));
    printf("sizeof(long): %lu\n", (unsigned long)sizeof(long));
#if defined(ULLONG_MAX)
    printf("sizeof(long long): %lu\n", (unsigned long)sizeof(long long));
#endif
    printf("sizeof(void*): %lu\n", (unsigned long)sizeof(void *));
    printf("sizeof(size_t): %lu\n", (unsigned long)sizeof(size_t));
    printf("sizeof(ptrdiff_t): %lu\n", (unsigned long)sizeof(ptrdiff_t));

    printf("\n=== krconfig.h ===\n");
    printf("KR_MSC_VER: %d\n", KR_MSC_VER);
    printf("KR_GNUC: %d\n", KR_GNUC);
    printf("KR_CLANG: %d\n", KR_CLANG);
    printf("KR_STDC_VERSION: %ld\n", (long)KR_STDC_VERSION);
    printf("KR_BYTE_ORDER: %d\n", KR_BYTE_ORDER);
    printf("KR_SIZEOF_POINTER: %d\n", KR_SIZEOF_POINTER);
    printf("KR_SIZEOF_PTRDIFF_T: %d\n", KR_SIZEOF_PTRDIFF_T);
    printf("KR_CONSTEXPR: %s\n", XSTR(KR_CONSTEXPR));
    printf("KR_FORCEINLINE: %s\n", XSTR(KR_FORCEINLINE));
    printf("KR_INLINE: %s\n", XSTR(KR_INLINE));
#if 0
    printf("KR_NODISCARD: %s\n", XSTR(KR_NODISCARD));
    printf("KR_NOEXCEPT: %s\n", XSTR(KR_NOEXCEPT));
    printf("KR_RESTRICT: %s\n", XSTR(KR_RESTRICT));
    printf("KR_THREAD: %s\n", XSTR(KR_THREAD));
#endif

    return 0;
}
