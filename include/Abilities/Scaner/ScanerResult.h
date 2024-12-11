#ifndef SCANER_RES_H
#define SCANER_RES_H

#include "../Results/IAbilityResult.h"
#include <string>

struct ScanerResult : public IAbilityResult
{
    bool shipsFound = false;
    std::string getResult() {if(shipsFound)
    {
        return message + "found\n";
    }
    return message + "not found\n";}
    std::string message = "Ability applied successfully. Enemy's ships ";

};

#endif