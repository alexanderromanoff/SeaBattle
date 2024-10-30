#include "../include/Factory.h"

void Factory::buildScaner(ScanerArgs& scArgs)
{
    mAbility = new Scaner(scArgs.coordinates, scArgs.pField);
}

void Factory::buildShelling(ShellingArgs&shArgs)
{
    mAbility = new Shelling(shArgs.pField, shArgs.pShipManager);
}

void Factory::buildMassiveAttack(MassiveAttackArgs& maArgs)
{
    mAbility = new MassiveAttack(maArgs.pField);
}

IAbility & Factory::getAbility()
{
    if(mAbility == nullptr)
    {

    }
    return *mAbility;
}