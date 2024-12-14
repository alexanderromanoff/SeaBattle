#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "IOInterface.h"

class ConsoleInput //: public IOInterface
{
private:
    std::fstream console;

public:
    ConsoleInput(const std::string& terminalPath);
    std::pair<int, int> readFieldSize();
    std::map<int, int> readShipsMap();
    std::pair<int, int> readCoordinates();
    Battleship::Orientation readOrientation();
    std::string readCommand();
    // int readShipIndex();

    void viewAbility(AbilityManager::AbilitiesCodes code); 
    void writeInfo(std::string); 
    
};

#endif