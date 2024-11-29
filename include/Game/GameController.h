#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H


#include "CommandArgs.h"
#include "Game.h"
#include <fstream>
#include <string>
#include <regex>

class GameController
{
private:
    std::string destFile = "/home/alex/sea_battle/src/save.txt";
    Game& mGame;
    IOInterface& mInput;
    
    //info for following rounds
    std::pair<int, int> fieldSizesData;
    std::map<int, int> shipsData;

    bool validFieldSize(std::pair<int, int>);
    bool validShipNum(int);
public:
    GameController(Game& game); //
    void initGame();
    void saveProgress();
    void loadProgress();
    void runGame();
    void newWave();
    void selectCommand(CommandArgs& args);
    void processAction(std::string playerInput);
};

class InputHandler
{
private:
    GameController& mController;
public:
    void processInput(std::string inputStr);
    InputHandler(GameController* controller);
};



#endif