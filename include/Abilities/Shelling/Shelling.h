#ifndef SHELLING_H
#define SHELLING_h

#include "../IAbility.h"
#include "ShellingResult.h"

class Shelling : public IAbility
{
private:
    ShipManager* mShipManager;
public:
    Shelling(ShipManager* pShipManager);
    IAbilityResult& applyAbility();
};

#endif