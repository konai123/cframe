//
// Created by korona on 2021-10-13.
//

#pragma once

/*
 * macros
 * */

#include <cassert>

#if defined(DEBUG) || defined(_DEBUG)
#define CFRAME_ASSERT(x) {  \
    assert()                \
}                           \
                            \
#else

#define CFRAME_ASSERT(x) { \
    abort()                \
}
#endif

namespace cframe {

}