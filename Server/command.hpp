#pragma once

#include "config.hpp"

class Command
{
public:
    sf::String cmd;
    vector<sf::String> args;

    static Command parseCommand(sf::String cmds);
};
