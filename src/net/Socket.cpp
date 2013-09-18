
#include "net/Socket.h"

using namespace game::net;

Socket::Socket(const string& host, uint16_t port) : socket(NULL) {
    IPaddress address;
    int err = SDLNet_ResolveHost(&address, host.c_str(), port);
    if (err < 0) throw NetException(SDLNet_GetError());
    Initialize(address);
}

Socket::Socket(IPaddress address) : socket(NULL) {
    Initialize(address);
}

Socket::~Socket() {
    Close();
}

int Socket::Send(const void * data, int size) {
    int length = SDLNet_TCP_Send(socket, data, size);
    if (length < size) throw NetException(SDLNet_GetError());
    return length;
}

int Socket::Recv(void * data, int size) {
    int length = SDLNet_TCP_Recv(socket, data, size);
    if (length <= 0) throw NetException(SDLNet_GetError());
    return length;
}

void Socket::Close() {
    if (!socket) SDLNet_TCP_Close(socket);
}

void Socket::Initialize(IPaddress address) {
    socket = SDLNet_TCP_Open(&address);
    if (!socket) throw NetException(SDLNet_GetError());
}
