#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "Commands.h"
#include "../ShipManager.h"
#include "../Field.h"
#include "../AbilityManager.h"
#include "../Players/Player.h"


class GameObserver;

class Game
{
private:
    std::vector<GameObserver*> mObservers; 
    GameState* currentState = nullptr;
    Player* attacker = nullptr;
    Player* target = nullptr;
    int roundNumber = 0;

public:
    Game();
    ~Game();
public:
    void attackPlayer(int x, int y);
    void placeShip(Player& invoker,  int index, int x, int y, Battleship::Orientation orientation);
    void applyAbility(IAbilityArguments& args);
public:
    void setShipsData(std::map<int, int> shipsMap);
    void setFieldData(std::pair<int, int> sizes);
    void addObserver(GameObserver* observer);
    void startGame();
    Player* runGame();
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