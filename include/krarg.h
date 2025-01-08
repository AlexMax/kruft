/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(KRARG_H)
#define KRARG_H

#include "./krconfig.h"

#if (!KR_CONFIG_NOINCLUDE)
#include <stdarg.h>
#endif

#if !defined(va_copy)
#define va_copy(dest, src) ((dest) = (src))
#endif /* !defined(va_copy) */

#endif /* !defined(KRARG_H) */
