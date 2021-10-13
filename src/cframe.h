//
// Created by korona on 2021-10-13.
//

#pragma once

/*
 * macros
 * */
#include <cassert>

#ifdef _WIN32
#include "win/cframe_win_impl.h"
#elif  __linux__
//TODO
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define CFRAME_ASSERT(x) {                                      \
    assert(x)                                                   \
}                                                               \

#define CFRAME_STATIC_ASSERT(x) {                               \
    static_assert(x)                                            \
}                                                               \

#else

#define CFRAME_ASSERT(x) {                                      \
}

#define CFRAME_STATIC_ASSERT(x) {                               \
}

#endif

/*
 * types
 * */
constexpr int CframeMaxLengthFieldSize = 4;
typedef int CframeSizeT;
typedef unsigned char byte;
static_assert(sizeof(CframeSizeT) <= CframeMaxLengthFieldSize);

namespace Cframe {
    struct CFRAME_DECODER_INFO {
        CframeSizeT LengthFieldOffset;
        CframeSizeT LengthFieldLength;
        CframeSizeT LengthFieldBias;
    };

    struct CFRAME_IO {
        CFRAME_DECODER_INFO DecoderInfo;
    };

}

/*
 * functions
 * */
namespace Cframe {
    constexpr bool Initialize(const CFRAME_DECODER_INFO decoderInfo);
    byte* ReadFrame(const CframeInternal::CFRAME_SOCKET* socket);
}

namespace Cframe {
    CFRAME_IO IO;
}