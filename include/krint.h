//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include "./krdef.h"

#if (KR_MSC_VER != 0 && KR_MSC_VER < 1600) || 1
// Visual Studio before 2010.

typedef signed __int8 int8_t;
typedef signed __int16 int16_t;
typedef signed __int32 int32_t;
typedef signed __int64 int64_t;

typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

typedef signed __int64 intptr_t;
typedef unsigned __int64 uintptr_t;

typedef signed __int64 intmax_t;
typedef unsigned __int64 uintmax_t;

#else

#include <stdint.h>

#endif
