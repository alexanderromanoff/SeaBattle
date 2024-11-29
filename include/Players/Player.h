#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "../ShipManager.h"
#include "../Field.h"

#include "../Game/Input/IOInterface.h"
#include "../AbilityManager.h"
#include "../Abilities/Results/ResultVisitor.h"
#include "TurnProperties.h"

class InputHandler;

class Player
{
protected:

    Field* mField = nullptr;
    ShipManager* mShManager = nullptr;
    TurnProperties* mProperties = nullptr;
    AbilityManager* mAbManager = nullptr;

    bool isInitialized = false;
    int mAliveShips;

public:
    virtual void makeMove() = 0;
    virtual void placeShips() = 0;
    virtual void processAttackResult(Field::Attack_Result atkRes, bool wasAttacked) = 0;
    virtual void processAbilityResult(IAbilityResult& abRes) = 0;
    virtual IOInterface& getIO() = 0;
    
    bool isAlive();
    bool isInit();

    Field& getField();
    ShipManager& getShManager();
    TurnProperties& getProperties();
    AbilityManager& getAbManager();
 

   // Player(InputHandler& controler);
    
};

#endif