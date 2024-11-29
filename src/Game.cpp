#include "../include/Game/Game.h"


void Game::attackPlayer(int x, int y)
{
    Field& targetField = target->getField();
    int attackPower = attacker->getProperties().attackPower;

    Field::Attack_Result atkRes = targetField.attackCell(x, y, attackPower);
    attacker->processAttackResult(atkRes, false);
    target->processAttackResult(atkRes, true);
    roundNumber++;
    std::swap(attacker, target);
}

void Game::applyAbility(IAbilityArguments& args)
{
    IAbilityResult& result = attacker->getAbManager().useAbility(args);
    attacker->processAbilityResult(result);
}

void Game::placeShips(Player& invoker)
{
    invoker.placeShips();
}

void Game::setState(GameState& state)
{
    currentState = &state;
}

// void Game::startGame()
// {}

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