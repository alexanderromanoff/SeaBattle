#include "../include/Game/Input/DummyInput.h"

std::pair<int, int> DummyInput::readFieldSize()
{
    return {10, 10};
}
std::map<int, int> DummyInput::readShipsMap()
{
    std::map<int, int> shipsMap;
    shipsMap.insert({1, 4});
    shipsMap.insert({2, 3});
    shipsMap.insert({3, 2});
    shipsMap.insert({4, 1});
    return shipsMap;
}
std::pair<int, int> DummyInput::readCoordinates()
{
    return {x, y};
}
Battleship::Orientation DummyInput::readOrientation()
{
    int val = rand() % 2;
    if(val == 1)
    {
        return Battleship::Orientation::VERTICAL;
    }
    return Battleship::Orientation::HORIZONTAL;
}
std::string DummyInput::readCommand()
{
    std::string command = "ATK ";
    std::pair<int, int> atkCoords = readCoordinates();
    command += std::to_string(atkCoords.first) + " " + std::to_string(atkCoords.second);
    return command;
}

void DummyInput::getFromBot(int x, int y)
{
    this->x = x;
    this->y = y;
}

void DummyInput::viewInfo(int code)
{}