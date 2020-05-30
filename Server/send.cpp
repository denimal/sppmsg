#include "config.hpp"

void sendToAll(string str, TcpSocket* sender, bool skipSender)
{
    for(std::pair<string,TcpSocket*>& socket2 : Global::instance->sockets)
    {
        Packet packet2;
        packet2 << str;
        if(!(socket2.second == sender && skipSender))
            if(socket2.second->send(packet2) != Socket::Done)
            {
                disconnect(socket2.second);
            }
    }
}

bool sendToUser(string tx, string user)
{
    Packet packet2;
    packet2 << tx;

    TcpSocket * sck = findUserSocket(user);
    if(sck != NULL)
        sck->send(packet2);
    else
        return false;
    return true;
}
