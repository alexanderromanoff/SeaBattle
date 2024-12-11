#include "../include/Game/GameState.h"
#include "../include/Players/DummyPlayer.h"
#include "../include/Players/UserPlayer.h"

GameState::GameState(UserPlayer* uPlayer, DummyPlayer* dPlayer) : userPlayer(uPlayer), dummyPlayer(dPlayer) {}
GameState::GameState(const GameState& source)
{
    userPlayer = new UserPlayer(*source.userPlayer);
    dummyPlayer = new DummyPlayer(*source.dummyPlayer);
}
GameState &GameState::operator = (const GameState& source)
{
    if(&source != this)
    {
        userPlayer = new UserPlayer(*source.userPlayer);
        dummyPlayer = new DummyPlayer(*source.dummyPlayer);
    }
    return *this;
}

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


