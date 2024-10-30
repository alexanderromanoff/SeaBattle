#include "../include/MassiveAttack.h"

MassiveAttack::MassiveAttack(Field* pField) : mField(pField) {};

void MassiveAttack::applyAbility()
{
    std::cout << "mField->setAttackPower(2)\n";
}

// void MassiveAttack::setField(Field & fieldObject)
// {
//     mFieldPointer = &fieldObject;
// }
