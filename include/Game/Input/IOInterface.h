#ifndef IOINTERFACE_H
#define IOINTERFACE_H

#include <string>
#include <iostream>
#include <map>
#include "../../Battleship.h"
#include "../../AbilityManager.h"
#include <sstream>


class IOInterface
{
public:
    virtual std::pair<int, int> readFieldSize() = 0;
    virtual std::map<int, int> readShipsMap() = 0;
    virtual std::pair<int, int> readCoordinates() = 0;
    virtual Battleship::Orientation readOrientation() = 0;
    virtual std::string readCommand() = 0;
    virtual int readShipIndex()= 0;
};

class IOConcrete : public IOInterface
{};

#endif
