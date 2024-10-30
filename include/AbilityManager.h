#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H
#include <list>
#include "Visitor.h"
#include "IAbility.h"
#include "Factory.h"
#include <algorithm>
#include <queue>

class AbilityManager
{
public:
    enum AbilitiesCodes {MASSIVE_ATTACK = 0, SHELLING = 1, SCANER = 2};
private:
    std::queue<AbilitiesCodes> mAvaliableAbilitiesInfo;
    IAbility& buildAbility(IArgs & arguments);
public:
    AbilityManager();
    void recieveAbility();
    void useAbility(IArgs & arguments); 
    AbilitiesCodes viewAvaliableAbilities();
};


#endif