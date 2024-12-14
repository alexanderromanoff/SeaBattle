#include "../include/Players/UserPlayer.h"
#include "../include/Game/GameController.h"
// #include "../include/Game/Input/ConsoleInput.h"
#include "../include/Game/Input/IOMediator.h"

void UserPlayer::makeMove()
{
    mMediator.callInput(this, Player::PlayerInputRequest::COMMAND);
    
}

void UserPlayer::placeShips()
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
                std::cerr << ex.what() << '\n';
            }
            catch(CollisionException& ex)
            {
                success = false;
                std::cerr << ex.what() << '\n';
            }
            catch(ShipAlreadyPlacedException& ex)
            {
                success = false;
                std::cerr << ex.what() << '\n';
            }
            
        } while (!success);
        placingIndex++;
        
        // mObserver.handleEvent(*this);
    }
    isInitialized = true;
}

void UserPlayer::makeChoice()
{
    mMediator.callInput(this, Player::PlayerInputRequest::MAKE_CHOICE);
}

void UserPlayer::processAttackResult(Field::Attack_Result atkRes, bool wasAttacked)
{
    if(!wasAttacked)
    {
        // if USER was an ATTACKER (agressor)
        switch (atkRes)
        {
        case Field::Attack_Result::Miss:
            mMediator.callOutput(this, Player::PlayerInputRequest::INFO, {UserPlayer::MISS});
            break;
        case Field::Attack_Result::Invalid:
            mMediator.callOutput(this, Player::PlayerInputRequest::INFO, {UserPlayer::INVALID});
            break;
        case Field::Attack_Result::Strike:
            mMediator.callOutput(this, Player::PlayerInputRequest::INFO, {UserPlayer::STRIKE});
            break;
        case Field::Attack_Result::Wreck:
            mAbManager->recieveAbility();
            mMediator.callOutput(this, Player::PlayerInputRequest::INFO, {UserPlayer::WRECK});
            break;
        case Field::Attack_Result::Defeat:
            mMediator.callOutput(this, Player::PlayerInputRequest::INFO, {"великая победа, капитан, новый раунд "});

        default:
            break;
        }
    }
    else
    {
        // if user WAS attacked
        switch (atkRes)
        {
        case Field::Attack_Result::Wreck:
            mShManager->processDeath();
            break;
        case Field::Attack_Result::Defeat:
            mMediator.callOutput(this, Player::PlayerInputRequest::INFO, {"делааа... поражение, кэп "});
            break;
        default:
            break;
        }
        // mObserver.handleEvent(*this);
    }
    mProperties->switchBlock(false);
    mProperties->setAttackPower(1);
    

}

void UserPlayer::processAbilityResult(IAbilityResult& abRes)
{
    mMediator.callOutput(this, Player::PlayerInputRequest::INFO, {abRes.getResult()});
    mProperties->switchBlock(true);
}

void UserPlayer::initUser(std::pair<int, int> &fieldSize, std::map<int, int> &shipsMap)
{
    mField = new Field(fieldSize.first, fieldSize.second);
    mShManager = new ShipManager(shipsMap);
    mAbManager = new AbilityManager;
    mProperties = new TurnProperties;
   // mAliveShips = mShManager->getNumberOfShips();
    // connectToMediator();
}

void UserPlayer::initUser(Field* field, ShipManager* shMan, AbilityManager* abMan)
{
    mField = field;
    mShManager = shMan;
    mAbManager = abMan;
    mProperties = new TurnProperties;
   // mAliveShips = mShManager->getNumberOfShips();
    isInitialized = true;
    // connectToMediator();
}


void UserPlayer::connectToMediator()
{
    mMediator.setUserColleague(this);
}

UserPlayer::UserPlayer(IOMediator& mediator) : Player(mediator) 
{
}
UserPlayer::UserPlayer(const UserPlayer& source) : Player(source) 
{
} 

UserPlayer & UserPlayer::operator = (const UserPlayer& source)
{
    if(&source != this)
    {
        mMediator = source.mMediator;
        // mObserver = source.mObserver;

        mMediator.setUserColleague(this);

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
