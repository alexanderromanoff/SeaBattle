#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include "IOInterface.h"

class ConsoleInput : public IOInterface
{
public:
    std::pair<int, int> readFieldSize();
    std::map<int, int> readShipsMap();
    std::pair<int, int> readCoordinates();
    Battleship::Orientation readOrientation();
    std::string readCommand();
    std::pair<int, int> readShipPlacement(int size);
    void viewInfo(int code);
    void writeRes(std::string);
};

#endif