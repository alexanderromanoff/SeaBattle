#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H


#include "CommandArgs.h"
#include "Game.h"
#include <fstream>
#include <string>
#include <regex>

class Saver;
class IOMediator;
class PlayerObserver;

// template for input device here
class GameController
{
private:

    Game& mGame;
    IOMediator* mMediator;
    std::string savePath = "svae1.txt";

private:
    int count  = 0;
    bool sizesInit = false;
    bool shipsInit = false;
    std::pair<int, int> fieldSizes;
    std::map<int, int> shipsMap;

public:
    bool interruptSignal = false;
    ~GameController();
    GameController(Game& game);
    // Game& getGame();
    void setChoice();
    void initController(IOMediator* mediator); 
    void initGame();
    void setFieldData(std::pair<int, int> sizes);
    std::pair<int, int> getFieldSizes();
    void setShipsData(std::map<int, int> shipsMap);
    void controlGame();
    void saveProgress();
    void loadProgress();
    void selectCommand(CommandArgs& args);
};



#endif