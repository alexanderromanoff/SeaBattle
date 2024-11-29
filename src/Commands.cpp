#include "../include/Game/Commands.h"
#include "../include/Game/Game.h"

AttackCommand::AttackCommand(int x, int y, Player& invoker) : attackerPlayer(invoker), x(x), y(y) {}

void AttackCommand::execute(Game& game)
{
    game.attackPlayer(x, y);
}

MassiveAttackCommand::MassiveAttackCommand(Player& invoker) : invoker(invoker) {}

void MassiveAttackCommand::execute(Game& game)
{
    IAbilityArguments* args = new MassiveAttackArgs(&invoker.getProperties());
    game.applyAbility(*args);
}


ScanerCommand::ScanerCommand(Player& target, std::pair<int, int> coords) : coords(coords), target(target) {}

void ScanerCommand::execute(Game& game)
{
    IAbilityArguments* args = new ScanerArgs(coords, &target.getField());
    game.applyAbility(*args);
}

ShellingCommand::ShellingCommand(Player& target) : target(target) {}

void ShellingCommand::execute(Game& game)
{
    IAbilityArguments* args = new ShellingArgs(&target.getShManager());
    game.applyAbility(*args);
}