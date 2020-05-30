#ifndef CONFIG_HPP_INCL
#define CONFIG_HPP_INCL

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

TcpSocket* findUserSocket(string);
void disconnect(TcpSocket*);
void sendToAll(string str, TcpSocket* sender = NULL, bool skipSender = false);
bool sendToUser(string, string);

class Global
{
public:
    static Global* instance;

    vector<pair<string,TcpSocket*>> sockets;
    SocketSelector selector;
    TcpListener server;
};


#endif // CONFIG_HPP_INCL


