#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <Server/client.hpp>
#include <Utility/command.hpp>
#include <SFML/Network.hpp>

class Server
{
    std::map<int, Client*> clients;
    sf::SocketSelector selector;
    sf::TcpListener listener;
    int uniqueId;
public:
    bool error;

    Server();
    ~Server();
    void sendToAll(sf::String data, Client* client = NULL);
    void sendTo(Client* client, sf::String data, bool kickOnError = true);
    Client* getClientById(int id);
    Client* getClientByName(sf::String name);
    int getIdOfClient(Client* client); //0=no client found
    void kickClient(Client* client, sf::String reason = "Disconnected");
    int addClient(Client* client);
    void command(Client* client, Command& command);
    void select();
};

#endif // SERVER_HPP
