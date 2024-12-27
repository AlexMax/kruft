/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(KRINT_H)
#define KRINT_H

#include "./krconfig.h"

#include "krlimits.h"
#include <stddef.h>

/*
 * If we have an stdint.h, we should be using it.  Not using stdint.h on
 * a platform that has the header will result in mountains of compatibility
 * issues since our types might not line up.
 */

#if defined(__has_include)
#if __has_include(<stdint.h>)
#define KR_USE_STDINT_
#endif /* __has_include(<stdint.h>) */
#elif (KR_MSC_VER >= 1600 || KR_STDC_VERSION >= 199901)
#define KR_USE_STDINT_
#endif

#if defined(KR_USE_STDINT_)
#if (!KR_CONFIG_NOINCLUDE)
#include <stdint.h>
#endif /* (!KR_CONFIG_NOINCLUDE) */
#else  /* defined(KR_USE_STDINT_) */

/* C99: Lowest-rank type that can fit 8 bits. */

#if (CHAR_WIDTH == 8)
typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
#define INT8_C(x) (x)
#define UINT8_C(x) (x)
#else
#define KR_NO8_
#endif /* (CHAR_WIDTH == 8) */

/* C99: Lowest-rank type that can fit 16 bits. */

#if (CHAR_WIDTH == 16)
typedef signed char int_least16_t;
typedef unsigned char uint_least16_t;
#define INT16_C(x) (x)
#define UINT16_C(x) (x)
#elif (SHRT_WIDTH == 16)
typedef signed short int_least16_t;
typedef unsigned short uint_least16_t;
#define INT16_C(x) (x)
#define UINT16_C(x) (x)
#else
#define KR_NO16_
#endif /* (CHAR_WIDTH == 16) */

/* C99: Lowest-rank type that can fit 32 bits. */

#if (CHAR_WIDTH == 32)
typedef signed char int_least32_t;
typedef unsigned char uint_least32_t;
#define INT32_C(x) (x)
#define UINT32_C(x) (x)
#elif (SHRT_WIDTH == 32)
typedef signed short int_least32_t;
typedef unsigned short uint_least32_t;
#define INT32_C(x) (x)
#define UINT32_C(x) (x)
#elif (INT_WIDTH == 32)
typedef signed int int_least32_t;
typedef unsigned int uint_least32_t;
#define INT32_C(x) (x)
#define UINT32_C(x) (x##u)
#elif (LONG_WIDTH == 32)
typedef signed long int_least32_t;
typedef unsigned long uint_least32_t;
#define INT32_C(x) (x##l)
#define UINT32_C(x) (x##ul)
#else
#define KR_NO32_
#endif /* (CHAR_WIDTH == 32) */

/* C99: Lowest-rank type that can fit 64 bits. */

#if defined(_UI64_MAX)
typedef signed __int64 int_least64_t;
typedef unsigned __int64 uint_least64_t;
#define INT64_C(x) (x##i64)
#define UINT64_C(x) (x##ui64)
#elif (CHAR_WIDTH == 64)
typedef signed char int_least64_t;
typedef unsigned char uint_least64_t;
#define INT64_C(x) (x)
#define UINT64_C(x) (x)
#elif (SHRT_WIDTH == 64)
typedef signed short int_least64_t;
typedef unsigned short uint_least64_t;
#define INT64_C(x) (x)
#define UINT64_C(x) (x)
#elif (INT_WIDTH == 64)
typedef signed int int_least64_t;
typedef unsigned int uint_least64_t;
#define INT64_C(x) (x)
#define UINT64_C(x) (x##u)
#elif (LONG_WIDTH == 64)
typedef signed long int_least64_t;
typedef unsigned long uint_least64_t;
#define INT64_C(x) (x##l)
#define UINT64_C(x) (x##ul)
#elif (LLONG_WIDTH == 64)
typedef signed long long int_least64_t;
typedef unsigned long long uint_least64_t;
#define INT64_C(x) (x##ll)
#define UINT64_C(x) (x##ull)
#else /* (CHAR_WIDTH == 64) */
#define KR_NO64_
#endif /* (CHAR_WIDTH == 64) */

/*
 * Next, figure out the "fast" types.  It is assumed that int is the fastest
 * version of a type for a given width.  Everything else is the same as least.
 */

#if !defined(KR_NO8_)
typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef signed char int8_t;
typedef unsigned char uint8_t;

#define INT8_MIN (-127 - 1)
#define INT8_MAX (127)
#define UINT8_MAX (0xff)

#define INT_FAST8_MIN INT8_MIN
#define INT_FAST8_MAX INT8_MAX
#define UINT_FAST8_MAX UINT8_MAX

#define INT_LEAST8_MIN INT8_MIN
#define INT_LEAST8_MAX INT8_MAX
#define UINT_LEAST8_MAX UINT8_MAX
#endif /* !defined(KR_NO8_) */

#if !defined(KR_NO16_)
#if (INT_WIDTH == 16)
typedef signed int int_fast16_t;
typedef unsigned int uint_fast16_t;
typedef signed int int16_t;
typedef unsigned int uint16_t;
#else
typedef int_least16_t int_fast16_t;
typedef uint_least16_t uint_fast16_t;
typedef int_least16_t int16_t;
typedef uint_least16_t uint16_t;
#endif

#define INT16_MIN (-32767 - 1)
#define INT16_MAX (32767)
#define UINT16_MAX (0xffff)

