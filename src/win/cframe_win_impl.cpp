//
// Created by korona on 2021-10-13.
//

#include "cframe_win_impl.h"

namespace CframeInternal
{
    int read(const CFRAME_SOCKET* socket, byte* buf, int l) {
        return ::recv(socket->Socket, reinterpret_cast<char*>(buf), static_cast<int>(l), 0);
    }
}