#ifndef I_ABILITY
#define I_ABILITY
#include <variant>
#include <iostream>
#include "../Field.h"
#include "../ShipManager.h"
#include "../Players/TurnProperties.h"
#include "../Battleship.h"
#include "Results/IAbilityResult.h"


class IAbility
{
public:
    virtual IAbilityResult& applyAbility() = 0;
};

#endif