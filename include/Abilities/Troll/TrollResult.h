#ifndef TROLL_RES_H
#define TROLL_RES_H

#include "../Results/IAbilityResult.h"
#include <string>

struct TrollResult : public IAbilityResult
{
    std::string getResult() {return successMessage;}
    std::string successMessage = "hehehe u can't apply more than 1 ability per move\n";
};

#endif