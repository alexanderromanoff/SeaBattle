#ifndef COMMAND_ARGS_H
#define COMMAND_ARGS_H

#include<string>

struct CommandArgs
{
    std::string commandName = "None";
    int x = -1;
    int y = -1;
};

#endif