#ifndef SHELLING_H
#define SHELLING_h

#include "../IAbility.h"
#include "TrollResult.h"

class Troll : public IAbility
{

public:
    Troll() = default;
    IAbilityResult& applyAbility()
    {
        return *(new TrollResult);
    }
};

#endif