#include "../include/Game/SaveLoad/StringOperator.h"


std::string StringOperator::toStringField(Field& field)
{
    std::string stateString;

    std::vector<std::vector<Field::Cell::CELL_STATES>> cellStates = field.getCellStates();
    for(int i = 0; i < field.getHeight(); i++)
    {
        for(int j = 0; j < field.getWidth(); j++)
        {
            Field::Cell::CELL_STATES state = cellStates[i][j];
            switch (state)
            {
            case Field::Cell::CELL_STATES::UNKNOWN:
                stateString += "0";
                break;
            case Field::Cell::CELL_STATES::EMPTY:
                stateString += "1";
                break;
            case Field::Cell::CELL_STATES::SHIP_EXISTS:
                stateString += "2";
                break;
            case Field::Cell::CELL_STATES::SHIP_DAMAGED:
                stateString += "3";
                break;
            case Field::Cell::CELL_STATES::SHIP_DESTROYED:
                stateString += "4";
                break;
            default:
                break;
            }
            
        }
    }
    return stateString;
}
std::string StringOperator::toStringShips(Field& field)
{
    std::string shipsString;

    std::map<std::pair<int, int>, Battleship*> fieldShips = field.getShips();
    for(auto & item : fieldShips)
    {
        shipsString += std::to_string(item.first.first) + "\n";
        shipsString += std::to_string(item.first.second) + "\n";
        Battleship* ship = item.second;
        Battleship::Orientation ornt = ship->getOrientation();
        shipsString += std::to_string(ship->getNumberOfSegments());
        if (ornt == Battleship::Orientation::VERTICAL)
        {
            shipsString += "1";
        }
        else
        {
            shipsString += "2";
        }
        for(int i = 0; i < ship->getNumberOfSegments(); i++)
        {
            shipsString += std::to_string(ship->getSegmentHealth(i));
        }
        shipsString += "\n";
    }
    return shipsString;

}
std::string StringOperator::toStringAbMan(AbilityManager& abMan)
{
    std::string abilityString;
    std::queue<AbilityManager::AbilitiesCodes> abQueue = abMan.getInfo();
    if(abQueue.size() == 0)
    {
        abilityString += "3\n";
        return abilityString;
    }
    while(abQueue.size() > 0)
    {
        abilityString += std::to_string(abQueue.front());
        abQueue.pop();
    }
    abilityString += "\n";
    return abilityString;
}

Field& StringOperator::initFromStringField(std::string info, Field& field)
{
    std::vector<std::vector<Field::Cell::CELL_STATES>> cellStates = field.getCellStates();
    for(int i = 0; i < field.getHeight(); i++)
    {
        for(int j = 0; j < field.getWidth(); j++)
        {
            char state = info[i*j + j];
            switch (state)
            {
            case '0':
                cellStates[i][j] = Field::Cell::CELL_STATES::UNKNOWN;
                break;
            case '1':
                cellStates[i][j] = Field::Cell::CELL_STATES::EMPTY;
                break;
            case '2':
                cellStates[i][j] = Field::Cell::CELL_STATES::SHIP_EXISTS;
                break;
            case '3':
                cellStates[i][j] = Field::Cell::CELL_STATES::SHIP_DAMAGED;
                break;
            case '4':
                cellStates[i][j] = Field::Cell::CELL_STATES::SHIP_DESTROYED;
                break;
            default:
                break;
            }
            
        }
    }
    field.setCellStates(cellStates);
    return field;
}

ShipManager& StringOperator::initFromStringShips(std::string info, Field& field, ShipManager& shMan)
{
    std::istringstream stream (info);
    std::string line;
    while(std::getline(stream, line)) // get Xcoord
    {
        int xCoord = std::stoi(line);
        std::getline(stream, line); // get yCoord
        int yCoord = std::stoi(line);
        std::getline(stream, line); // get ship info
        std::string shipInfo = line;
        Battleship& newShip = buildShip(shipInfo);
        field.placeShip(newShip, xCoord, yCoord, newShip.getOrientation());
        shMan.addShip(newShip);
    } 
    return shMan;

}

AbilityManager& StringOperator::initFromStringAbMan(std::string info, AbilityManager& abMan)
{
    std::queue<AbilityManager::AbilitiesCodes> abQueue;
    for(int i = 0; i < info.size(); i++)
    {
        switch (info[i])
        {
        case '0':
            abQueue.push(AbilityManager::AbilitiesCodes::MASSIVE_ATTACK);
            break;
        case '1':
            abQueue.push(AbilityManager::AbilitiesCodes::SHELLING);
            break;
        case '2':
            abQueue.push(AbilityManager::AbilitiesCodes::SCANER);
            break;
        default:
            break;
        }
    }
    abMan.setInfo(abQueue);
    return abMan;
}

Battleship& StringOperator::buildShip(const std::string& shipInfo)
{
    int shipSize = shipInfo[0] - '0';
    int numOrientation = shipInfo[1] - '0';
    Battleship::Orientation shipOrientation = Battleship::Orientation::HORIZONTAL;
    if(numOrientation == 2)
    {
        shipOrientation = Battleship::Orientation::VERTICAL;
    }
    Battleship* shipObject = new Battleship(shipSize);
    shipObject->setOrientation(shipOrientation);
    for(int i = 2; i < shipSize + 2; i++)
    {
        int health = shipInfo[i] - '0';
        shipObject->setSegmentHealth(i - 2, health);
    }
    return *shipObject;
}
