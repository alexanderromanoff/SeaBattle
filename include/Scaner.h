#ifndef SCANER_H
#define SCANER_H

#include "IAbility.h"

class Scaner : public IAbility
{
private:
    std::pair<int, int> mCoords;
    Field* mField;
    //AbilityResult* mAbilityResult; // ability result is temporarily inavailable
public:
    Scaner(std::pair<int, int> coords, Field* pFieldPointer);
    void applyAbility();
};

#endif