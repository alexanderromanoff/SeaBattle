#include "../include/Game/Input/ConsoleInput.h"
#include <limits>


ConsoleInput::ConsoleInput(const std::string& terminalPath)
{
    // console.open(terminalPath, std::ios::in | std::ios::out);
    // if (!console.is_open()) 
    // {
    //     throw std::runtime_error("Failed to open terminal: " + terminalPath);
    // }
}

std::pair<int, int> ConsoleInput::readFieldSize()
{
    int hor, ver;
        std::string input;
        while (true) {
            std::cout << "Enter field sizes (horizontal and vertical): ";
            if (std::getline(std::cin, input)) {
                std::istringstream iss(input);
                if (iss >> hor >> ver && iss.eof() && hor > 0 && ver > 0) {
                    break;
                }
            }
            std::cout << "Invalid input. Please enter two positive integers.\n";
        }
        return {hor, ver};
}
std::map<int, int> ConsoleInput::readShipsMap()
{
        std::map<int, int> shipsMap;
        for (int i = 1; i < 5; i++) {
            int num;
            std::string input;
            while (true) {
                std::cout << "Enter number of ships of size " << i << ": ";
                if (std::getline(std::cin, input)) {
                    std::istringstream iss(input);
                    if (iss >> num && iss.eof() && num >= 0) {
                        shipsMap[i] = num;
                        break;
                    }
                }
                std::cout << "Invalid input. Please enter a non-negative integer.\n";
            }
        }
        return shipsMap;
}



std::pair<int, int> ConsoleInput::readCoordinates()
{
        int x, y;
        std::string input;
        while (true) {
            std::cout << "Enter x and y: ";
            if (std::getline(std::cin, input)) {
                std::istringstream iss(input);
                if (iss >> x >> y && iss.eof()) {
                    break;
                }
            }
            std::cout << "Invalid input. Please enter two integers.\n";
        }
        return {x, y};
}


int ConsoleInput::readShipIndex()
{
        int index;
        std::string input;
        while (true) {
            std::cout << "Enter ship index: ";
            if (std::getline(std::cin, input)) {
                std::istringstream iss(input);
                if (iss >> index && iss.eof() && index >= 0) {
                    break;
                }
            }
            std::cout << "Invalid input. Please enter a positive integer.\n";
        }
        return index;
}

Battleship::Orientation ConsoleInput::readOrientation()
{
std::string input;
        while (true) {
            std::cout << "Enter ship orientation (v for vertical, h for horizontal): ";
            if (std::getline(std::cin, input) && !input.empty()) {
                char c = std::tolower(input[0]);
                if (c == 'v') {
                    return Battleship::Orientation::VERTICAL;
                } else if (c == 'h') {
                    return Battleship::Orientation::HORIZONTAL;
                }
            }
            std::cout << "Invalid input. Please enter 'v' or 'h'.\n";
        }
}

std::string ConsoleInput::readCommand()
{
        std::string input;
        std::cout << "Enter command: ";
        if (std::getline(std::cin, input)) {
            size_t spacePos = input.find(' ');
            if (spacePos != std::string::npos) {
                input = input.substr(0, spacePos);
            }
        }
        std::cout << "<" << input << ">\n";
        return input;
}

void ConsoleInput::viewAbility(AbilityManager::AbilitiesCodes code)
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
    
    case 3:
        std::cout << "No ablities\n";
        break;

    default:
        break;
    }
}

void ConsoleInput::writeInfo(std::string str)
{
    std::cout << str << "\n";
}

/*
Alexander Romanoff, [09.12.2024 23:36]
`
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <limits>
#include <stdexcept>
#include <utility>

class ConsoleInput {
public:
    ConsoleInput(const std::string& terminalPath) {
        // console.open(terminalPath, std::ios::in | std::ios::out);
        // if (!console.is_open()) 
        // {
        //     throw std::runtime_error("Failed to open terminal: " + terminalPath);
        // }
    }

    std::pair<int, int> readFieldSize() {
        int hor, ver;
        std::string input;
        while (true) {
            std::cout << "Enter field sizes (horizontal and vertical): ";
            if (std::getline(std::cin, input)) {
                std::istringstream iss(input);
                if (iss >> hor >> ver && iss.eof() && hor > 0 && ver > 0) {
                    break;
                }
            }
            std::cout << "Invalid input. Please enter two positive integers.\n";
        }
        return {hor, ver};
    }

    std::map<int, int> readShipsMap() {
        std::map<int, int> shipsMap;
        for (int i = 1; i < 5; i++) {
            int num;
            std::string input;
            while (true) {
                std::cout << "Enter number of ships of size " << i << ": ";
                if (std::getline(std::cin, input)) {
                    std::istringstream iss(input);
                    if (iss >> num && iss.eof() && num >= 0) {
                        shipsMap[i] = num;
                        break;
                    }
                }
                std::cout << "Invalid input. Please enter a non-negative integer.\n";
            }
        }
        return shipsMap;
    }

    std::pair<int, int> readCoordinates() {
        int x, y;
        std::string input;
        while (true) {
            std::cout << "Enter x and y: ";
            if (std::getline(std::cin, input)) {
                std::istringstream iss(input);
                if (iss >> x >> y && iss.eof()) {
                    break;
                }
            }
            std::cout << "Invalid input. Please enter two integers.\n";
        }
        return {x, y};
    }

    int readShipIndex() {
        int index;
        std::string input;
        while (true) {
            std::cout << "Enter ship index: ";
            if (std::getline(std::cin, input)) {
                std::istringstream iss(input);
                if (iss >> index && iss.eof() && index > 0) {
                    break;
                }
            }
            std::cout << "Invalid input. Please enter a positive integer.\n";
        }
        return index;
    }

    enum class Orientation { VERTICAL, HORIZONTAL };

    Orientation readOrientation() {
        std::string input;
        while (true) {
            std::cout << "Enter ship orientation (v for vertical, h for horizontal): ";
            if (std::getline(std::cin, input) && !input.empty()) {
                char c = std::tolower(input[0]);
                if (c == 'v') {
                    return Orientation::VERTICAL;
                } else if (c == 'h') {
                    return Orientation::HORIZONTAL;
                }
            }
            std::cout << "Invalid input. Please enter 'v' or 'h'.\n";
        }
    }

    std::string readCommand() {
        std::string input;
        std::cout << "Enter command: ";
        if (std::getline(std::cin, input)) {
            size_t spacePos = input.find(' ');
            if (spacePos != std::string::npos) {
                input = input.substr(0, spacePos);
            }
        }
        std::cout << "<" << input << ">\n";
        return input;
    }

    void viewAbility(int code) {
        switch (code) {
            case 0:
                std::cout << "Massive attack\n";
                break;

Alexander Romanoff, [09.12.2024 23:36]
case 1:
                std::cout << "Shelling\n";
                break;
            case 2:
                std::cout << "Scanner\n";
                break;
            case 3:
                std::cout << "No abilities\n";
                break;
            default:
                std::cout << "Unknown ability code\n";
                break;
        }
    }

    void writeInfo(const std::string& str) {
        std::cout << str << "\n";
    }
};
`
*/