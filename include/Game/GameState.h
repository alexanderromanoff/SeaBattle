#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <sstream>
#include "../Players/DummyPlayer.h"
#include "../Players/UserPlayer.h"


class GameState
{
private:
    UserPlayer* userPlayer = nullptr;
    DummyPlayer* dummyPlayer = nullptr;

public:
    GameState(UserPlayer* uPlayer, DummyPlayer* dPlayer);
    UserPlayer& getUser();
    DummyPlayer& getDummy();
    std::string getUserInfo() const;
    std::string getDummyInfo() const;

    void parseInfo(const std::string& info);
    Field* buildField(std::istringstream& stream);
    ShipManager* buildShManager(std::istringstream& stream, Field* field);
    AbilityManager* buildAbManager(std::istringstream& stream);
    Battleship& buildShip(const std::string& shipInfo);


    friend std::ostream& operator<<(std::ostream& os, const GameState& gState);
    friend std::istream& operator>>(std::istream& is, GameState& gState);
};

#endif
