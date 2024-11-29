#ifndef DUMMY_INPUT_H
#define DUMMY_INPUT_H

#include "IOInterface.h"

class DummyInput : public IOInterface
{
private:
    int x;
    int y;
    
public:
    std::pair<int, int> readFieldSize();
    std::map<int, int> readShipsMap();
    std::pair<int, int> readCoordinates();
    Battleship::Orientation readOrientation();
    std::string readCommand();
    void getFromBot(int x, int y);
    void viewInfo(int code);
};


#endif