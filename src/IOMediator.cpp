#include "../include/Game/Input/IOMediator.h"
#include "../include/Players/UserPlayer.h"
#include "../include/Players/DummyPlayer.h"


ConcreteMediator::ConcreteMediator(IOInterface& userDev, IOInterface& dumbDev, InputHandler& inpHandler) :
mUserDevice(userDev), mDummyDevice(dumbDev), mHandler(inpHandler) {}

void ConcreteMediator::callInput(Player* requester, Player::PlayerInputRequest reqType)
{
    if(requester == userColleague)
    {
        switch (reqType)
        {
        case Player::PlayerInputRequest::PLACE_SHIP:
        {
            mHandler.newArgs();
            mHandler.setCommandExplicitly(CommandArgs::CommandType::PLACE);
            
            int index = requester->getPlIndex();
            int size = requester->getShManager().getShipAtIndex(index).getNumberOfSegments();
            mHandler.handleIndex(userColleague, index);

            mUserDevice.writeInfo("Размещаем корабль размером " + std::to_string(size));

            std::pair<int, int> coords = mUserDevice.readCoordinates();
            while(!mHandler.handleCoordinates(userColleague, coords))
            {
                mUserDevice.writeInfo("неверные координаты, ты балбес ");
                coords = mUserDevice.readCoordinates();   
            }
            Battleship::Orientation ornt = mUserDevice.readOrientation();
            mHandler.handleOrientation(userColleague, ornt);

            mHandler.runContr();
            
            return;
        }
        case Player::PlayerInputRequest::COMMAND:
        {
            mHandler.newArgs();

            std::string commandName = mUserDevice.readCommand();
            CommandArgs::CommandType commandType = mHandler.handleCommandName(userColleague, commandName);

            while (commandType == CommandArgs::CommandType::NONE)
            {
                mUserDevice.writeInfo("нет такой команды, ты балбес");
                commandName = mUserDevice.readCommand();
                commandType = mHandler.handleCommandName(userColleague, commandName);
            }

            switch (commandType)
            {
                case CommandArgs::CommandType::ATTACK:
                {                     
                    std::pair<int, int> coords = mUserDevice.readCoordinates();
                    while(!mHandler.handleCoordinates(userColleague, coords))
                    {
                        mUserDevice.writeInfo("неверные координаты, ты балбес ");
                        coords = mUserDevice.readCoordinates();
                    }
                    mHandler.runContr();
                    return;
                }

                case CommandArgs::CommandType::ABILITY:
                {
                    if(userColleague->getProperties().abilityBlocked)
                    {
                        mHandler.runContr();
                        return;
                    }
                    if(userColleague->getAbManager().viewAvaliableAbilities() == AbilityManager::AbilitiesCodes::SCANER)
                    {
                        std::pair<int, int> coords = mUserDevice.readCoordinates();
                        while(!mHandler.handleCoordinates(userColleague, coords))
                        {
                            mUserDevice.writeInfo("неверные координаты, ты балбес ");
                            coords = mUserDevice.readCoordinates();
                        }
                    }
                    mHandler.runContr();
                    return;
                }

                case CommandArgs::CommandType::SAVE:
                {
                    mHandler.runContr();
                    return;
                }

                case CommandArgs::CommandType::LOAD:
                {
                    mHandler.runContr();
                    return;
                }

                case CommandArgs::CommandType::INFO:
                {
                    switch (requester->getAbManager().viewAvaliableAbilities())
                    {
                    case 0:
                        mUserDevice.writeInfo("Massive attack\n");
                        break;
                    case 1:
                        mUserDevice.writeInfo("Shelling\n");
                        break;

                    case 2:
                        mUserDevice.writeInfo( "Scaner\n");
                        break;
                    
                    case 3:
                        mUserDevice.writeInfo("No ablities\n");
                        break;

                    default:
                        break;
                    }
                    return;
                }

                case CommandArgs::CommandType::QUIT:
                {
                    // exit(0);
                    mHandler.runContr();
                    return;
                }
                
                default:
                {
                    mUserDevice.writeInfo("невозможно применить эту команду сейчас ");
                    return;
                }
            }
            return;
        }

        case Player::PlayerInputRequest::MAKE_CHOICE:
        {
            mHandler.newArgs();
            mUserDevice.writeInfo("Сделайте выбор ");
            std::string commandName = mUserDevice.readCommand();
            bool validChoice = mHandler.handleGameStart(userColleague, commandName);
            CommandArgs::CommandType commandType = mHandler.handleCommandName(userColleague, commandName);
            while(!validChoice)
            {
                mUserDevice.writeInfo("нельзя применить эту команду сейчас ");
                commandName = mUserDevice.readCommand();
                validChoice = mHandler.handleGameStart(userColleague, commandName);
                commandType = mHandler.handleCommandName(userColleague, commandName);
            }
            
            switch (commandType)
            {
                case CommandArgs::CommandType::NEW_GAME:
                {
                    std::pair<int, int> fieldSizes = mUserDevice.readFieldSize();

                    while(!mHandler.handleFieldSize(userColleague, fieldSizes))
                    {
                        mUserDevice.writeInfo("неверный размер поля, ты балбес ");
                        fieldSizes = mUserDevice.readFieldSize();
                    }
                    std::map<int, int> shipsMap = mUserDevice.readShipsMap();


                    while(!mHandler.handleShipsMap(userColleague, shipsMap))
                    {
                        mUserDevice.writeInfo("неверное количество кораблей, ты балбес ");
                        shipsMap = mUserDevice.readShipsMap();
                    }
                    mHandler.runContr();
                    return;
                }

                case CommandArgs::CommandType::LOAD:
                {
                    mHandler.runContr();
                    return;
                }
                case CommandArgs::QUIT:
                {
                    // exit(0);
                    mHandler.runContr();
                    return;
                }

                default:
                {
                    mUserDevice.writeInfo("невозможно применить эту команду сейчас ");
                    return;
                }  
            }
            return;
        }
  
        default:
        {
            std::cout << "what the flip\n";
            return;
        }
        }
    }
    else if(requester == dummyColleague)
    {
                    
        switch (reqType)
        {
        case Player::PlayerInputRequest::PLACE_SHIP:
        {   
            mHandler.newArgs();
            mHandler.setCommandExplicitly(CommandArgs::CommandType::PLACE);
            int index = requester->getPlIndex();
            mHandler.handleIndex(dummyColleague, index);
            std::pair<int, int> coords = mDummyDevice.readCoordinates();
            coords.first %= requester->getField().getWidth();
            coords.second %= requester->getField().getHeight();
            while(!mHandler.handleCoordinates(dummyColleague, coords))
            {
                coords = mDummyDevice.readCoordinates();   
            }
            Battleship::Orientation ornt = mDummyDevice.readOrientation();
            mHandler.handleOrientation(dummyColleague, ornt);
            mHandler.runContr();

            return;
        }
        case Player::PlayerInputRequest::COMMAND:
        {
            mHandler.newArgs();
            mHandler.setCommandExplicitly(CommandArgs::CommandType::ATTACK);
            // mUserDevice.writeInfo("бот думает...");
            std::pair<int, int> coords = mDummyDevice.readCoordinates();
            while(!mHandler.handleCoordinates(dummyColleague, coords))
            {
                coords = mDummyDevice.readCoordinates(); 
                coords.first %= requester->getField().getWidth();
                coords.second %= requester->getField().getHeight();   
            }
            mHandler.runContr();
            return;
        }
        case Player::PlayerInputRequest::MAKE_CHOICE:
        {
            mHandler.handleFieldSize(dummyColleague,mDummyDevice.readFieldSize());

            mHandler.handleShipsMap(dummyColleague, mDummyDevice.readShipsMap());
            return;
        }

        default:
            return;
        }
    }
}

void ConcreteMediator::callOutput(Player* requester, Player::PlayerInputRequest reqType, const std::vector<std::string> message)
{
    if(requester == userColleague)
    {
        for(auto& item: message)
        {
            mUserDevice.writeInfo(item);
        }
        
    }

    else if(requester == dummyColleague)
    {
        switch (reqType)
        {
        case Player::PlayerInputRequest::INFO:
        {
            for(auto& item: message)
            {
                mUserDevice.writeInfo(item);
            }
            return;
        }
        default:
            return;
        }
    }
}

void ConcreteMediator::setDummyColleague(DummyPlayer* dPlayer)
{
    dummyColleague = dPlayer;
}

void ConcreteMediator::setUserColleague(UserPlayer* uPlayer)
{
    userColleague = uPlayer;
}