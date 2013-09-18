
#ifndef NET__SOCKET_H_INCLUDED
#define NET__SOCKET_H_INCLUDED

#include <SDL2/SDL_net.h>

#include "excp/NetException.h"
#include "ilog/Logger.h"

using namespace std;
using namespace game::excp;

namespace game { namespace net {

    class Socket {
    public:
        Socket(TCPsocket socket) : socket(socket) { }
        Socket(const string& host, uint16_t port);
        Socket(IPaddress address);
        ~Socket();

        int Send(const void * data, int len);
        int Recv(void * data, int size);
        void Close();

    private:
        void Initialize(IPaddress address);

    protected:
        TCPsocket socket;
    };
}}

#endif // NET__SOCKET_H_INCLUDED
