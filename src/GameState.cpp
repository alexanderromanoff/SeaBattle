#include "../include/Game/GameState.h"
#include "../include/Players/DummyPlayer.h"
#include "../include/Players/UserPlayer.h"

GameState::GameState(UserPlayer* uPlayer, DummyPlayer* dPlayer) : 
userPlayer(uPlayer), dummyPlayer(dPlayer) {}

// GameState::GameState(const GameState& source)
// {
//     userPlayer = new UserPlayer(*source.userPlayer);
//     dummyPlayer = new DummyPlayer(*source.dummyPlayer);
// }
// GameState &GameState::operator = (const GameState& source)
// {
//     if(&source != this)
//     {
//         userPlayer = new UserPlayer(*source.userPlayer);
//         dummyPlayer = new DummyPlayer(*source.dummyPlayer);
//     }
//     return *this;

// }

UserPlayer* GameState::getUser()
{
    return userPlayer;
}

DummyPlayer* GameState::getDummy()
{
    return dummyPlayer;
}

GameState::~GameState()
{
    delete userPlayer;
    delete dummyPlayer;
}

 std::pair<int, int> GameState::getFieldSizes()
 {
    return fieldSizes;
 }

  std::map<int, int> GameState::getShipsMap()
  {
    return shipsMap;
  }

void GameState::setFieldSizes(std::pair<int,  int> fSizes)
{
    fieldSizes = fSizes;
}
void GameState::setShipsMap(std::map<int, int> shMap)
{
    shipsMap = shMap;
}
