#include "config.hpp"
#include "command.hpp"

Command Command::parseCommand(sf::String cmds)
{
    Command cmd;
    int lsepp = 0;
    int sepp = 0;

    for(int i = 0; i < cmds.getSize() + 1; i++)
    {
        if(cmds[i] == ' ' || cmds[i] == '\0')
        {
            sepp = i;
            if(lsepp == 0)
                cmd.cmd = cmds.substring(lsepp, sepp-lsepp);
            else
                cmd.args.push_back(cmds.substring(lsepp, sepp-lsepp));

            lsepp = i+1;
        }
    }
    return cmd;
}
