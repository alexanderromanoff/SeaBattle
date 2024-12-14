#ifndef CONSOLE_DISPLAYER_H
#define CONSOLE_DISPLAYER_H

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "GameDisplayer.h"

class ConsoleDisplayer
{
private:
    std::ofstream console;
    void drawFieldLine(Field& fieldToDraw, int numberOfLine, bool hide);
public:
    ConsoleDisplayer(const std::string& terminalPath);
    ~ConsoleDisplayer();
    void writeName(std::string name);
    void drawField(Field& userField, Field& botField);
    void drawShipManager(ShipManager& shaManToDraw);
    void drawAbilityManager(AbilityManager& abManToDraw);
};

#endif