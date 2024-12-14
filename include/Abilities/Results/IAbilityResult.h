#ifndef ABILITY_RESULT_H
#define ABILITY_RESULT_H

//#include "IResultVisitor.h"
#include <string>

struct IAbilityResult
{
    virtual std::string getResult() = 0;
};

#endif