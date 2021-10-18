//
// Created by korona on 2021-10-13.
//

#pragma once
#include <WinSock2.h>

typedef unsigned char byte;

namespace CframeInternal
{
    struct CFRAME_SOCKET {
        SOCKET Socket;
    };

    int read(const CFRAME_SOCKET* socket, byte* buf, int l);
}