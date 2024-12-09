//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include "./krdef.h"

#if (!KR_CPLUSPLUS)
#if (KR_STDC_VERSION >= 199901)

#include <stdbool.h>

#else

#define bool int
#define true (1)
#define false (0)

#endif // (KR_STDC_VERSION >= 199901)
#endif // (!KR_CPLUSPLUS)
