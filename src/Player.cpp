#include "../include/Players/Player.h"
#include "../include/Game/Input/IOMediator.h"

Field& Player::getField()
{
    return *mField;
}

ShipManager& Player::getShManager()
{
    return *mShManager;
}

TurnProperties& Player::getProperties()
{
    return *mProperties;
}

AbilityManager& Player::getAbManager()
{
    return *mAbManager;
}

bool Player::isAlive()
{
    return mShManager->getNumberOfAliveShips() != 0;
}

bool Player::isInit()
{
    return isInitialized;
}

int Player::getPlIndex()
{
    return placingIndex;
}

std::map<int, int> Player::getSetOfShips()
{
    std::map<int, int> res;
    res.insert({1, 0});
    res.insert({2, 0});
    res.insert({3, 0});
    res.insert({4, 0});
    for(int i = 0; i < mShManager->getNumberOfShips(); i++)
    {
        int key = mShManager->getShipAtIndex(i).getNumberOfSegments();
        res[key] += 1;
    }
    return res;
}

Player::Player(IOMediator& mediator) : mMediator(mediator) {}

Player::Player(const Player& source) : mMediator(source.mMediator)
{
    mField = new Field(*source.mField);
    mShManager = new ShipManager;
    std::map<std::pair<int, int>, Battleship*> sourceShips = source.mField->getShips();
    for(auto & item : sourceShips)
    {
        Battleship* newShip = new Battleship(*item.second);
        newShip->setPlaced(false);
        mShManager->addShip(*newShip);
        mField->placeShip(*newShip, item.first.second, item.first.first, newShip->getOrientation());
    }
    if(source.mProperties != nullptr)
    {
        mProperties = new TurnProperties(*source.mProperties);
    }
    if(source.mAbManager != nullptr)
    {
        mAbManager = new AbilityManager(*source.mAbManager);
    }
   // mAliveShips = source.mAliveShips;   
    isInitialized = source.isInitialized; 

}

Player &Player::operator = (const Player& source)
{
    if(&source != this)
    {
        mMediator = source.mMediator;

        mField = new Field(*source.mField);
        mShManager = new ShipManager;
        std::map<std::pair<int, int>, Battleship*> sourceShips = source.mField->getShips();
        for(auto & item : sourceShips)
        {
            Battleship* newShip = new Battleship(*item.second);
            mShManager->addShip(*newShip);
            mField->placeShip(*newShip, item.first.first, item.first.second, newShip->getOrientation());
        }
        if(source.mProperties != nullptr)
        {
            mProperties = new TurnProperties(*source.mProperties);
        }
        if(source.mAbManager != nullptr)
        {
            mAbManager = new AbilityManager(*source.mAbManager);
        }
       // mAliveShips = source.mAliveShips;       
    }  
    return *this; 
}

Player::~Player()
{    
    delete mField;
    delete mAbManager;
    delete mShManager;
    delete mProperties;
}