#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>
#include <algorithm>
#include <fstream>
#include "../CommandArgs.h"
#include "../../Players/Player.h"

class GameController;


class InputHandler // used by mediator
{
private:
    std::vector<std::string> defaultInputs {"ATK", 
                                            "PLACE", 
                                            "ABL", 
                                            "SAVE", 
                                            "LOAD", 
                                            "NEW_GAME", 
                                            "QUIT", 
                                            "INFO"};

    std::vector<CommandArgs::CommandType> availableCommands {CommandArgs::CommandType::ATTACK,
                                                             CommandArgs::CommandType::PLACE,
                                                             CommandArgs::CommandType::ABILITY,
                                                             CommandArgs::CommandType::SAVE,
                                                             CommandArgs::CommandType::LOAD,
                                                             CommandArgs::CommandType::NEW_GAME,
                                                             CommandArgs::CommandType::QUIT,
                                                             CommandArgs::CommandType::INFO};

    // std::map<std::string, CommandArgs::CommandType> defaultInputMap     {{"ATK", CommandArgs::CommandType::ATTACK},
    //                                                                     {"PLACE", CommandArgs::CommandType::PLACE},
    //                                                                     {"ABL", CommandArgs::CommandType::ABILITY},
    //                                                                     {"SAVE", CommandArgs::CommandType::SAVE},
    //                                                                     {"LOAD", CommandArgs::CommandType::LOAD},
    //                                                                     {"NEW_GAME", CommandArgs::CommandType::NEW_GAME},
    //                                                                     {"QUIT", CommandArgs::CommandType::QUIT},
    //                                                                     {"INFO", CommandArgs::CommandType::INFO}};

    std::map<std::string, CommandArgs::CommandType> inputMap;


    const std::string inpMapPath = "/home/alex/sea_battle/src/inpMap.txt";

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
    void setCommandExplicitly(CommandArgs::CommandType commandType);
    void runContr();
    std::map<std::string, CommandArgs::CommandType> readInputMap();
    // orientation input validity is checked on the spot

};

#endif