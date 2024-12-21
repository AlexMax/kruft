//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include "./krconfig.h"

#if defined(__has_include)
#if __has_include(<stdint.h>)
#define KR_USE_STDINT_
#endif // __has_include(<stdint.h>)
#elif (KR_MSC_VER >= 1600 || KR_STDC_VERSION >= 199901)
#define KR_USE_STDINT_
#endif

#if defined(KR_USE_STDINT_)
#if (!KR_CONFIG_NOINCLUDE)
#include <stdint.h>
#endif
#undef KR_USE_STDINT_
#else // defined(KR_USE_STDINT_)
#if (!KR_CONFIG_NOINCLUDE)
#include <limits.h>
#endif

#if (UCHAR_MAX == 0xff)
typedef signed char int8_t;
typedef unsigned char uint8_t;
#endif

#if (UINT_MAX == 0xffff)
typedef signed int int16_t;
typedef unsigned int uint16_t;
#elif (USHRT_MAX == 0xffff)
typedef signed short int16_t;
typedef unsigned short uint16_t;
#endif

#if (UINT_MAX == 0xffffffff)
typedef signed int int32_t;
typedef unsigned int uint32_t;
#elif (ULONG_MAX == 0xffffffff)
typedef signed long int32_t;
typedef unsigned long uint32_t;
#endif

#if defined(_UI64_MAX)                                                  // MSVC
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;
#elif defined(ULONG_LONG_MAX) && (ULONG_LONG_MAX == 0xffffffffffffffff) // GCC
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
#elif (ULONG_MAX == 0xffffffffffffffff)                                 // LP64
typedef signed long int64_t;
typedef unsigned long uint64_t;
#elif defined(ULLONG_MAX) && (ULLONG_MAX == 0xffffffffffffffff)         // LLP64
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
#else
#define KR_SKIP_64BIT_
#endif

#define INT8_MIN (-127 - 1)
#define INT8_MAX (127)
#define UINT8_MAX (0xff)

#define INT16_MIN (-32767 - 1)
#define INT16_MAX (32767)
#define UINT16_MAX (0xffff)

#define INT32_MIN (-2147483647 - 1)
#define INT32_MAX (2147483647)
#define UINT32_MAX (0xffffffff)

#if !defined(KR_SKIP_64BIT_)
#define INT64_MIN (-9223372036854775807 - 1)
#define INT64_MAX (9223372036854775807)
#define UINT64_MAX (0xffffffffffffffff)
#endif

#undef KR_SKIP_64BIT_

#endif // defined(KR_USE_STDINT_)
