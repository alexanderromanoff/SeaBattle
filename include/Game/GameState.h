#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <sstream>
#include <map>
// #include "../Players/DummyPlayer.h"
// #include "../Players/UserPlayer.h"

class UserPlayer;
class DummyPlayer;

class GameState
{
private:
    std::pair<int,  int> fieldSizes = {10, 10};
    std::map<int, int>  shipsMap = {{1, 4}, {2, 3}, {3, 2}, {4, 1}};
    UserPlayer* userPlayer = nullptr;
    DummyPlayer* dummyPlayer = nullptr; // при загрузке подаем класс шде игроки пока пустые

public:
    GameState(UserPlayer* uPlayer, DummyPlayer* dPlayer);
    ~GameState();
    GameState(const GameState& source);
    GameState & operator = (const GameState& source);
    // правило 3
    // GameState(GameState&& source);
    // GameState & operator = (GameState&& source);

    UserPlayer* getUser();
    DummyPlayer* getDummy();
    std::pair<int,  int> getFieldSizes();
    std::map<int, int> getShipsMap();
    void setFieldSizes(std::pair<int,  int>);
    void setShipsMap(std::map<int, int>);


};

#endif
