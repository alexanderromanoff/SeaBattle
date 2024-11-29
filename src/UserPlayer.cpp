#include "../include/Players/UserPlayer.h"
#include "../include/Game/GameController.h"
#include "../include/Game/Input/ConsoleInput.h"

void UserPlayer::makeMove()
{
    mController.processInput(mInput.readCommand());
}

void UserPlayer::placeShips()
{
for(int i = 0; i < mShManager->getNumberOfShips(); i++)
    {
        bool successful = false;
        while(!successful)
        {
            Battleship& shipObject = mShManager->getShipAtIndex(i);
            std::pair<int, int> coords = mInput.readShipPlacement(shipObject.getNumberOfSegments());
            int x = coords.first;
            int y = coords.second;
            Battleship::Orientation orientation = mInput.readOrientation();
        
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
        std::cout << "success\n";
    }
}

IOInterface& UserPlayer::getIO()
{
    return mInput;
}

void UserPlayer::processAttackResult(Field::Attack_Result atkRes, bool wasAttacked)
{
    if(atkRes == Field::Attack_Result::Wreck)
    {
        if(wasAttacked)
        {
            mAliveShips--;
        }
        else
        {
            mAbManager->recieveAbility();
        }
    }
    if(!wasAttacked)
    {
    switch (atkRes)
    {
    case Field::Attack_Result::Miss:
        mInput.writeRes("мимо!\n");
        break;
    case Field::Attack_Result::Invalid:
        mInput.writeRes("клетка уже была атакована\n");
        break;
    case Field::Attack_Result::Strike:
        mInput.writeRes("ранил!\n");
        break;
    case Field::Attack_Result::Wreck:
        mInput.writeRes("убил.\n");
        break;

    default:
        break;
    }
    }

}

void UserPlayer::processAbilityResult(IAbilityResult& abRes)
{
    mInput.writeRes(abRes.getResult());
}

void UserPlayer::initUser(std::pair<int, int> &fieldSize, std::map<int, int> &shipsMap)
{
    mField = new Field(fieldSize.first, fieldSize.second);
    mShManager = new ShipManager(shipsMap);
    mAbManager = new AbilityManager;
    mProperties = new TurnProperties;
    mAliveShips = mShManager->getNumberOfShips();
    isInitialized = true;
}

void UserPlayer::initUser(Field* field, ShipManager* shMan)
{
    mField = field;
    mShManager = shMan;
    mAbManager = new AbilityManager; // will also be initialized as field and shMan
    mProperties = new TurnProperties;
    mAliveShips = mShManager->getNumberOfShips();
    isInitialized = true;
}

UserPlayer::UserPlayer(InputHandler& controller) : mController(controller), mInput(*(new ConsoleInput)) {}