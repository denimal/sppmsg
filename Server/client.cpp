#include <Server/client.hpp>
#include <Server/server.hpp>

Client::Client(sf::String name, Server* srv, sf::TcpSocket* socket)
    : userName(name)
    , server(srv)
    , clientSocket(socket)
    , error(false){}

Client::~Client() {}

bool Client::send(sf::String data)
{
    sf::Packet packet;
    packet << data;
    sf::Socket::Status status = clientSocket->send(packet);
    return status == sf::Socket::Done;
}
sf::TcpSocket* Client::getSocket()
{
    return clientSocket;
}
sf::String Client::getName()
{
    return userName;
}
void Client::setName(sf::String name)
{
    userName = name;
}
