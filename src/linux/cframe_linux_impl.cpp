//
// Created by korona on 2021-10-18.
//

#include "cframe_linux_impl.h"

namespace CframeInternal
{
int read(const CFRAME_SOCKET* socket, byte* buf, int l) {
    return ::recv(socket->Socket, reinterpret_cast<char*>(buf), static_cast<int>(l), 0);
}
}