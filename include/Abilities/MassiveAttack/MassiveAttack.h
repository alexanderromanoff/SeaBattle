#ifndef MASSIVE_ATTACK_H
#define MASSIVE_ATTACK_H

#include "../IAbility.h"
#include "MassiveAttackResult.h"

class MassiveAttack : public IAbility
{
private:
    TurnProperties* mProperties;
public:
    MassiveAttack(TurnProperties* pProperties);
    IAbilityResult& applyAbility();
};

#endif