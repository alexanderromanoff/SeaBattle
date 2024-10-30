#ifndef I_ABILITY
#define I_ABILITY
#include <variant>
#include <iostream>
#include "Field.h"
#include "ShipManager.h"

class IAbility
{
public:
    virtual void applyAbility() = 0;
};

#endif