#ifndef DUMMY_PLAYER_H
#define DUMMY_PLAYER_H

#include "Player.h"


class DummyPlayer : public Player
{

public:
    DummyPlayer(IOMediator& mediator);
    DummyPlayer(const DummyPlayer& source);  
    DummyPlayer & operator = (const DummyPlayer& source);
    void initDummy(std::pair<int, int> &fieldSize, std::map<int, int> &shipsMap); 
    void initDummy(Field* field, ShipManager* shMan);
    void makeMove();
    void placeShips();
    void makeChoice();
    void processAttackResult(Field::Attack_Result atkRes, bool wasAttacked);
    void processAbilityResult(IAbilityResult& abRes);
    void connectToMediator();
};

#endif