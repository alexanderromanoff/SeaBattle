#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>
#include <algorithm>
#include "../CommandArgs.h"
#include "../../Players/Player.h"

class GameController;


class InputHandler // used by mediator
{
private:
    std::map<std::string, CommandArgs::CommandType> inputMap   {{"ATK", CommandArgs::CommandType::ATTACK},
                                                                {"PLACE", CommandArgs::CommandType::PLACE},
                                                                {"ABL", CommandArgs::CommandType::ABILITY},
                                                                {"SAVE", CommandArgs::CommandType::SAVE},
                                                                {"LOAD", CommandArgs::CommandType::LOAD},
                                                                {"NEW_GAME", CommandArgs::CommandType::NEW_GAME},
                                                                {"QUIT", CommandArgs::CommandType::QUIT},
                                                                {"INFO", CommandArgs::CommandType::INFO}};

    CommandArgs* currentComArgs = nullptr;

    GameController& mController;
public:
    InputHandler(GameController& controller);
    void newArgs();
    bool handleFieldSize(Player* player, std::pair<int, int> sizes);
    bool handleShipsMap(Player* player, std::map<int, int> shipsMap);
    bool handleCoordinates(Player* player, std::pair<int, int> coords);
    CommandArgs::CommandType handleCommandName(Player* player, std::string commandStr);
    bool handleGameStart(Player* player, std::string startCommandStr);
    bool handleOrientation(Player* player, Battleship::Orientation orientation);
    bool handleIndex(Player* player,  int index);
    void runContr();
    // orientation input validity is checked on the spot

};

#endif