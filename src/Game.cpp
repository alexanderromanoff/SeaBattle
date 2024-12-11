#include "../include/Game/Game.h"
#include "../include/Game/Display/GameObserver.h"
#include "../include/Players/UserPlayer.h"
#include "../include/Players/DummyPlayer.h"


Game::Game() 
{
    mObservers.resize(0);
}

void Game::attackPlayer(int x, int y)
{
    Field& targetField = target->getField();
    // int attackPower = attacker->getProperties().attackPower; // return this back
    // game displayer should be HERE!

    Field::Attack_Result atkRes = targetField.attackCell(x, y, 1);
    attacker->processAttackResult(atkRes, false);
    target->processAttackResult(atkRes, true);
    if(atkRes != Field::Attack_Result::Invalid)
    {
        std::swap(attacker, target);
        for(int i = 0; i < mObservers.size(); i++)
        {
            mObservers[i]->handleEvent(*getState());
        }
    }
    
    
    
}

void Game::addObserver(GameObserver* observer)
{
    mObservers.push_back(observer);
}


void Game::applyAbility(IAbilityArguments& args)
{
    IAbilityResult& result = attacker->getAbManager().useAbility(args);
    attacker->processAbilityResult(result);
}

void Game::placeShip(Player& invoker,  int index, int x, int y, Battleship::Orientation orientation)
{

    Field& field = invoker.getField();
    Battleship& ship = invoker.getShManager().getShipAtIndex(index);
    field.placeShip(ship, x, y, orientation);
    if(&invoker == currentState->getUser())
    {
        for(int i = 0; i < mObservers.size(); i++)
        {
            mObservers[i]->handleEvent(*getState());
        }
    }
}

void Game::setState(GameState& state)
{
    if (currentState != nullptr)
    {
         delete currentState;
    }

    currentState = &state;
    roundNumber++;
    // if (roundNumber > 4)
    // {
    //     exit(69);
    // }
}

void Game::startGame()
{
    if(currentState == nullptr)
    {
        throw std::runtime_error("game not init");
    }

    DummyPlayer& dPlayer = *currentState->getDummy();
    UserPlayer& uPlayer = *currentState->getUser();
    
    if(!dPlayer.isInit())
    {
        setAttacker(dPlayer);
        dPlayer.placeShips();
    }
    if(!uPlayer.isInit())
    {
        setAttacker(uPlayer);
        uPlayer.placeShips();
    }
    setAttacker(uPlayer);
    setTarget(dPlayer); // nice take)))) if user is init
                        // bot starts a war with itself
    
}

Player* Game::runGame()
{
    // while(1)
    // {
    
    //     if(!target->isAlive())
    //     {
    //        break;
    //     }
    // }
    playRound();
    return &getAttacker();
    
}

void Game::playRound()
{
    attacker->makeMove();
}

void Game::executeCommand(Command& command)
{
    command.execute(*this);
}

GameState* Game::getState()
{
    return currentState;
}

Player& Game::getAttacker()
{
    return *attacker;
}

Player& Game::getTarget()
{
    return *target;
}

void Game::setAttacker(Player& player)
{
    attacker = &player;
}

void Game::setTarget(Player& player)
{
    target = &player;
}

Game::~Game()
{
    delete currentState;
}