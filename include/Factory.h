#ifndef FACTORY_H
#define FACTORY_H

#include "IAbility.h"
#include "IArgs.h"
#include "MassiveAttack.h"
#include "Scaner.h"
#include "Shelling.h"
#include "MassiveAttackArgs.h"
#include "ScanerArgs.h"
#include "ShellingArgs.h"

class Factory
{
private:
    IAbility* mAbility = nullptr;
public:
    IAbility & getAbility();
    void buildScaner(ScanerArgs& scArgs);
    void buildShelling(ShellingArgs& shArgs);
    void buildMassiveAttack(MassiveAttackArgs& maArgs);
};

#endif