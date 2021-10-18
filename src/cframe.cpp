//
// Created by korona on 2021-10-13.
//

#include "cframe.h"
#include <cstring>

Cframe::CFRAME_IO Cframe::IO;

bool Cframe::Initialize(const CFRAME_DECODER_INFO& decoderInfo) {
    Cframe::IO.DecoderInfo = decoderInfo;
    Cframe::IO.ReadSize = 0;
    Cframe::IO.Buffer.resize(0);
    Cframe::IO.Buffer.reserve(1024*2);

    return true;
}

CframeSizeT Cframe::ReadFrame(const CframeInternal::CFRAME_SOCKET *socket, std::vector<byte>& outBuffer) {
    const auto& info = Cframe::IO.DecoderInfo;
    CframeSizeT waitSize = info.LengthFieldOffset + info.LengthFieldLength;
    if (Cframe::IO.Buffer.size() < waitSize)
        Cframe::IO.Buffer.resize(waitSize);

    while (Cframe::IO.ReadSize < waitSize) {
        int ret = read(socket, Cframe::IO.Buffer.data() + Cframe::IO.ReadSize, waitSize - Cframe::IO.ReadSize);
        if (ret <= CFRAME_SOCKET_DISCONNECTED) {
            return ret;
        }
        Cframe::IO.ReadSize += ret;
    }

    byte* cursor = Cframe::IO.Buffer.data() + Cframe::IO.DecoderInfo.LengthFieldOffset;
    CframeSizeT leftedSize;
    ::memcpy(&leftedSize, cursor, Cframe::IO.DecoderInfo.LengthFieldLength);
    CFRAME_ASSERT(leftedSize >= 0);
    leftedSize += Cframe::IO.DecoderInfo.LengthFieldBias;
    Cframe::IO.Buffer.resize(waitSize + leftedSize);

    while (Cframe::IO.ReadSize - waitSize < leftedSize) {
        int ret = read(socket, Cframe::IO.Buffer.data() + Cframe::IO.ReadSize, leftedSize - (Cframe::IO.ReadSize - waitSize));
        if (ret <= CFRAME_SOCKET_DISCONNECTED) {
            return ret;
        }
        Cframe::IO.ReadSize += ret;
    }

    outBuffer = Cframe::IO.Buffer;
    auto ret = Cframe::IO.ReadSize;
    Cframe::Initialize(Cframe::IO.DecoderInfo);

    return ret;
}