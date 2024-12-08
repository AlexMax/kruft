//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <stdbool.h>
#include <stdint.h>

#if defined(__cplusplus)
#define KR_CASTR(t, u) (reinterpret_cast<t>(u))
#else
#define KR_CASTR(t, u) (t)(u)
#endif

#if defined(__cplusplus)
#define KR_CASTS(t, u) (static_cast<t>(u))
#else
#define KR_CASTS(t, u) (t)(u)
#endif

#if defined(__cplusplus)
#define KR_CONSTEXPR constexpr
#else
#define KR_CONSTEXPR inline
#endif

#if defined(__cplusplus)
#define KR_NODISCARD [[nodiscard]]
#else
#define KR_NODISCARD
#endif

#if defined(__cplusplus)
#define KR_NULL (nullptr)
#else
#define KR_NULL (NULL)
#endif

#if defined(_MSC_VER)
#define KR_RESTRICT __restrict
#else
#define KR_RESTRICT __restrict__
#endif

#if defined(_MSC_VER)
#define KR_THREAD __declspec(thread)
#else
#define KR_THREAD __thread
#endif

#if defined(_MSC_VER)
#define KR_UNREACHABLE() (__assume(0))
#else
#define KR_UNREACHABLE() (__builtin_unreachable())
#endif
