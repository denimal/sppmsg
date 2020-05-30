#include "config.hpp"

using namespace sf;
using namespace std;

bool appRunning = true;
bool running = true;
sf::String logstr;
sf::String chatString;
TcpSocket sck;
vector<sf::String> issuedCommands;
int cmdIndex = -1;
sf::Mutex mutex;
View wndView(FloatRect(0.f, 0.f, 500.f, 500.f));
RenderWindow wnd;
int caretPos = 0;

void send()
{
    sf::Lock lock(mutex);
    if(chatString == "\\\\")
    {
        running = false;
        sck.disconnect();
    }
    else
    {
        Packet packet;
        packet << chatString;
        Socket::Status status1 = sck.send(packet);
        if(status1 == Socket::Disconnected)
            logstr += "Server closed!\n";
        else if(status1 == Socket::Error)
            logstr += "Unexpected error while sending data!\n";
    }
}

void network()
{
    while(running)
    {
        Packet packet2;

        if(sck.receive(packet2) == Socket::Done)
        {
            sf::Lock lock(mutex);
            sf::String text;
            if(packet2 >> text)
            {
                logstr += (text + "\n");
                wndView = View(FloatRect(0.f, 0.f, wnd.getSize().x, wnd.getSize().y));
            }
        }
        else
        {
            running = false;
            sck.disconnect();
        }
    }
}

void loop()
{
    wnd.create(VideoMode(500, 500), "SPPMsg Client");
    wnd.setFramerateLimit(60);
    Font font;
    font.loadFromFile("font.ttf");
    wnd.setView(wndView);
    wnd.setKeyRepeatEnabled(true);
    View guiView(FloatRect(0.f, 0.f, 500.f, 500.f));

    while(running && wnd.isOpen())
    {
        Event e;
        while(wnd.pollEvent(e))
        {
            if(e.type == Event::Closed)
                running = false;
            if(e.type == Event::Resized)
            {
                wndView.reset(FloatRect(0.f, 0.f, e.size.width, e.size.height));
                guiView.reset(FloatRect(0.f, 0.f, e.size.width, e.size.height));
            }

            if(e.type == Event::KeyPressed && e.key.code == Keyboard::Return)
            {
                send();
                issuedCommands.push_back(chatString);
                chatString = "";
                caretPos = 0;
            }
            else if(e.type == Event::TextEntered)
            {
                if(e.text.unicode == 8)
                {
                    if(caretPos > 0)
                    {
                        chatString.erase(caretPos - 1);
                        caretPos--;
                    }
                }
                else if(e.text.unicode > 0x1F)
                {
                    chatString.insert(caretPos, e.text.unicode);
                    caretPos += 1;
                }

                cmdIndex = -1;
            }
            if(e.type == Event::KeyPressed)
            {
                if(e.key.code == Keyboard::Up)
                {
                    if(!issuedCommands.empty())
                    {
                        if(cmdIndex == -1)
                        {
                            cmdIndex = issuedCommands.size()-1;
                            chatString = issuedCommands[cmdIndex];
                            caretPos = chatString.getSize();
                        }
                        else
                        {
                            if(cmdIndex != 0)
                                cmdIndex--;

                            chatString = issuedCommands[cmdIndex];
                            caretPos = chatString.getSize();
                        }
                    }
                }
                else if(e.key.code == Keyboard::Down)
                {
                    if(!issuedCommands.empty())
                    {
                        if(cmdIndex < issuedCommands.size()-1)
                        {
                            cmdIndex++;
                            chatString = issuedCommands[cmdIndex];
                            caretPos = chatString.getSize();
                        }
                        else
                        {
                            cmdIndex = -1;
                            chatString = "";
                            caretPos = 0;
                        }
                    }
                }
                else if(e.key.code == Keyboard::Left)
                {
                    if(caretPos > 0)
                        caretPos--;
                }
                else if(e.key.code == Keyboard::Right)
                {
                    if(caretPos <= chatString.getSize())
                        caretPos++;
                }
            }
        }

        {
            sf::Lock lock(mutex);
            wnd.clear(Color::White);
            wnd.setView(wndView);
            Text tx(logstr, font, 16);
            tx.setPosition(2, wnd.getView().getSize().y-tx.getLocalBounds().height-50.f);
            tx.setFillColor(Color::Black);
            wnd.draw(tx);
        }

        wnd.setView(guiView);
        RectangleShape rs(Vector2f(wnd.getView().getSize().x, 50.f));
        rs.setPosition(0.f, wnd.getView().getSize().y-50.f);
        rs.setFillColor(Color(200,200,200));
        wnd.draw(rs);

        Text tx2(chatString, font, 20);
        tx2.setPosition(5, wnd.getView().getSize().y-50.f);
        tx2.setFillColor(Color::Black);
        tx2.setStyle(Text::Underlined);
        wnd.draw(tx2);

        RectangleShape rs2(Vector2f(3.f, 25.f));
        rs2.setPosition(tx2.findCharacterPos(caretPos));
        rs2.setFillColor(time(NULL) % 2 == 0 ? Color::Transparent : Color::Black);
        wnd.draw(rs2);

        wnd.display();
    }
}

int main(int argc, char* argv[])
{
    cout << "Starting SPPMsg Client..." << endl;

    while(appRunning)
    {
        int port;
        do
        {
            cin.clear();
            cout << "Select port to connect (0 to exit app):" << endl;
            cin >> port;
            cin.ignore(100,'\n');
        } while(cin.fail());

        if(port == 0)
        {
            appRunning = false;
            break;
        }

        cout << "Select Username: " << endl;
        string username;
        cin >> username;

        cout << "Select Server IP: " << endl;
        string ip;
        cin >> ip;

        bool attemptConnect = true;
        bool skipConnect = false;

        do
        {
            Socket::Status status;
            if(!skipConnect)
                status = sck.connect(ip, port);

            if(status != Socket::Done)
            {
                cout << "Error: " << ((status==Socket::Disconnected ? "Disconnected" :
                (status==Socket::Error ? ("Error" + to_string(errno)) : ("Unexpected error: "
                + to_string(status))))) << ". Do you want to try again? (Y/N)" << endl;

                string str;
                cin >> str;

                if(str == "Y")
                {
                    skipConnect = false;
                    continue;
                }
                else if(str == "N")
                {
                    attemptConnect = false;
                    running = false;
                }
                else
                {
                    cout << "Invalid String!" << endl;
                    skipConnect = true;
                }
            }
            else
                attemptConnect = false;
        } while(attemptConnect);

        Packet packet1;
        packet1 << ("/username " + username);
        sck.send(packet1);

        Thread guiThread(loop);
        guiThread.launch();
        Thread networkThread(network);
        networkThread.launch();

        guiThread.wait();
    }

    return 0;
}
