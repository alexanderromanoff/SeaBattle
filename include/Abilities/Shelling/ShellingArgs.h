#ifndef SHELLING_ARGS_H
#define SHELLING_ARGS_H

#include "../Arguments/IAbilityArguments.h"
#include "../Arguments/IArgumentsVisitor.h"
#include "../IAbility.h"

struct ShellingArgs : public IAbilityArguments
{
//methods
    ShellingArgs(ShipManager* pShipManager) : pShipManager(pShipManager) {}
    void acceptVisitor(IArgumentsVisitor & visitor) {visitor.Visit(*this);}
//members
    ShipManager * pShipManager;
};

#endif