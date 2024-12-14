#ifndef IARGS_H
#define IARGS_H

#include "IArgumentsVisitor.h"

struct IAbilityArguments
{
    virtual void acceptVisitor(IArgumentsVisitor & visitor) = 0;
};

#endif