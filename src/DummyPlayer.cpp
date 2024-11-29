#include "../include/Players/DummyPlayer.h"
#include "../include/Game/GameController.h"
#include "../include/Game/Input/DummyInput.h"

void DummyPlayer::makeMove()
{
    std::cout << "bot attacks...\n";
    int x = rand() % mField->getWidth();
    int y = rand() % mField->getHeight();
    // add some different logic
    mInput.getFromBot(x, y);
    mController.processInput(mInput.readCommand());
}

void DummyPlayer::placeShips()
{
    for(int i = 0; i < mShManager->getNumberOfShips(); i++)
    {
        bool successful = false;
        while(!successful)
        {
            int x = rand() % mField->getWidth();
            int y = rand() % mField->getHeight();
            Battleship& shipObject = mShManager->getShipAtIndex(i);
            Battleship::Orientation orientation = mInput.readOrientation();
            int randVal = rand() % 2;
            try
            {
                mField->placeShip(shipObject, x, y, orientation);
                successful = true;
            }
            catch(CollisionException)
            {
                successful = false;
            }
            catch(OutOfFieldException)
            {
                successful = false;
            }
        }
    }
}

IOInterface& DummyPlayer::getIO()
{
    return mInput;
}

void DummyPlayer::processAttackResult(Field::Attack_Result atkRes, bool wasAttacked)
{
    if(atkRes == Field::Attack_Result::Wreck)
    {
        if(wasAttacked)
        {
            mAliveShips--;
        }
    }
}

void DummyPlayer::processAbilityResult(IAbilityResult& abRes)
{
    // doesn't generate abilities, won't handle result
}

void DummyPlayer::initDummy(std::pair<int, int> &fieldSize, std::map<int, int> &shipsMap)
{
    mField = new Field(fieldSize.first, fieldSize.second);
    mShManager = new ShipManager(shipsMap);
    mAbManager = new AbilityManager;
    mProperties = new TurnProperties;
    mAliveShips = mShManager->getNumberOfShips();
    isInitialized = true;
}

void DummyPlayer::initDummy(Field* field, ShipManager* shMan)
{
    mField = field;
    mShManager = shMan;
    mAbManager = new AbilityManager; // aren't required
    mProperties = new TurnProperties; // so they we can use just new empty instances
    mAliveShips = mShManager->getNumberOfShips();
    isInitialized = true;
}

DummyPlayer::DummyPlayer(InputHandler& controller) : mController(controller), mInput(*(new DummyInput)) {}



