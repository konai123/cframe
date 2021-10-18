//
// Created by korona on 2021-10-13.
//

#include "cframe.h"
#include <iostream>

#pragma comment(lib, "ws2_32.lib")
using namespace Cframe;

/*
 * Only tested on MSVC
 * */
SOCKET createServer()
{
    WORD		wVersionRequested;
    WSADATA		wsaData;
    SOCKADDR_IN servAddr, cliAddr; //Socket address information
    int			err;
    int			bytesSent;
    char        buf[50];

    wVersionRequested = MAKEWORD(1, 1);
    err = WSAStartup(wVersionRequested, &wsaData);

    if (err != 0) {
        WSACleanup();
        return false;
    }

    servAddr.sin_family = AF_INET; // address family Internet
    servAddr.sin_port = htons(10050); //Port to connect on
    servAddr.sin_addr.s_addr = inet_addr("0.0.0.0"); //Target IP

    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    if (s == INVALID_SOCKET)
    {
        WSACleanup();
        return false; //Couldn't create the socket
    }

    int x = bind(s, reinterpret_cast<SOCKADDR *>(&servAddr), sizeof(servAddr));
    if (x == SOCKET_ERROR)
    {
        WSACleanup();
        return false; //Couldn't connect
    }

    listen(s, 5);
    int xx = sizeof(cliAddr);
    SOCKET s2 = accept(s, reinterpret_cast<SOCKADDR *>(&cliAddr), &xx);
    return s2;
}

[[noreturn]]
int main(int argc, char** argv)
{
    Cframe::CFRAME_DECODER_INFO decoder;
    decoder.LengthFieldOffset = 4;
    decoder.LengthFieldBias = 1;
    decoder.LengthFieldLength = 4;

    Cframe::Initialize(decoder);

    auto socket = createServer();
    CFrameSocket csocket;
    csocket.Socket = socket;

    std::vector<byte> frame;
    while (1) {
        int ret = Cframe::ReadFrame(&csocket, frame);
        if (ret <= 0) break;

        std::cout << "ReadSize: " << ret << std::endl;
        for (int i = 0; i < ret; ++i) {
            std::cout << frame[i] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}