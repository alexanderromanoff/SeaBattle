#ifndef SHELLING_H
#define SHELLING_h

#include "IAbility.h"

class Shelling : public IAbility
{
private:
    Field* mField;
    ShipManager* mShipManager;
public:
    Shelling(Field* pField, ShipManager* pShipManager);
    void applyAbility();
};

#endif