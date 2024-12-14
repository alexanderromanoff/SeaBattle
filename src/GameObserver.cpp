#include "../include/Game/Display/GameObserver.h"
#include "../include/Players/UserPlayer.h"
#include "../include/Players/DummyPlayer.h"

GameObserver::GameObserver(IGameDisplayer& gDisp) : mGameDisplayer(gDisp) {}

GameObserver::GameObserver(const GameObserver& source) : mGameDisplayer(source.mGameDisplayer) {}

GameObserver& GameObserver::operator = (const GameObserver& source)
{
    if(&source != this)
    {
        mGameDisplayer = source.mGameDisplayer;
    }
    return *this;
}


ConcreteGameObserver::ConcreteGameObserver(IGameDisplayer& gDisp) : GameObserver(gDisp) {}

void ConcreteGameObserver::handleEvent(GameState& gState)
{
    mGameDisplayer.drawField(gState.getUser()->getField(), gState.getDummy()->getField());
}