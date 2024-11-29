#ifndef USER_PLAYER_H
#define USER_PLAYER_H

#include "Player.h"
#include "../Game/Input/ConsoleInput.h"


// Forward declarations
//class ConsoleInput;

class UserPlayer : public Player
{
private:
    ConsoleInput& mInput;
    InputHandler& mController;
public:
    UserPlayer(InputHandler& controller);
    void initUser(std::pair<int, int>& fieldSize, std::map<int, int>& shipsMap);
    void initUser(Field* field, ShipManager* shMan);

    void makeMove();
    void placeShips();
    void processAttackResult(Field::Attack_Result atkRes, bool wasAttacked);
    void processAbilityResult(IAbilityResult& abRes);
    IOInterface& getIO();
};

#endif
