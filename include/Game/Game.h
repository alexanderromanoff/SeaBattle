#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "Commands.h"


class Game
{
private:
    GameState* currentState = nullptr;
    Player* attacker = nullptr;
    Player* target = nullptr;
    int roundNumber = 0;
public:
    Game() = default;
    ~Game();
    void attackPlayer(int x, int y);
    void placeShips(Player& invoker);
    void applyAbility(IAbilityArguments& args);
    void setState(GameState& state);
    void setAttacker(Player& player);
    void setTarget(Player& player);
    void playRound();
    void executeCommand(Command& command);
    GameState* getState();
    Player& getTarget();
    Player& getAttacker();
};

#endif