/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

/*
 * User configuration settings:
 *
 * KRUFT_CONFIG_USEIMPLEMENTATION:
 *	If defined, don't include function implementations unless you define
 *  KRUFT_IMPLEMENTATION before including.
 * KR_CONFIG_NOINCLUDE:
 *	If defined, does not include any libc header automatically.
 */

#if !defined(KRCONFIG_H)
#define KRCONFIG_H

/* Configuration options. */

#if !defined(KRUFT_CONFIG_USEIMPLEMENTATION)
#define KRUFT_CONFIG_USEIMPLEMENTATION (0)
#endif

#if !defined(KR_CONFIG_NOINCLUDE)
#define KR_CONFIG_NOINCLUDE (0)
#endif

#if !defined(KR_MALLOC)
#define KR_MALLOC(sz) (malloc((sz)))
#endif

#if !defined(KR_REALLOC)
#define KR_REALLOC(p, sz) (realloc((p), (sz)))
#endif

#if !defined(KR_FREE)
#define KR_FREE(p) (free((p)))
#endif

/* Compiler detection. */

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

/* C standard version. */

#if defined(__STDC_VERSION__)
#define KR_STDC_VERSION (__STDC_VERSION__)
#else
#define KR_STDC_VERSION (0)
#endif

/* C++ standard version. */

#if defined(__cplusplus) && defined(_MSVC_LANG)
#define KR_CPLUSPLUS (_MSVC_LANG)
#elif defined(__cplusplus)
#define KR_CPLUSPLUS (__cplusplus)
#else
#define KR_CPLUSPLUS (0)
#endif

/* Endian detection. */

#if (KR_GNUC || KR_CLANG)
#define KR_ORDER_LITTLE_ENDIAN (__ORDER_LITTLE_ENDIAN__)
#define KR_ORDER_BIG_ENDIAN (__ORDER_BIG_ENDIAN__)
#define KR_BYTE_ORDER (__BYTE_ORDER__)
#else /* (KR_GNUC || KR_CLANG) */
#define KR_ORDER_LITTLE_ENDIAN (1234)
#define KR_ORDER_BIG_ENDIAN (4321)
#if defined(__BIG_ENDIAN__)
#define KR_BYTE_ORDER (KR_ORDER_BIG_ENDIAN)
#else
#define KR_BYTE_ORDER (KR_ORDER_LITTLE_ENDIAN)
#endif /* defined(__BIG_ENDIAN__) */
#endif /* (KR_GNUC || KR_CLANG) */

/*
 * Size of pointer and size types.
 *
 * GCC and Clang have nice constants that tell us.  Modern MSVC only targets
 * a few specific platforms with fewer possibilities.
 *
 * On older and obscure platforms, int is a good guess - except when compiling
 * with certain memory models under DOS, which uses 32-bit sizes despite
 * int remaining 16-bit.
 *
 * TODO: Non-GNU/Clang/MSVC compilers targeting 64-bit.
 */

#if (KR_GNUC || KR_CLANG)
#define KR_SIZEOF_POINTER (__SIZEOF_POINTER__)
#define KR_SIZEOF_PTRDIFF_T (__SIZEOF_PTRDIFF_T__)
#define KR_SIZEOF_SIZE_T (__SIZEOF_SIZE_T__)
#elif (KR_MSC_VER) && defined(_WIN64)
#define KR_SIZEOF_POINTER (8)
#define KR_SIZEOF_PTRDIFF_T (8)
#define KR_SIZEOF_SIZE_T (8)
#elif (KR_MSC_VER) && defined(_WIN32)
#define KR_SIZEOF_POINTER (4)
#define KR_SIZEOF_PTRDIFF_T (4)
#define KR_SIZEOF_SIZE_T (4)
#elif defined(__LARGE__) || defined(__HUGE__) /* DOS memory models. */
#define KR_SIZEOF_POINTER (LONG_WIDTH / CHAR_BIT)
#define KR_SIZEOF_PTRDIFF_T (LONG_WIDTH / CHAR_BIT)
#define KR_SIZEOF_SIZE_T (LONG_WIDTH / CHAR_BIT)
#else /* A good guess on most obscure platforms. */
#define KR_SIZEOF_POINTER (INT_WIDTH / CHAR_BIT)
#define KR_SIZEOF_PTRDIFF_T (INT_WIDTH / CHAR_BIT)
#define KR_SIZEOF_SIZE_T (INT_WIDTH / CHAR_BIT)
#endif /* (KR_GNUC || KR_CLANG) */

/* Language and compiler feature shims. */

#if (KR_CPLUSPLUS >= 199711)
#define KR_CASTC(t, u) (const_cast<t>(u))
#else
#define KR_CASTC(t, u) (t)(u)
#endif

#if (KR_CPLUSPLUS >= 199711)
#define KR_CASTR(t, u) (reinterpret_cast<t>(u))
#else
#define KR_CASTR(t, u) (t)(u)
#endif

#if (KR_CPLUSPLUS >= 199711)
#define KR_CASTS(t, u) (static_cast<t>(u))
#else
#define KR_CASTS(t, u) (t)(u)
#endif

#if (KR_CPLUSPLUS >= 201402)
#define KR_CONSTEXPR constexpr
#else
#define KR_CONSTEXPR KR_INLINE
#endif

#if (KR_MSC_VER)
#define KR_FORCEINLINE __forceinline
#elif (KR_GNUC || KR_CLANG)
#define KR_FORCEINLINE KR_INLINE __attribute__((always_inline))
#else
#define KR_FORCEINLINE KR_INLINE
#endif

#if (KR_MSC_VER && KR_MSC_VER < 1900) /* Visual C++ 2015 */
#define KR_INLINE __inline
#elif (KR_CPLUSPLUS >= 199711) /* C++ inline. */
#define KR_INLINE inline
#elif (KR_STDC_VERSION >= 199901) /* C++-style inline in C99. */
#define KR_INLINE static inline
#else                     /* Last resort. */
#if (KR_GNUC || KR_CLANG) /* Try to avoid "unused definition." */
#define KR_INLINE __attribute__((unused)) static
#else /* (KR_GNUC || KR_CLANG) */
#define KR_INLINE static
#endif /* (KR_GNUC || KR_CLANG) */
#endif

#if (KR_MSC_VER) && defined(_Check_return_)
#define KR_NODISCARD _Check_return_
#elif (KR_GNUC || KR_CLANG)
#define KR_NODISCARD __attribute__((__warn_unused_result__))
#else
#define KR_NODISCARD
#endif

#if (KR_CPLUSPLUS >= 201103l)
#define KR_NOEXCEPT noexcept
#else
#define KR_NOEXCEPT
#endif

#if (KR_MSC_VER)
#define KR_RESTRICT __restrict
#elif (KR_GNUC || KR_CLANG)
#define KR_RESTRICT __restrict__
#else
#define KR_RESTRICT
#endif

#if (KR_MSC_VER)
#define KR_THREAD __declspec(thread)
#elif (KR_GNUC || KR_CLANG)
#define KR_THREAD __thread
#else
#define KR_THREAD
#endif

#if (KR_MSC_VER)
#define KR_UNREACHABLE() (__assume(0))
#elif (KR_GNUC || KR_CLANG)
#define KR_UNREACHABLE() (__builtin_unreachable())
#else
#define KR_UNREACHABLE()
#endif

#endif /* !defined(KRCONFIG_H) */
