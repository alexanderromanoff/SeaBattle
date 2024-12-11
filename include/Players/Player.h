#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "../ShipManager.h"
#include "../Field.h"
// #include "../Game/Input/IOMediator.h"
#include "../AbilityManager.h"
#include "TurnProperties.h"

class IOMediator;

class Player
{
protected:
    IOMediator& mMediator;
    // PlayerObserver& mObserver;

    Field* mField = nullptr;
    ShipManager* mShManager = nullptr;
    TurnProperties* mProperties = nullptr;
    AbilityManager* mAbManager = nullptr;

    bool isInitialized = false;
    int mAliveShips;

public:                 
    enum PlayerInputRequest {PLACE_SHIP, COMMAND, MAKE_CHOICE, INFO, DATA};
    virtual void makeMove() = 0;
    virtual void placeShips() = 0;
    virtual void makeChoice() = 0;
    virtual void processAttackResult(Field::Attack_Result atkRes, bool wasAttacked) = 0;
    virtual void processAbilityResult(IAbilityResult& abRes) = 0;
    
    bool isAlive();
    bool isInit();

    Field& getField();
    ShipManager& getShManager();
    TurnProperties& getProperties();
    AbilityManager& getAbManager();
    
    Player(IOMediator& mediator); 
    Player(const Player& source);  
    Player & operator = (const Player& source);
    // Player(Player&& source);
    // Player & operator = (Player&& source);
    ~Player();
    
};

#endif