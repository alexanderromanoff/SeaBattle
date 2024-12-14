#ifndef GAME_OBSERVER_H
#define GAME_OBSERVER_H

#include "GameDisplayer.h"
class Player;

class GameObserver
{
protected:
    IGameDisplayer& mGameDisplayer;
public:
    virtual ~GameObserver() {}
    GameObserver(IGameDisplayer& gDisp);
    virtual void handleEvent(GameState& gState) = 0;
    GameObserver(const GameObserver& source); // why the skibidi i need it
    GameObserver & operator = (const GameObserver& source);  // turns out i actually need it
};


class ConcreteGameObserver : public GameObserver
{

public:
    ConcreteGameObserver(IGameDisplayer& gDisp);
    void handleEvent(GameState& gState);
};

// class UserObserver : public PlayerObserver
// {
// public:
//     UserObserver(IGameDisplayer& gDisp);
//     void handleEvent(Player& observedPlayer);
// };

// class DummyObserver : public PlayerObserver
// {
// public:
//     DummyObserver(IGameDisplayer& gDisp);
//     void handleEvent(Player& observedPlayer);
// };


#endif