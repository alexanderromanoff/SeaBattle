#ifndef MASSIVE_ATTACK_ARGS_H
#define MASSIVE_ATTACK_ARGS_H

#include "../Arguments/IAbilityArguments.h"
#include "../Arguments/IArgumentsVisitor.h"
#include "../IAbility.h"

struct MassiveAttackArgs : public IAbilityArguments
{
//methods
    void acceptVisitor(IArgumentsVisitor & visitor) {visitor.Visit(*this);}
    MassiveAttackArgs(TurnProperties* pTurnProps) : pTurnProps(pTurnProps) {}
//members
    TurnProperties * pTurnProps;
};

#endif