#ifndef FACTORY_H
#define FACTORY_H

#include "MassiveAttack/MassiveAttackArgs.h"
#include "Scaner/ScanerArgs.h"
#include "Shelling/ShellingArgs.h"
#include "MassiveAttack/MassiveAttack.h"
#include "Scaner/Scaner.h"
#include "Shelling/Shelling.h"
#include "Troll/Troll.h"

class Factory
{
private:
    IAbility* mAbility = nullptr;
public:
    IAbility & getAbility();
    void buildScaner(ScanerArgs& scArgs);
    void buildShelling(ShellingArgs& shArgs);
    void buildMassiveAttack(MassiveAttackArgs& maArgs);
    void buildTroll();
};

#endif