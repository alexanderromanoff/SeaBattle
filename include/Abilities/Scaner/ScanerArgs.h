#ifndef SCANER_ARGS_H
#define SCANER_ARGS_H

#include "../Arguments/IAbilityArguments.h"
#include "../Arguments/IArgumentsVisitor.h"
#include "../IAbility.h"

struct ScanerArgs : public IAbilityArguments
{
//methods
    ScanerArgs(std::pair <int, int> coordinates, Field * pField) : 
        coordinates(coordinates), pField(pField) {}
    void acceptVisitor(IArgumentsVisitor & visitor) {visitor.Visit(*this);}
//members
    std::pair <int, int> coordinates;
    Field * pField;
};

#endif