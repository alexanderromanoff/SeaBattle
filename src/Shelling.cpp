#include "../include/Abilities/Shelling/Shelling.h"

Shelling::Shelling(ShipManager* pShipManager) : mShipManager(pShipManager)
{}

IAbilityResult& Shelling::applyAbility()
{   
    srand(time(NULL));
    std::vector<int> shipsToAttackIndices;
    ShellingResult& res = *(new ShellingResult);
    try
    {
        shipsToAttackIndices = mShipManager->getAliveShipsIndicies();
    }
    catch(NoShipsException& ex)
    {
        res.success = false;
        return res;
    }
    
    int randomIndex = rand() % shipsToAttackIndices.size(); 
    Battleship & shipObject = mShipManager->getShipAtIndex(randomIndex);

    std::vector<int> segmentsToAttackIndices = shipObject.getAliveSegmentsIndices();
    int randomSegmentIndex = rand() % segmentsToAttackIndices.size();
    shipObject.takeDamage(randomSegmentIndex, 1);

    return res;
}