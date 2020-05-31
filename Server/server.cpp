#include <Server/server.hpp>

Server::Server()
    : uniqueId(0)
    , error(false)
{
    sf::Socket::Status status;
    status = listener.listen(50291);
    selector.add(listener);
    if(status != Socket::Done)
    {
        cout << "Error listening: " << status << endl;
        error = true;
        return;
    }
    cout << "Started listening at " << listener.getLocalPort() << endl;
}

Server::~Server()
{
    selector.clear();
}

void Server::sendToAll(sf::String data, Client* sender)
{
    for(auto& pr: clients)
    {
        if(pr.second != sender)
            pr.second->send(data);
    }
}
void Server::sendTo(Client* client, sf::String data, bool kickOnError)
{
    bool b = client->send(data);
    if(!b && kickOnError)
        kickClient(client);
}
Client* Server::getClientById(int id)
{
    auto it = clients.find(id);
    if(it == clients.end())
        return NULL;
    return it->second;
}
Client* Server::getClientByName(sf::String name)
{
    for(auto& pr: clients)
    {
        if(pr.second->getName() == name)
            return pr.second;
    }
    return NULL;
}
int Server::getIdOfClient(Client* client)
{
    for(auto& pr: clients)
    {
        if(pr.second == client)
            return pr.first;
    }
    return 0;
}
void Server::kickClient(Client* client, sf::String reason)
{
    auto _client = clients.find(getIdOfClient(client));
    selector.remove(*client->getSocket());
    sendTo(client, reason, false);
    cout << "IP: " << client->getSocket()->getRemoteAddress() << ":" << client->getSocket()->getRemotePort() << " disconnected" << endl;
    client->getSocket()->disconnect();
    clients.erase(_client);
    sendToAll(client->getName() + " disconnected", NULL);
    delete client;
}
int Server::addClient(Client* client)
{
    cout << "Adding client " << client->getName().toAnsiString() << " as id " << (++uniqueId) << endl;
    clients[uniqueId] = client;
    selector.add(*client->getSocket());
}
void Server::command(Client* client, Command& command)
{
    if(command.cmd == "username")
    {
        if(command.args.size() != 1)
            client->send("Usage: /username <name>");
        else
        {
            sf::String str = client->getName();
            client->setName(command.args[0]);

            if(client->getName() != "User")
                sendToAll("'" + str + "' changed username to '" + client->getName() + "'", NULL);
            else
                sendToAll("'" + client->getName() + "' connected", NULL);
        }
    }
    else if(command.cmd == "msg")
    {
        if(command.args.size() < 2)
		{
            client->send("Usage: /msg <username> <text...>");
			return;
		}

        sf::String str2;
        for(int i = 1; i < command.args.size(); i++)
        {
            str2 += (command.args[i] + " ");
        }
        Client* client2 = getClientByName(command.args[0]);
        if(!client2)
            client->send("Username not found: '" + command.args[0] + "'");
        else
            sendTo(client2, "["+client->getName()+"] "+str2);

        if(client2 != client)
            client->send("["+client->getName()+"] "+str2);
    }
    else if(command.cmd == "list")
    {
        if(command.args.size() != 0)
        {
            client->send("Usage: /list");
        }
        else
        {
            sf::String playersstr;
            client->send("In this server currently are: ");
            int i = 0;

            for(auto& pr: clients)
            {
                playersstr += pr.second->getName();
                if(i != clients.size() - 1)
                    playersstr += ", ";
                i++;
            }
            client->send(playersstr + ".");
        }
    }
    else if(command.cmd == "help")
    {
        client->send("Commands: /help, /msg, /username, /list");
    }
    else
    {
        client->send("Unknown Command! Type /help to get list of commands.");
    }
}
void Server::select()
{
    if(selector.wait(seconds(2)))
    {
        if(selector.isReady(listener))
        {
            TcpSocket* socket = new TcpSocket;
            Socket::Status status2 = listener.accept(*socket);

            if(status2 == Socket::Done)
            {
                Client* client = new Client("User", this, socket);
                if(client)
                    addClient(client);
                cout << "IP: " << socket->getRemoteAddress() << ":" << socket->getRemotePort() << " connected" << endl;
            }
            else
            {
                delete socket;
            }
        }
        if(!clients.empty())
        {
            for(auto& pr : clients)
            {
                sf::TcpSocket* sck = pr.second->getSocket();
                if(selector.isReady(*sck))
                {
                    Packet packet;
                    if(sck->receive(packet) == Socket::Done)
                    {
                        sf::String str;
                        packet >> str;

                        if(str.empty())
                            continue;

                        if(str[0] == '/')
                        {
                            cout << "'" << pr.second->getName().toAnsiString() << "' issued command: " << str.toAnsiString() << endl;
                            Command cmd = Command::parseCommand(str.substring(1));
                            command(pr.second, cmd);
                        }
                        else
                        {
                            cout << "'" << pr.second->getName().toAnsiString() << "' sent: " << str.toAnsiString() << endl;
                            sendToAll("<"+pr.second->getName()+"> "+ str);
                        }
                    }
                    else
                    {
                        kickClient(pr.second);
                    }
                }
            }
        }
    }
}
