#ifndef MASSIVE_ATTACK_RES_H
#define MASSIVE_ATTACK_RES_H

#include "../Results/IAbilityResult.h"
#include <string>

struct MassiveAttackResult : public IAbilityResult
{
    std::string getResult() {return message;}
    std::string message = "Ability applied successfully, the damage will be doubled\n";
};

#endif