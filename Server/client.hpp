#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>

#include <string>

class Server;

class Client
{
    sf::String userName;
    Server* server;
    sf::TcpSocket* clientSocket;
public:
    bool error;

    Client(sf::String name, Server* srv, sf::TcpSocket* socket);
    ~Client();
    bool send(sf::String data);
    sf::TcpSocket* getSocket();
    sf::String getName();
    void setName(sf::String);
};

#endif // CLIENT_HPP

