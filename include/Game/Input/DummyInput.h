#ifndef DUMMY_INPUT_H
#define DUMMY_INPUT_H

#include "IOInterface.h"

class DummyInput : public IOInterface
{
private:
    int horBound;
    int verBound;
    int curShipIndex = 0;
    
public:
    std::pair<int, int> readFieldSize();
    std::map<int, int> readShipsMap();
    std::pair<int, int> readCoordinates();
    Battleship::Orientation readOrientation();
    std::string readCommand();
    int readShipIndex();
    
    // void getFromBot(int x, int y);

    void setInfo(std::vector<std::string>); // DummyInput ONLY, mediator will know the type of device

};


#endif