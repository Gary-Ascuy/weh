
#ifndef NET__TCPSERVER_H_INCLUDED
#define NET__TCPSERVER_H_INCLUDED

#include <SDL2/SDL_net.h>

#include "excp/NetException.h"
#include "ilog/Logger.h"

using namespace std;
using namespace game::excp;

namespace game { namespace net {

    class TCPServer {
    public:
        TCPServer(uint16_t port);
        ~TCPServer();

        TCPsocket Accept();
        void Close();

    protected:
        IPaddress address;
        TCPsocket server;
    };

}}

#endif // NET__TCPSERVER_H_INCLUDED
