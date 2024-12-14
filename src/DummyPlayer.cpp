#include "../include/Players/DummyPlayer.h"
#include "../include/Game/GameController.h"
#include "../include/Game/Input/IOMediator.h"
// #include "../include/Game/Input/DummyInput.h"

void DummyPlayer::makeMove()
{
    // mMediator.callOutput(this, Player::PlayerInputRequest::INFO, {DummyPlayer::THINK});
    // add some different logic
    mMediator.callInput(this, Player::PlayerInputRequest::COMMAND);
    
}


void DummyPlayer::placeShips()
{
    for(int i = 0; i < mShManager->getNumberOfShips(); i++)
    {
        bool success = false;
        do
        {   
            try
            {
                mMediator.callInput(this, Player::PlayerInputRequest::PLACE_SHIP);
                success = true;
            }
            catch(OutOfFieldException& ex)
            {
                success = false;
            }
            catch(CollisionException& ex)
            {
                success = false;
            }
            catch(ShipAlreadyPlacedException& ex)
            {
                success = false;
            }
            
        } while (!success);
        placingIndex++;
                
    }
    isInitialized = true;
}

void DummyPlayer::processAttackResult(Field::Attack_Result atkRes, bool wasAttacked)
{
    if(atkRes == Field::Attack_Result::Invalid)
    {
        if(!wasAttacked)
        {
            makeMove();
        }
    }
    if(atkRes == Field::Attack_Result::Wreck)
    {
        if(wasAttacked)
        {
            mShManager->processDeath();
        }
    }
    // if(wasAttacked)
    // {
    //     mObserver.handleEvent(*this);
    // }
    
}

void DummyPlayer::processAbilityResult(IAbilityResult& abRes)
{
    // doesn't generate abilities, won't handle result
}

void DummyPlayer::initDummy(std::pair<int, int> &fieldSize, std::map<int, int> &shipsMap)
{
    mField = new Field(fieldSize.first, fieldSize.second);
    mShManager = new ShipManager(shipsMap);
    mProperties = new TurnProperties;
    mProperties->switchBlock(false);
   // mAliveShips = mShManager->getNumberOfShips();
    // connectToMediator();
}

void DummyPlayer::initDummy(Field* field, ShipManager* shMan)
{
    mField = field;
    mShManager = shMan;
    mProperties = new TurnProperties;
    mProperties->switchBlock(false);
  //  mAliveShips = mShManager->getNumberOfShips();
    isInitialized = true;
    // connectToMediator();

}

void DummyPlayer::connectToMediator()
{
    mMediator.setDummyColleague(this);
}

DummyPlayer::DummyPlayer(IOMediator& mediator) : Player(mediator)
{
   
}

DummyPlayer::DummyPlayer(const DummyPlayer& source):Player(source) 
{
}

DummyPlayer& DummyPlayer::operator = (const DummyPlayer& source)
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
            newShip->setPlaced(false);
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
        isInitialized = source.isInitialized;    
    }  
    return *this;
}


void DummyPlayer::makeChoice()
{
    
}



