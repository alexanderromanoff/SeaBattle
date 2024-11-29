#ifndef IOINTERFACE_H
#define IOINTERFACE_H

#include <string>
#include <iostream>
#include <map>
#include "../../Battleship.h"


class IOInterface
{
public:
    virtual std::pair<int, int> readFieldSize() = 0;
    virtual std::map<int, int> readShipsMap() = 0;
    virtual std::pair<int, int> readCoordinates() = 0;
    virtual Battleship::Orientation readOrientation() = 0;
    virtual std::string readCommand() = 0;
    virtual void viewInfo(int code) = 0;
};

#endif
