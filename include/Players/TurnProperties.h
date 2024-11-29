#ifndef TURN_PROPERTIES_H
#define TURN_PROPERTIES_H

struct TurnProperties
{
    int attackPower = 1;
    void setAttackPower(int newPower)
    {
        attackPower = newPower;
    }
    // more things later
};

#endif