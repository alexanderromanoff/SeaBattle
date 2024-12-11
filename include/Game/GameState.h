#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <sstream>
// #include "../Players/DummyPlayer.h"
// #include "../Players/UserPlayer.h"

class UserPlayer;
class DummyPlayer;

class GameState
{
private:

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
    // std::string getUserInfo() const;
    // std::string getDummyInfo() const;

};

#endif
