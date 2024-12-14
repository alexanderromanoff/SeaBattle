#ifndef USER_PLAYER_H
#define USER_PLAYER_H

#include "Player.h"


class UserPlayer : public Player
{
public:
    const std::string MISS = "мимо\n";
    const std::string STRIKE = "ранил\n";
    const std::string WRECK = "убил\n";
    const std::string INVALID = "уже атаковано\n";

public:
    UserPlayer(IOMediator& handler);
    UserPlayer(const UserPlayer& source);  
    UserPlayer & operator = (const UserPlayer& source);

    void initUser(std::pair<int, int>& fieldSize, std::map<int, int>& shipsMap);
    void initUser(Field* field, ShipManager* shMan, AbilityManager* abMan);

    void makeMove();
    void placeShips();
    void makeChoice();
    void processAttackResult(Field::Attack_Result atkRes, bool wasAttacked);
    void processAbilityResult(IAbilityResult& abRes);
    void connectToMediator();
};

#endif
