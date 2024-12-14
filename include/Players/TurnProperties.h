#ifndef TURN_PROPERTIES_H
#define TURN_PROPERTIES_H

struct TurnProperties
{
    int attackPower = 1;
    bool abilityBlocked = false;
    void setAttackPower(int newPower)
    {
        attackPower = newPower;
    }
    void switchBlock(bool val)
    {
        abilityBlocked = val;
    }
    // more things later
};

#endif