//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include "./krconfig.h"

#if (!KR_CPLUSPLUS)
#if (KR_STDC_VERSION >= 199901)

#if (!KR_CONFIG_NOINCLUDE)
#include <stdbool.h>
#endif

#else

#define bool int
#define true (1)
#define false (0)

#endif // (KR_STDC_VERSION >= 199901)
#endif // (!KR_CPLUSPLUS)
