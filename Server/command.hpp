#pragma once

#include "config.hpp"

class Command
{
public:
    string cmd;
    vector<string> args;

    static Command parseCommand(string cmds);
};

void command(Command&, string);
