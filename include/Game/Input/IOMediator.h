#ifndef IO_MEDIATOR_H
#define IO_MEDIIATOR_H

#include <string>
#include "ConsoleInput.h"
#include "DummyInput.h"
#include "../CommandArgs.h"
// #include "../../Players/UserPlayer.h"
// #include "../../Players/DummyPlayer.h"
#include "../../Players/Player.h"
#include "InputHandler.h"

class UserPlayer;
class DummyPlayer;

class IOMediator
{
public:
    virtual void callInput(Player* requester, Player::PlayerInputRequest reqType) = 0;
    virtual void callOutput(Player* requester, Player::PlayerInputRequest reqType, const std::vector<std::string> message) = 0;
    // virtual void configDevice(Player* requester, const std::vector<int> configData) = 0;
    virtual void setUserColleague(UserPlayer* uPlayer) = 0;
    virtual void setDummyColleague(DummyPlayer* dPlayer) = 0;
};

class ConcreteMediator : public IOMediator
{
private:
    // read it from file(?)
private:
    ConsoleInput& mUserDevice;
    DummyInput& mDummyDevice;
    InputHandler& mHandler;
    UserPlayer* userColleague;
    DummyPlayer* dummyColleague;
public:
    ConcreteMediator(ConsoleInput& userDev, DummyInput& dumbDev, InputHandler& inpHandler);
    void callInput(Player* requester, Player::PlayerInputRequest reqType);
    void callOutput(Player* requester, Player::PlayerInputRequest reqType, const std::vector<std::string> message);
    void setUserColleague(UserPlayer* uPlayer);
    void setDummyColleague(DummyPlayer* dPlayer);
};



#endif