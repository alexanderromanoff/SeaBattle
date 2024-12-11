#include "../include/Abilities/Scaner/Scaner.h"


Scaner::Scaner(std::pair<int, int> coords, Field* pField)
    : mCoords(coords), mField(pField) {}

IAbilityResult& Scaner::applyAbility()
{
    int x = mCoords.first;
    int y = mCoords.second;
    ScanerResult &result = *(new ScanerResult);
    for(int i = x; i <= x+1; i++)
        {
            for(int j = y; j <= y+1; j++)
            {
                if(mField->checkCellInField(i, j))
                {
                    if(mField->isCellOccupied(i, j))
                    {
                        result.shipsFound = true;
                    }
                }
            }
        }
        return result;
}