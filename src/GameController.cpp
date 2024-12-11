#include "../include/Game/GameController.h"
#include "../include/Game/Game.h"
#include "../include/Game/SaveLoad/Saver.h"
#include "../include/Players/DummyPlayer.h"
#include "../include/Players/UserPlayer.h"

GameController::GameController(Game& game) : mGame(game)
{

}

GameController::~GameController()
{}

void GameController::initController(IOMediator* mediator)
{
    mMediator = mediator;
    mSaver = new Saver;
}


void GameController::setChoice()
{
    UserPlayer placeholder = UserPlayer(*mMediator);
    placeholder.makeChoice();

}


void GameController::initGame()
{
    std::cout << "new game\n";
    UserPlayer *userPlayer = new UserPlayer(*mMediator);
    DummyPlayer *dummyPlayer = new DummyPlayer(*mMediator);
    userPlayer->initUser(fieldSizes, shipsMap);
    dummyPlayer->initDummy(fieldSizes, shipsMap);
    GameState* beginingState = new GameState(userPlayer, dummyPlayer);
    defaultState = new GameState(userPlayer, dummyPlayer);
    
    mGame.setState(*beginingState);
    mGame.startGame();
    // mGame.currentState = beginingState;
}


void GameController::saveProgress()
{
    GameState* state = mGame.getState();
    mSaver->save(*state);
}

void GameController::loadProgress()
{
    GameState* state = mGame.getState();
    bool wasNotInit = false;
    if(state == nullptr)
    {
        wasNotInit = true;
        UserPlayer *userPlayer = new UserPlayer(*mMediator);
        DummyPlayer *dummyPlayer = new DummyPlayer(*mMediator);
        state = new GameState(userPlayer, dummyPlayer);
    }
    mSaver->load(*state);
    if(wasNotInit)
    {
        mGame.setState(*state);
    }
}

void GameController::setFieldData(std::pair<int, int> sizes)
{
    fieldSizes = sizes;
    sizesInit = true;
}

std::pair<int, int> GameController::getFieldSizes()
{
    if(sizesInit)
    {
        return fieldSizes;
    }
    return {0, 0};
}

void GameController::setShipsData(std::map<int, int> ships)
{
    shipsMap = ships;
    shipsInit = true;
}

void GameController::selectCommand(CommandArgs& args)
{
    Command* command = nullptr;
    switch (args.commandName)
    {
    case CommandArgs::CommandType::ATTACK:
    {
        if(&mGame.getAttacker() == mGame.getState()->getUser())
        {
            // std::cout << args.coordinates.first << " "<< args.coordinates.second;
        }
        // std::cout << ar << args.coordinates.first << " "<< args.coordinates.second;
        // std::cout << args.coordinates.second;
        command = new AttackCommand(args.coordinates.first, args.coordinates.second, mGame.getAttacker());
        break;
    }
    case CommandArgs::CommandType::ABILITY:
    {

        AbilityManager::AbilitiesCodes code = mGame.getAttacker().getAbManager().viewAvaliableAbilities();
        if(mGame.getAttacker().getProperties().abilityBlocked)
        {
            mGame.getAttacker().processAbilityResult(*(new TrollResult));    
            return;                                            
        }                                                   
        switch (code)                                       // if the top ability is scaner, so mb should move this check to mediator
        {
            case AbilityManager::AbilitiesCodes::SCANER:
            {
                command = new ScanerCommand(mGame.getTarget(), args.coordinates);
                break;
            }
            case AbilityManager::AbilitiesCodes::SHELLING:
            {
                command = new ShellingCommand(mGame.getTarget());
                break;
            }
            case AbilityManager::AbilitiesCodes::MASSIVE_ATTACK:
            {
                command = new MassiveAttackCommand(mGame.getAttacker());
                break;
            }
            default:
            {
                break;
            }
            break;
        } 
        break;
    }
    case CommandArgs::CommandType::PLACE:
    {
        
        command = new PlaceCommand(mGame.getAttacker(), args.coordinates, args.index, args.orientation);  
        break; 
    }
    case CommandArgs::CommandType::SAVE:
    {
        saveProgress();
        std::cout << "save OK ";
        break;
    }
    case CommandArgs::CommandType::LOAD:
    {
        loadProgress();
        std::cout << "load OK ";
        break;
    }
    case CommandArgs::CommandType::NEW_GAME:
    {
        initGame();
        break;
    }
    case CommandArgs::CommandType::QUIT:
    {
        interruptSignal = true;
        break;
    }

    default:
        break;
    }

    if(command != nullptr)
    {
        mGame.executeCommand(*command);
        delete command;
    }

    //runGame();
}


void GameController::controlGame()
{
    

    Player* currentAttacker = mGame.runGame(); 
    if(currentAttacker->isAlive())
    {
        return;
    }

    std::cout <<"winner detected ";
    if(currentAttacker == mGame.getState()->getUser())
    {  
        Player* loser = mGame.getState()->getUser();
        loser->processAttackResult(Field::Attack_Result::Defeat, true);
        loser->makeChoice();
    }
    else
    {
        currentAttacker->processAttackResult(Field::Attack_Result::Defeat, false);
        UserPlayer* copiedUser = new UserPlayer(*mGame.getState()->getUser());
        DummyPlayer *newDummy = new DummyPlayer(*mMediator);
        newDummy->initDummy(fieldSizes, shipsMap);
        GameState* newState = new GameState(copiedUser, newDummy);
        mGame.setState(*newState);
        mGame.startGame();
    }
}


