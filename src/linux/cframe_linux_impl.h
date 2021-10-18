//
// Created by korona on 2021-10-13.
//

#pragma once
#include <sys/socket.h>

typedef unsigned char byte;

namespace CframeInternal
{
struct CFRAME_SOCKET {
    int Socket;
};

int read(const CFRAME_SOCKET* socket, byte* buf, int l);
}