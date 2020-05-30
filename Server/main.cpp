#include "config.hpp"
#include "command.hpp"

using namespace sf;
using namespace std;

bool running = true;

Global* Global::instance;

void event()
{
    RenderWindow wnd(VideoMode(200,200), "SPPMSG Server");
    while(running)
    {
        Event event;
        wnd.clear();
        while(wnd.pollEvent(event))
        {
            if(event.type == Event::Closed)
                running = false;
        }
        wnd.display();
    }
    wnd.close();
}

int main()
{
    Global global;
    Global::instance = &global;
    cout << "Starting SPPMsg Server..." << endl;
    Clock clock;

    // Initialize server
    global.server.setBlocking(false);
    global.selector.add(global.server);
    Socket::Status status;

    // Start listening
    status = global.server.listen(Socket::AnyPort);
    if(status != Socket::Done)
    {
        cout << "Error with listening: " << status << endl;
        return 1;
    }
    cout << "Started listening at " << global.server.getLocalPort() << endl;

    Thread eventThread(event);
    eventThread.launch();
    cout << "Loading took " << clock.restart().asSeconds() << " seconds" << endl;
    // Loop

    while(running)
    {
        TcpSocket* socket = new TcpSocket;
        Socket::Status status2 = global.server.accept(*socket);

        if(status2 == Socket::Done)
        {
            global.sockets.push_back(make_pair("User", socket));
            cout << "IP: " << socket->getRemoteAddress() << ":" << socket->getRemotePort() << " connected" << endl;
            global.selector.add(*socket);
        }
        else if(status2 == Socket::Disconnected)
        {
            disconnect(socket);
        }
        else
        {
            delete socket;
        }

        if(global.selector.wait(seconds(2)))
        {
            for(std::pair<string,TcpSocket*>& socket : global.sockets)
            {
                if(global.selector.isReady(*socket.second))
                {
                    Packet packet;
                    if(socket.second->receive(packet) == Socket::Done)
                    {
                        string str;
                        packet >> str;

                        if(str[0] == '/')
                        {
                            cout << "'" << socket.first << "' issued command: " << str << endl;
                            Command cmd = Command::parseCommand(str.substr(1));
                            command(cmd, socket.first);
                        }
                        else
                        {
                            cout << "'" << socket.first << "' sent: " << str << endl;
                            sendToAll("<"+socket.first+"> "+ str);
                        }
                    }
                    else
                    {
                        disconnect(socket.second);
                    }
                }
            }
        }
    }

    cout << "Server was running for " << clock.restart().asSeconds() << " seconds" << endl;
    global.selector.clear();
    eventThread.wait();
    Global::instance->server.close();
    cout << "Closing took " << clock.getElapsedTime().asSeconds() << " seconds" << endl;
    cout << "Press any key to continue . . ." << endl;
    getchar();

    return 0;
}
