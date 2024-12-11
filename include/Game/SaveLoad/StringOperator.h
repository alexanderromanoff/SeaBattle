#ifndef TO_STRING_H
#define TO_STRING_H

#include <string>
#include "../GameState.h"
#include "../../Players/UserPlayer.h"

class StringOperator
{
private:
    Battleship& buildShip(const std::string& shipInfo);

public:
    std::string toStringField(Field& field);
    std::string toStringShips(Field& field);
    std::string toStringAbMan(AbilityManager& abMan);

    Field& initFromStringField(std::string info, Field& field);
    ShipManager& initFromStringShips(std::string info, Field& field, ShipManager& shMan);
    AbilityManager& initFromStringAbMan(std::string info, AbilityManager& abMan);
    
};

#endif