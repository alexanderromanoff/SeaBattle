#ifndef COMMANDS_H
#define COMMANDS_H

// #include "Game.h"
#include <iostream>

class Game;
class Player;

class Command
{
public:
    virtual void execute(Game& game) = 0;
};

class AttackCommand : public Command
{
private:
    int x;
    int y;
    Player& attackerPlayer;
public:
    AttackCommand(int x, int y, Player& attackerPlayer);
    void execute(Game& game);
}; 

class MassiveAttackCommand : public Command
{
private:
    Player& invoker;
    
public:
    MassiveAttackCommand(Player& invoker);
    void execute(Game& game);
};

class ScanerCommand : public Command
{
private:
    Player& target;
    std::pair<int, int> coords;
    
public:
    ScanerCommand(Player& target, std::pair<int, int> coords);
    void execute(Game& game);
};

class ShellingCommand : public Command
{
private:
    Player& target;
public:
    ShellingCommand(Player& target);
    void execute(Game& game);
};

#endif