#define INT_FAST16_MIN INT16_MIN
#define INT_FAST16_MAX INT16_MAX
#define UINT_FAST16_MAX UINT16_MAX

#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST16_MAX INT16_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#endif /* !defined(KR_NO16_) */

#if !defined(KR_NO32_)
#if (INT_WIDTH == 32)
typedef signed int int_fast32_t;
typedef unsigned int uint_fast32_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
#else
typedef int_least32_t int_fast32_t;
typedef uint_least32_t uint_fast32_t;
typedef int_least32_t int32_t;
typedef uint_least32_t uint32_t;
#endif

#define INT32_MIN (-2147483647 - 1)
#define INT32_MAX (2147483647)
#define UINT32_MAX (0xffffffff)

#define INT_FAST32_MIN INT32_MIN
#define INT_FAST32_MAX INT32_MAX
#define UINT_FAST32_MAX UINT32_MAX

#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST32_MAX INT32_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#endif /* !defined(KR_NO32_) */

#if !defined(KR_NO64_)
#if (INT_WIDTH == 64)
typedef signed int int_fast64_t;
typedef unsigned int uint_fast64_t;
typedef signed int int64_t;
typedef unsigned int uint64_t;
#else
typedef int_least64_t int_fast64_t;
typedef uint_least64_t uint_fast64_t;
typedef int_least64_t int64_t;
typedef uint_least64_t uint64_t;
#endif

#define INT64_MIN (-9223372036854775807 - 1)
#define INT64_MAX (9223372036854775807)
#define UINT64_MAX (0xffffffffffffffff)

#define INT_FAST64_MIN INT64_MIN
#define INT_FAST64_MAX INT64_MAX
#define UINT_FAST64_MAX UINT64_MAX

#define INT_LEAST64_MIN INT64_MIN
#define INT_LEAST64_MAX INT64_MAX
#define UINT_LEAST64_MAX UINT64_MAX
#endif /* !defined(KR_NO64_) */

/* Maximum-size int. */

#if !defined(KR_NO64_)
typedef int_least64_t intmax_t;
typedef uint_least64_t uintmax_t;
#elif !defined(KR_NO64_)
typedef int_least32_t intmax_t;
typedef uint_least32_t uintmax_t;
#elif !defined(KR_NO64_)
typedef int_least16_t intmax_t;
typedef uint_least16_t uintmax_t;
#elif !defined(KR_NO64_)
typedef int_least8_t intmax_t;
typedef uint_least8_t uintmax_t;
#endif /* !defined(KR_NO64_) */

/* Types wide enough to hold pointers. */

#if (KR_SIZEOF_POINTER == 1)
typedef int_fast8_t intptr_t;
typedef uint_fast8_t uintptr_t;
#elif (KR_SIZEOF_POINTER == 2)
typedef int_fast16_t intptr_t;
typedef uint_fast16_t uintptr_t;
#elif (KR_SIZEOF_POINTER == 4)
typedef int_fast32_t intptr_t;
typedef uint_fast32_t uintptr_t;
#elif (KR_SIZEOF_POINTER == 8)
typedef int_fast64_t intptr_t;
typedef uint_fast64_t uintptr_t;
#endif

#endif /* defined(KR_USE_STDINT_) */

/* C99: Maximum value of size_t. */

#if !defined(SIZE_MAX)
#if (KR_SIZEOF_SIZE_T == 1)
#define SIZE_MAX (0xff)
#elif (KR_SIZEOF_SIZE_T == 2)
#define SIZE_MAX (0xffff)
#elif (KR_SIZEOF_SIZE_T == 4)
#define SIZE_MAX (0xffffffff)
#elif (KR_SIZEOF_SIZE_T == 8)
#define SIZE_MAX (0xffffffffffffffff)
#endif /* (KR_SIZEOF_SIZE_T == 1) */
#endif /* !defined(SIZE_MAX) */

/* C99: Minimum and maximum of ptrdiff_t. */

#if !defined(PTRDIFF_MIN) && !defined(PTRDIFF_MAX)
#if (KR_SIZEOF_PTRDIFF_T == 1)
#define PTRDIFF_MIN INT8_MIN
#define PTRDIFF_MAX INT8_MAX
#elif (KR_SIZEOF_PTRDIFF_T == 2)
#define PTRDIFF_MIN INT16_MIN
#define PTRDIFF_MAX INT16_MAX
#elif (KR_SIZEOF_PTRDIFF_T == 4)
#define PTRDIFF_MIN INT32_MIN
#define PTRDIFF_MAX INT32_MAX
#elif (KR_SIZEOF_PTRDIFF_T == 8)
#define PTRDIFF_MIN INT64_MIN
#define PTRDIFF_MAX INT64_MAX
#endif /* (PTRDIFF_WIDTH == 8) */
#endif /* !defined(PTRDIFF_MIN) && !defined(PTRDIFF_MAX) */

/* C23: Width of size_t. */

#if !defined(SIZE_WIDTH)
#define SIZE_WIDTH (KR_SIZEOF_SIZE_T * CHAR_BIT)
#endif /* !defined(SIZE_WIDTH) */

/* C23: Width of ptrdiff_t in bits. */

#if !defined(PTRDIFF_WIDTH)
#define PTRDIFF_WIDTH (KR_SIZEOF_PTRDIFF_T * CHAR_BIT)
#endif

#undef KR_NO8_
#undef KR_NO16_
#undef KR_NO32_
#undef KR_NO64_
#undef KR_USE_STDINT_

#endif /* !defined(KRINT_H) */
