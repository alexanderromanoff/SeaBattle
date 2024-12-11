#ifndef COMMAND_ARGS_H
#define COMMAND_ARGS_H

#include<string>
#include "../Battleship.h"

struct CommandArgs
{
    enum CommandType {ATTACK, ABILITY, PLACE, NEW_GAME, LOAD, SAVE, QUIT, INFO, NONE};
    CommandType commandName;
    std::pair<int, int> coordinates {-1, -1};
    int index = -1;
    Battleship::Orientation orientation;
};


#endif

