#ifndef NO_SHIPS_EXCEP_H
#define NO_SHIPS_EXCEP_H

#include <string>

class NoShipsException : public std::exception
{
public:
    NoShipsException() {}

    std::string what()
    {
        return message;
    }
private:
    std::string message = "No ships to attack!";
};

#endif