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
}


void GameController::setChoice()
{
    UserPlayer placeholder = UserPlayer(*mMediator);
    placeholder.connectToMediator();
    placeholder.makeChoice();

}


void GameController::initGame()
{
    UserPlayer *userPlayer = new UserPlayer(*mMediator);
    DummyPlayer *dummyPlayer = new DummyPlayer(*mMediator);
    userPlayer->initUser(fieldSizes, shipsMap);
    dummyPlayer->initDummy(fieldSizes, shipsMap);
    userPlayer->connectToMediator();
    dummyPlayer->connectToMediator();
    GameState* beginingState = new GameState(userPlayer, dummyPlayer);
    mGame.startGame(*beginingState);
}


void GameController::saveProgress()
{
    Saver* saver = new Saver(savePath);
    GameState* state = mGame.getState();
    saver->save(*state);
    delete saver;
}

void GameController::loadProgress()
{
    Saver* saver = new Saver(savePath);
    UserPlayer *userPlayer = new UserPlayer(*mMediator);
    DummyPlayer *dummyPlayer = new DummyPlayer(*mMediator);
    GameState* state = new GameState(userPlayer, dummyPlayer);
    try
    {
        saver->load(*state);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        delete saver;
        return;
    }
    if(!sizesInit)
    {
        int height = userPlayer->getField().getHeight();
        int width =  userPlayer->getField().getWidth();
        setFieldData({height, width});
    }
    if(!shipsInit)
    {
        std::map<int, int> shipsSet = userPlayer->getSetOfShips();
        setShipsData(shipsSet);
    }
    userPlayer->connectToMediator();
    dummyPlayer->connectToMediator();
    delete saver;
    mGame.startGame(*state);

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
        switch (code)                                    
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

    std::cout <<" ";

    if(currentAttacker == mGame.getState()->getUser())
    {  
        Player* loser = mGame.getState()->getUser();
        loser->processAttackResult(Field::Attack_Result::Defeat, true);
        loser->makeChoice();
    }
    else
    {
        Player* winner = mGame.getState()->getUser();
        winner->processAttackResult(Field::Attack_Result::Defeat, false);
        UserPlayer* copiedUser = new UserPlayer(*mGame.getState()->getUser());
        DummyPlayer* newDummy = new DummyPlayer(*mMediator);
        newDummy->initDummy(fieldSizes, shipsMap);

        copiedUser->connectToMediator();
        newDummy->connectToMediator();
        GameState* newState = new GameState(copiedUser, newDummy);
        mGame.startGame(*newState);
        // mGame.startGame();
    }
}


