//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include "./krdef.h"

#if (KR_MSC_VER >= 1600 || KR_STDC_VERSION >= 199901)

#include <stdint.h>

#else

#include <limits.h>

#if defined(UCHAR_MAX) && (UCHAR_MAX == 0xff)
typedef signed char int8_t;
typedef unsigned char uint8_t;
#endif

#if defined(USHRT_MAX) && (USHRT_MAX == 0xffff)
typedef signed short int16_t;
typedef unsigned short uint16_t;
#elif defined(UINT_MAX) && (UINT_MAX == 0xffff)
typedef signed int int16_t;
typedef unsigned int uint16_t;
#endif

#if defined(UINT_MAX) && (UINT_MAX == 0xffffffff)
typedef signed int int32_t;
typedef unsigned int uint32_t;
#elif defined(ULONG_MAX) && (ULONG_MAX == 0xffffffff)
typedef signed long int32_t;
typedef unsigned long uint32_t;
#endif

#if defined(ULONG_MAX) && (ULONG_MAX == 0xffffffffffffffff)
typedef signed int int64_t;
typedef unsigned int uint64_t;
#elif defined(ULLONG_MAX) && (ULLONG_MAX == 0xffffffffffffffff)
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
#elif defined(ULONG_LONG_MAX) && (ULONG_LONG_MAX == 0xffffffffffffffff) // GCC
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
#elif defined(_UI64_MAX) && (_UI64_MAX == 0xffffffffffffffff)           // Visual C++ 6.0
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif

typedef signed __int64 intptr_t;
typedef unsigned __int64 uintptr_t;

typedef signed __int64 intmax_t;
typedef unsigned __int64 uintmax_t;

#endif
