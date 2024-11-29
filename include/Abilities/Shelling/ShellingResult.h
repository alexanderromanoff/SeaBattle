#ifndef SHELLING_RES_H
#define SHELLING_RES_H

#include "../Results/IAbilityResult.h"
#include <string>

struct ShellingResult : public IAbilityResult
{
    std::string getResult() {return successMessage;}
    bool success = true;
    std::string successMessage = "Ability applied successfully, enemy's ship was damaged\n";
    std::string failMessage = "Ability applied, but there were no ships to damage";
};

#endif