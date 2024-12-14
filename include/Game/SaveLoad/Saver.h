#ifndef SAVER_H
#define SAVER_H
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include "../GameState.h"
#include "../../Players/Player.h"
#include "StringOperator.h"


using json = nlohmann::json; 

class Saver
{
private:
    const std::string destination;
public:
    Saver(std::string destination);
    friend std::ostream& operator<<(std::ostream& os, const GameState& gState);
    friend std::istream& operator>>(std::istream& is, GameState& gState);
    void save(GameState& gState);
    void load(GameState& gState);

};


class SimpleEncryptor {
public:
const int SHIFT = 3;

    std::string encrypt(const std::string& input) 
    {
        std::string output = input;
        for (char& c : output) 
        {
            c += SHIFT; // Сдвигаем символ
        }
        return output;
    }

    std::string decrypt(const std::string& input) 
    {
        std::string output = input;
        for (char& c : output) 
        {
            c -= SHIFT; // Обратный сдвиг
        }
        return output;
    }

    unsigned long hash(const std::string& str) 
    {
        unsigned long hash = 5381;
        for (char c : str) 
        {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash;
    }
};


#endif