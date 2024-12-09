//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include "./krdef.h"
#include "./krbool.h"

#if (!KR_CONFIG_NOINCLUDE)
#include <stddef.h>
#include <stdlib.h>
#endif

KR_NODISCARD inline void *kr_reallocarray(void *ptr, size_t nmemb, size_t size)
{
    const size_t x = nmemb * size;
    if (nmemb != 0 && x / nmemb != size)
    {
        return KR_NULL;
    }
    return realloc(ptr, nmemb * size);
}
