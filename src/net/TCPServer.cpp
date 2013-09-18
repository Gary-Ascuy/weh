
#include "net/TCPServer.h"

using namespace game::net;

TCPServer::TCPServer(uint16_t port) {
    int err = SDLNet_ResolveHost(&address, NULL, port);
    if (err < 0) throw NetException(SDLNet_GetError());

    server = SDLNet_TCP_Open(&address);
    if (!server) throw NetException(SDLNet_GetError());

    iLogger(iINFO << iTAGS({"server", "listening"}) << SDLNet_ResolveIP(&address) << ":" << SDLNet_Read16(&address.port));
}

TCPServer::~TCPServer() {
    Close();
}

TCPsocket TCPServer::Accept() {
    TCPsocket client = NULL;
    do {
        client = SDLNet_TCP_Accept(server);
    } while (!client);

    IPaddress * remoteIP = SDLNet_TCP_GetPeerAddress(client);
    iLogger(iINFO << iTAGS({"server", "acept"}) << SDLNet_ResolveIP(remoteIP) << ":" << SDLNet_Read16(&remoteIP -> port));
    return client;
}

void TCPServer::Close() {
    if (!server) SDLNet_TCP_Close(server);
}
