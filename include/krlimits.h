//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include "./krconfig.h"

#include <limits.h>

// Some ancient versions of GCC define LONG_LONG_* macros but not LLONG_*.

#if !defined(LLONG_MIN) && defined(LONG_LONG_MIN)
#define LLONG_MAX (LONG_LONG_MAX)
#endif

#if !defined(LLONG_MAX) && defined(LONG_LONG_MAX)
#define LLONG_MAX (LONG_LONG_MAX)
#endif

#if !defined(ULLONG_MAX) && defined(ULONG_LONG_MAX)
#define LLONG_MAX (LONG_LONG_MAX)
#endif

// C23 defines.

#if !defined(CHAR_WIDTH)
#define CHAR_WIDTH (CHAR_BIT)
#endif

#if !defined(SCHAR_WIDTH)
#define SCHAR_WIDTH (CHAR_WIDTH)
#endif

#if !defined(UCHAR_WIDTH)
#define UCHAR_WIDTH (CHAR_WIDTH)
#endif

#if !defined(SHRT_WIDTH)
#if (SHRT_MAX == 0x7fff)
#define SHRT_WIDTH (CHAR_WIDTH * 2)
#elif (SHRT_MAX == 0x7fffffff)
#define SHRT_WIDTH (CHAR_WIDTH * 4)
#endif
#endif // !defined(SHRT_WIDTH)

#if !defined(USHRT_WIDTH)
#define USHRT_WIDTH (SHRT_WIDTH)
#endif

#if !defined(INT_WIDTH)
#if (INT_MAX == 0x7fff)
#define INT_WIDTH (CHAR_WIDTH * 2)
#elif (INT_MAX == 0x7fffffff)
#define INT_WIDTH (CHAR_WIDTH * 4)
#elif (INT_MAX == 0x7fffffffffffffff)
#define INT_WIDTH (CHAR_WIDTH * 8)
#endif
#endif // !defined(INT_WIDTH)

#if !defined(UINT_WIDTH)
#define UINT_WIDTH (INT_WIDTH)
#endif

#if !defined(LONG_WIDTH)
#if (LONG_MAX == 0x7fffffffl)
#define LONG_WIDTH (CHAR_WIDTH * 4)
#elif (LONG_MAX == 0x7fffffffffffffffl)
#define LONG_WIDTH (CHAR_WIDTH * 8)
#endif
#endif // !defined(LONG_WIDTH)

#if !defined(ULONG_WIDTH)
#define ULONG_WIDTH (LONG_WIDTH)
#endif

#if !defined(LLONG_WIDTH)
#if defined(LLONG_MAX)
#if (LLONG_MAX == 0x7fffffffffffffffll)
#define LLONG_WIDTH (CHAR_WIDTH * 8)
#endif
#endif // defined(LLONG_MAX)
#endif // !defined(LLONG_WIDTH)

#if !defined(ULLONG_WIDTH)
#define ULLONG_WIDTH (LLONG_WIDTH)
#endif
