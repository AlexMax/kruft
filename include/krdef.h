//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

//
// User configuration settings:
//
// KR_CONFIG_NOINCLUDE: If defined, does not include any libc header
//                      automatically.
//

#pragma once

// Configuration.

#if !defined(KR_CONFIG_NOINCLUDE)
#define KR_CONFIG_NOINCLUDE (0)
#endif

// Compiler detection.

#if defined(_MSC_VER)
#define KR_MSC_VER (_MSC_VER)
#else
#define KR_MSC_VER (0)
#endif

#if defined(__GNUC__)
#define KR_GNUC (__GNUC__)
#else
#define KR_GNUC (0)
#endif

#if defined(__clang__)
#define KR_CLANG (__clang__)
#else
#define KR_CLANG (0)
#endif

#if defined(__STDC_VERSION__)
#define KR_STDC_VERSION (__STDC_VERSION__)
#else
#define KR_STDC_VERSION (0)
#endif

#if defined(__cplusplus) && defined(_MSVC_LANG)
#define KR_CPLUSPLUS (_MSVC_LANG)
#elif defined(__cplusplus)
#define KR_CPLUSPLUS (__cplusplus)
#else
#define KR_CPLUSPLUS (0)
#endif

#if (KR_CPLUSPLUS)
#define KR_CASTR(t, u) (reinterpret_cast<t>(u))
#else
#define KR_CASTR(t, u) (t)(u)
#endif

#if (KR_CPLUSPLUS)
#define KR_CASTS(t, u) (static_cast<t>(u))
#else
#define KR_CASTS(t, u) (t)(u)
#endif

#if (KR_CPLUSPLUS >= 201103)
#define KR_CONSTEXPR constexpr
#elif (KR_MSC_VER != 0 && KR_MSC_VER < 1900) // Visual C++ 2015
#define KR_CONSTEXPR __inline
#else
#define KR_CONSTEXPR inline
#endif

#if (KR_MSC_VER)
#define KR_FORCEINLINE __forceinline
#else
#define KR_FORCEINLINE inline __attribute__((always_inline))
#endif

#if (KR_MSC_VER < 1900) // Visual C++ 2015
#define KR_INLINE __inline
#else
#define KR_INLINE inline
#endif

#if (KR_MSC_VER) && defined(_Check_return_)
#define KR_NODISCARD _Check_return_
#elif (KR_GNUC || KR_CLANG)
#define KR_NODISCARD __attribute__((__warn_unused_result__))
#else
#define KR_NODISCARD
#endif

#if (KR_CPLUSPLUS)
#define KR_NOEXCEPT noexcept
#else
#define KR_NOEXCEPT
#endif

#if (KR_MSC_VER)
#define KR_RESTRICT __restrict
#else
#define KR_RESTRICT __restrict__
#endif

#if (KR_MSC_VER)
#define KR_THREAD __declspec(thread)
#else
#define KR_THREAD __thread
#endif

#if (KR_MSC_VER)
#define KR_UNREACHABLE() (__assume(0))
#else
#define KR_UNREACHABLE() (__builtin_unreachable())
#endif
