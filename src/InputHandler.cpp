#include "../include/Game/Input/InputHandler.h"
#include "../include/Game/GameController.h"

 // method_check_inp(Player& pl, type& type_of_inp) <- called by mediator 


InputHandler::InputHandler(GameController& contr) : mController(contr) {}

void InputHandler::newArgs()
{
    delete currentComArgs;
    currentComArgs = new CommandArgs;
}

bool InputHandler::handleFieldSize(Player* player, std::pair<int, int> sizes)
{
    if(sizes.first > MAX_FIELD_SIZE || sizes.first < MIN_FIELD_SIZE)
    {
        // throw std::invalid_argument("wrong sizes");
        return false;
    }
    if(sizes.second > MAX_FIELD_SIZE || sizes.second < MIN_FIELD_SIZE)
    {
        // throw std::invalid_argument("wrong sizes");
        return false;
    }
    mController.setFieldData(sizes); // move controller CALLS TO MEDIATOR CLASS or not
    return true;
}

bool InputHandler::handleShipsMap(Player* player, std::map<int,  int> shipsMap)
{
    std::pair<int, int> fieldSizes = mController.getFieldSizes();
    int fieldArea = fieldSizes.first * fieldSizes.second;
    int totalShipsArea = 0;
    for(auto& item : shipsMap)
    {
        totalShipsArea += item.first * item.second;
        if(item.second < 0 || item.second > 4) // change to constants
        {
            return false;
        }
    }

    if(fieldArea/totalShipsArea < 5)
    {
        return false;
    }

    mController.setShipsData(shipsMap); // move controller CALLS TO MEDIATOR CLASS
    return true;
}

bool InputHandler::handleCoordinates(Player* player, std::pair<int,  int> coords)
{
    if(coords.first > player->getField().getWidth() || coords.first < 0)
    {
        // throw std::invalid_argument("invalid coordinates");
        return false;
    }
    if(coords.second > player->getField().getHeight() || coords.second < 0)
    {
        // throw std::invalid_argument("invalid coordinates");
        return false;
    }
    currentComArgs->coordinates = coords;
    return true;
}

CommandArgs::CommandType InputHandler::handleCommandName(Player* player, std::string commandStr)
{
    if(inputMap.find(commandStr) == inputMap.end())
    {
        return CommandArgs::CommandType::NONE;
    }
    currentComArgs->commandName = inputMap[commandStr];
    return currentComArgs->commandName;
}

bool InputHandler::handleGameStart(Player* player, std::string startCommandStr)
{
    CommandArgs::CommandType choice = handleCommandName(player, startCommandStr);
    if (choice == CommandArgs::CommandType::NEW_GAME || 
        choice == CommandArgs::CommandType::LOAD ||
        choice == CommandArgs::CommandType::QUIT)
    {
        return true;
    }
    return false;
}

bool InputHandler::handleIndex(Player* player, int index)
{
    if(index < 0 || index > player->getShManager().getNumberOfShips() - 1)
    {
        // std::cout << index << "\n";
        std::cout <<player->getShManager().getNumberOfShips() - 1;
        return false;
    }
    currentComArgs->index = index;
    return true;
}

bool InputHandler::handleOrientation(Player* player, Battleship::Orientation orientation)
{
    currentComArgs->orientation = orientation;
    return true;
}

void InputHandler::runContr()
{
    mController.selectCommand(*currentComArgs);
}
