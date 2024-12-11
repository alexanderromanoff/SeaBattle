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

int DummyPlayer::getPlIndex()
{
    return placingIndex;
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
            mAliveShips--;
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
    // mAbManager = new AbilityManager;
    // mProperties = new TurnProperties;
    mAliveShips = mShManager->getNumberOfShips();
    std::string hor = std::to_string(mField->getWidth());
    std::string ver = std::to_string(mField->getHeight());
    mMediator.callOutput(this, Player::PlayerInputRequest::DATA, {hor, ver});
}

void DummyPlayer::initDummy(Field* field, ShipManager* shMan)
{
    mField = field;
    mShManager = shMan;
    // mAbManager = new AbilityManager; // aren't required
    // mProperties = new TurnProperties; // so they we can use just new empty instances
    std::string hor = std::to_string(mField->getWidth());
    std::string ver = std::to_string(mField->getHeight());

    mMediator.callOutput(this, Player::PlayerInputRequest::DATA, {hor, ver});
    mAliveShips = mShManager->getNumberOfShips();
    isInitialized = true;

}

DummyPlayer::DummyPlayer(IOMediator& mediator) : Player(mediator)
{
    mediator.setDummyColleague(this);
}

DummyPlayer::DummyPlayer(const DummyPlayer& source):Player(source) 
{
    mMediator.setDummyColleague(this);
}

DummyPlayer& DummyPlayer::operator = (const DummyPlayer& source)
{
    if(&source != this)
    {
        mMediator = source.mMediator;

        mMediator.setDummyColleague(this);

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
        mAliveShips = source.mAliveShips;   
        isInitialized = source.isInitialized;    
    }  
    return *this;
}


void DummyPlayer::makeChoice()
{
    
}



