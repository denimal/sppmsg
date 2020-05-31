#include "config.hpp"
#include <Utility/command.hpp>

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
    global.server = new Server();

    if(global.server->error)
    {
        cout << "An error occured starting server." << endl;
        return 1;
    }

    Thread eventThread(event);
    eventThread.launch();
    cout << "Loading took " << clock.restart().asSeconds() << " seconds" << endl;

    // Loop
    while(running)
    {
       global.server->select();
    }

    cout << "Server was running for " << clock.restart().asSeconds() << " seconds" << endl;
    eventThread.wait();
    cout << "Closing took " << clock.getElapsedTime().asSeconds() << " seconds" << endl;
    cout << "Press ENTER to continue . . ." << endl;
    getchar();

    delete global.server;

    return 0;
}
