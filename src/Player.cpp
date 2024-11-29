#include "../include/Players/Player.h"

Field& Player::getField()
{
    return *mField;
}

ShipManager& Player::getShManager()
{
    return *mShManager;
}

TurnProperties& Player::getProperties()
{
    return *mProperties;
}

AbilityManager& Player::getAbManager()
{
    return *mAbManager;
}

bool Player::isAlive()
{
    return mAliveShips != 0;
}

bool Player::isInit()
{
    return isInitialized;
}

// Player::Player(InputHandler& controller)  : mController(controller) {}