//
// Created by korona on 2021-10-13.
//

#pragma once

/*
 * macros
 * */
#include <cassert>
#include <vector>

#ifdef _WIN32
#include "win/cframe_win_impl.h"
#elif  __linux__
#include "linux/cframe_linux_impl.h"
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define CFRAME_ASSERT(x) {                                          \
    assert(x);                                                      \
}                                                                   \

#else

#define CFRAME_ASSERT(x) {                                      \
}

#define CFRAME_STATIC_ASSERT(x) {                               \
}

#endif

#define CFRAME_SOCKET_DISCONNECTED  0

/*
 * types
 * */
namespace {
    constexpr int CframeMaxLengthFieldSize = 4;
}

typedef int CframeSizeT;
static_assert(sizeof(CframeSizeT) >= CframeMaxLengthFieldSize);

namespace Cframe {
    struct CFRAME_DECODER_INFO {
        CframeSizeT LengthFieldOffset;
        CframeSizeT LengthFieldLength;
        CframeSizeT LengthFieldBias;
    };

    struct CFRAME_IO {
        CFRAME_DECODER_INFO DecoderInfo;
        CframeSizeT ReadSize;
        std::vector<byte> Buffer;
    };
}

/*
 * functions
 * */
namespace Cframe {
    using CFrameSocket = CframeInternal::CFRAME_SOCKET;
    bool Initialize(const CFRAME_DECODER_INFO& decoderInfo);
    CframeSizeT ReadFrame(const CFrameSocket *socket, std::vector<byte>& out);
}

namespace Cframe {
    extern CFRAME_IO IO;
}