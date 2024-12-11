#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H
#include <algorithm>
#include <queue>
#include "Abilities/Arguments/ArgumentsVisitor.h"
#include "Abilities/IAbility.h"
#include "Exceptions/ExcepNoAbilities.h"



class AbilityManager
{
public:
    enum AbilitiesCodes {MASSIVE_ATTACK = 0, SHELLING = 1, SCANER = 2, NONE = 3};
private:
    std::queue<AbilitiesCodes> mAvaliableAbilitiesInfo;
    IAbility& buildAbility(IAbilityArguments & arguments);
public:
    AbilityManager();
    void recieveAbility();
    std::queue<AbilitiesCodes> getInfo();
    void setInfo(std::queue<AbilitiesCodes>);
    IAbilityResult& useAbility(IAbilityArguments & arguments); 
    AbilitiesCodes viewAvaliableAbilities();
};


#endif