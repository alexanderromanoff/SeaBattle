#include "../include/Game/GameState.h"
#include "../include/Players/DummyPlayer.h"
#include "../include/Players/UserPlayer.h"

GameState::GameState(UserPlayer* uPlayer, DummyPlayer* dPlayer) : userPlayer(uPlayer), dummyPlayer(dPlayer) {}

UserPlayer& GameState::getUser()
{
    return *userPlayer;
}

DummyPlayer& GameState::getDummy()
{
    return *dummyPlayer;
}

std::string GameState::getUserInfo() const
{
    std::string uInfo;
    uInfo += userPlayer->getField().getFieldMap();
    uInfo += userPlayer->getAbManager().getInfo();
    uInfo += userPlayer->getField().getShips();
    return uInfo;

}
std::string GameState::getDummyInfo() const
{
    std::string dInfo;
    dInfo += dummyPlayer->getField().getFieldMap();
    dInfo += dummyPlayer->getField().getShips();
    return dInfo;
}

void GameState::parseInfo(const std::string& info)
{
        std::istringstream stream(info);

        Field* uField = buildField(stream);
        AbilityManager* uAbManager = buildAbManager(stream);
        ShipManager* uShipManager = buildShManager(stream, uField);
        userPlayer->initUser(uField, uShipManager);

        Field* dField = buildField(stream);
        ShipManager* dShipManager = buildShManager(stream, dField);
        dummyPlayer->initDummy(dField, dShipManager);
}

Field* GameState::buildField(std::istringstream& stream)
{
    std::string line;
    std::getline(stream, line);

    int height = std::stoi(line);
    std::getline(stream, line);

    int width = std::stoi(line);
    Field* field = new Field(height, width);

    std::getline(stream,  line);
    field->setFieldMap(line);
    return field;
}

ShipManager* GameState::buildShManager(std::istringstream& stream, Field* field)
{
    std::map<int, int> empty;
    empty.insert({1, 0});
    ShipManager* shManager = new ShipManager(empty);
    std::string line;
    std::getline(stream, line); // get the first xCoord
    while(line != "end")
    {

        int xCoord = std::stoi(line);
        std::getline(stream, line); // get yCoord

        int yCoord = std::stoi(line);
        std::getline(stream, line); // get ship info
        std::string shipInfo = line;

        Battleship& newShip = buildShip(shipInfo);
        field->placeShip(newShip, xCoord, yCoord, newShip.getOrientation());
        shManager->addShip(newShip);

        std::getline(stream, line); // get new x or find "end"
    }
    return shManager;
}

AbilityManager* GameState::buildAbManager(std::istringstream& stream)
{
    std::string line;
    std::getline(stream, line);
    AbilityManager* abManager = new AbilityManager;
    abManager->setInfo(line);
    return abManager;
}

Battleship& GameState::buildShip(const std::string& shipInfo)
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
    for(int i = 2; i < shipSize; i++)
    {
        int health = shipInfo[i] - '0';
        shipObject->setSegmentHealth(i - 2, health);
    }
    return *shipObject;
}

std::ostream& operator<<(std::ostream& os, const GameState& gState)
{
    os << gState.getUserInfo() << gState.getDummyInfo();
    return os;
}

std::istream& operator>>(std::istream& is, GameState &gState){
    std::ostringstream buffer;
    std::string line;
    while(std::getline(is, line))
    {
        buffer << line << "\n";
    }
    gState.parseInfo(buffer.str());
    return is;
}