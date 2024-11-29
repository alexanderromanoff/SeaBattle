#include "../include/Game/Input/ConsoleInput.h"
#include <limits>

std::pair<int, int> ConsoleInput::readFieldSize()
{
    int hor;
    int ver;
    std::cout << "enter field sizes (horizontal and vertical)\n";
    std::cin >> hor >> ver;
    return {hor, ver};
}
std::map<int, int> ConsoleInput::readShipsMap()
{
    std::map<int, int> shipsMap;
    for(int i = 1; i < 5; i++)
    {
        int num;
        std::cout << "enter number of ships size " << i <<"\n";
        std::cin >> num;
        shipsMap.insert({i, num});
    }
    return shipsMap;
}
std::pair<int, int> ConsoleInput::readCoordinates()
{
    int x; 
    int y;
    std::cout << "enter x and y\n";
    std::cin >> x >> y;
    return {x, y};
}

std::pair<int, int> ConsoleInput::readShipPlacement(int size)
{
    std::cout << "placing ship of size " << size << "\n";
    return readCoordinates();
}

Battleship::Orientation ConsoleInput::readOrientation()
{
    std::string inp;
    std::cout << "enter ship orientation\n";
    std::cin >> inp;
    if(inp[0] == 'v')
    {
        return Battleship::Orientation::VERTICAL;
    }
    return Battleship::Orientation::HORIZONTAL;
}
std::string ConsoleInput::readCommand()
{
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string command;
    std::cout << "enter command: ";

    std::getline(std::cin, command);

    return command;
}

void ConsoleInput::viewInfo(int code)
{
    switch (code)
    {
    case 0:
        std::cout << "Massive attack\n";
        break;


    case 1:
        std::cout << "Shelling\n";
        break;

    case 2:
        std::cout << "Scaner\n";
        break;
    
    default:
        break;
    }
}

void ConsoleInput::writeRes(std::string res)
{
    std::cout << res;
}