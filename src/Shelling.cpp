#include "../include/Shelling.h"

Shelling::Shelling(Field* pFIeld, ShipManager* pShipManager) : mField(pFIeld), mShipManager(pShipManager)
{}

void Shelling::applyAbility()
{
    std::vector<int> shipsToAttackIndices = mShipManager->getAliveShipsIndicies();
    srand(time(NULL));
    int randomIndex = rand() % shipsToAttackIndices.size();
    Battleship & shipObject = mShipManager->getShipAtIndex(randomIndex);
    int randomSegmentIndex = rand() % shipObject.getNumberOfSegments();
    int damage = 1;
    // mField->setAttackPower(1);
    shipObject.takeDamage(randomSegmentIndex, damage);
}

// void Shelling::setField(Field & fieldObject)
// {
//     mFieldPointer = &fieldObject;
// }

// void Shelling::setShipManager(ShipManager & shipManagerObject)
// {
//     mShipManagerPointer = &shipManagerObject;
// }