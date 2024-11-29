#ifndef DUMMY_PLAYER_H
#define DUMMY_PLAYER_H

#include "Player.h"
#include "../Game/Input/DummyInput.h"

//
// class DummyInput;

class DummyPlayer : public Player
{
private:
    DummyInput& mInput;
    InputHandler& mController;
public:
    DummyPlayer(InputHandler& controller);
    void initDummy(std::pair<int, int> &fieldSize, std::map<int, int> &shipsMap);
    void initDummy(Field* field, ShipManager* shMan);

    void makeMove();
    void placeShips();
    void processAttackResult(Field::Attack_Result atkRes, bool wasAttacked);
    void processAbilityResult(IAbilityResult& abRes);
    IOInterface& getIO();
};

#endif