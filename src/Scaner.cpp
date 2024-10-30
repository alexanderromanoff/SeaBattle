#include "../include/Scaner.h"


Scaner::Scaner(std::pair<int, int> coords, Field* pField)
    : mCoords(coords), mField(pField) {} //mAbilityResult(pAbilityResult)

void Scaner::applyAbility()
{
    int x = mCoords.first;
    int y = mCoords.second;
    for(int i = x; i <= x+1; i++)
        {
            for(int j = y; j <= y+1; j++)
            {
                if(mField->checkCellInField(i, j))
                {
                    if(mField->isCellOccupied(i, j))
                    {
                        std::cout << "battleships found\n";
                        //mAbilityResult->shipsFound = true;
                        return;
                    }
                }
            }
        }
        std::cout << "battleships not found\n";
}

// void Scaner::setField(Field & fieldObject)
// {
//     mFieldPointer = &fieldObject;
// }

// void Scaner::setCoords(int x, int y)
// {
//     this->x = x;
//     this->y = y;
// }
