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

typedef int8_t kr_i8;
typedef uint8_t kr_u8;

typedef int16_t kr_i16;
typedef uint16_t kr_u16;

typedef int32_t kr_i32;
typedef uint32_t kr_u32;

typedef int64_t kr_i64;
typedef uint64_t kr_u64;

#define KR_I8_MIN (INT8_MIN)
#define KR_I8_MAX (INT8_MAX)
#define KR_U8_MAX (UINT8_MAX)

#define KR_I16_MIN (INT16_MIN)
#define KR_I16_MAX (INT16_MAX)
#define KR_U16_MAX (UINT16_MAX)

#define KR_I32_MIN (INT32_MIN)
#define KR_I32_MAX (INT32_MAX)
#define KR_U32_MAX (UINT32_MAX)

#define KR_I64_MIN (INT64_MIN)
#define KR_I64_MAX (INT64_MAX)
#define KR_U64_MAX (UINT64_MAX)

#else

#include <limits.h>

#if (UCHAR_MAX == 0xff)
typedef signed char kr_i8;
typedef unsigned char kr_u8;
#endif

#if (UINT_MAX == 0xffff)
typedef signed int kr_i16;
typedef unsigned int kr_u16;
#elif (USHRT_MAX == 0xffff)
typedef signed short kr_i16;
typedef unsigned short kr_u16;
#endif

#if (UINT_MAX == 0xffffffff)
typedef signed int kr_i32;
typedef unsigned int kr_u32;
#elif (ULONG_MAX == 0xffffffff)
typedef signed long kr_i32;
typedef unsigned long kr_u32;
#endif

#if defined(_UI64_MAX) && (_UI64_MAX == 0xffffffffffffffff)             // MSVC
typedef signed __int64 kr_i64;
typedef unsigned __int64 kr_u64;
#elif defined(ULONG_LONG_MAX) && (ULONG_LONG_MAX == 0xffffffffffffffff) // GCC
typedef signed long long kr_i64;
typedef unsigned long long kr_u64;
#elif (ULONG_MAX == 0xffffffffffffffff)                                 // LP64
typedef signed long kr_i64;
typedef unsigned long kr_u64;
#elif defined(ULLONG_MAX) && (ULLONG_MAX == 0xffffffffffffffff)         // LLP64
typedef signed long long kr_i64;
typedef unsigned long long kr_u64;
#else
#define KR_SKIP_64BIT_
#endif

#define KR_I8_MIN (-128)
#define KR_I8_MAX (127)
#define KR_U8_MAX (0xff)

#define KR_I16_MIN (-32768)
#define KR_I16_MAX (32767)
#define KR_U16_MAX (0xffff)

#define KR_I32_MIN (-2147483648)
#define KR_I32_MAX (2147483647)
#define KR_U32_MAX (0xffffffff)

#if !defined(KR_SKIP_64BIT_)
#define KR_I64_MIN (-9223372036854775808)
#define KR_I64_MAX (9223372036854775807)
#define KR_U64_MAX (0xffffffffffffffff)
#endif

#undef KR_SKIP_64BIT_

#endif
