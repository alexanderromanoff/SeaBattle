#ifndef MASSIVE_ATTACK_H
#define MASSIVE_ATTACK_H

#include "IAbility.h"

class MassiveAttack : public IAbility
{
private:
    Field* mField;
public:
    MassiveAttack(Field* pField);
    void applyAbility();
};

#endif