#include "config.hpp"
#include "command.hpp"

Command Command::parseCommand(string cmds)
{
    Command cmd;
    int lsepp = 0;
    int sepp = 0;

    for(int i = 0; i < cmds.size()+1; i++)
    {
        if(cmds[i] == ' ' || cmds[i] == '\0')
        {
            sepp = i;
            if(lsepp == 0)
                cmd.cmd = cmds.substr(lsepp, sepp-lsepp);
            else
                cmd.args.push_back(cmds.substr(lsepp, sepp-lsepp));

            lsepp = i+1;
        }
    }
    return cmd;
}

void command(Command& cmd, string senderUsername)
{
    if(cmd.cmd == "username")
    {
        if(cmd.args.size() != 1)
            sendToUser("Usage: /username <name>", senderUsername);
        else
        {
            string str = senderUsername;

            for(std::pair<string,TcpSocket*>& socket : Global::instance->sockets)
            {
                if(socket.first == senderUsername)
                {
                    socket.first = cmd.args[0];

                    if(senderUsername != "User")
                        sendToAll("'" + str + "' changed username to '" + socket.first + "'");
                    else
                        sendToAll("'" + socket.first + "' connected");

                    break;
                }
            }
        }
    }
    else if(cmd.cmd == "msg")
    {
        if(cmd.args.size() < 2)
		{
            sendToUser("Usage: /msg <username> <text>", senderUsername);
			return;
		}

        string str2;
        for(int i = 1; i < cmd.args.size(); i++)
        {
            str2 += (cmd.args[i] + " ");
        }
        if(!sendToUser("["+senderUsername+"] "+str2, cmd.args[0]))
            sendToUser("Username not found: '" + cmd.args[0] + "'", senderUsername);

        sendToUser("["+senderUsername+"] "+str2, senderUsername);
    }
    else if(cmd.cmd == "list")
    {
        if(cmd.args.size() != 0)
        {
            sendToUser("Usage: /list", senderUsername);
        }
        else
        {
            string playersstr;
            sendToUser("In this server currently are: ", senderUsername);
            int i = 0;

            for(pair<string,TcpSocket*>& socket: Global::instance->sockets)
            {
                playersstr += socket.first;
                if(i != Global::instance->sockets.size() - 1)
                    playersstr += ", ";
                i++;
            }
            sendToUser(playersstr + ".", senderUsername);
        }
    }
    else if(cmd.cmd == "help")
    {
        sendToUser("Commands: /help, /msg, /username, /list", senderUsername);
    }
    else
    {
        sendToUser("Unknown Command! Type /help to get list of commands.", senderUsername);
    }
}
