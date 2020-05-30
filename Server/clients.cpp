#include "config.hpp"

TcpSocket* findUserSocket(string name)
{
    for(std::pair<string,TcpSocket*>& socket : Global::instance->sockets)
    {
        if(socket.first == name)
        {
            return socket.second;
        }
    }
    return NULL;
}

void disconnect(TcpSocket* sck)
{
    for(auto it = Global::instance->sockets.begin(); it != Global::instance->sockets.end(); it++)
    {
        if(it->second == sck)
        {
            Global::instance->sockets.erase(it);
            sendToAll(it->first + " disconnected");
            break;
        }
    }

    cout << "IP: " << sck->getRemoteAddress() << ":" << sck->getRemotePort() << " disconnected" << endl;
    Global::instance->selector.remove(*sck);
    delete sck;
}
