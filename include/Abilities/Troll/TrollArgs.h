#ifndef SHELLING_ARGS_H
#define SHELLING_ARGS_H

#include "../Arguments/IAbilityArguments.h"
#include "../Arguments/IArgumentsVisitor.h"
#include "../IAbility.h"

struct TrollArgs : public IAbilityArguments
{
//methods
    TrollArgs() {}
    void acceptVisitor(IArgumentsVisitor & visitor) {visitor.Visit(*this);}
};

#endif