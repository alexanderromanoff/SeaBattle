#include "../include/Abilities/MassiveAttack/MassiveAttack.h"

MassiveAttack::MassiveAttack(TurnProperties* pProperties) : mProperties(pProperties) {};

IAbilityResult& MassiveAttack::applyAbility()
{
    mProperties->setAttackPower(2);
    return *(new MassiveAttackResult);
}

