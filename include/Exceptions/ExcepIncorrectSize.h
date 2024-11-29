#ifndef WRONG_SIZE_EXCEP_H
#define WRONG_SIZE_EXCEP_H

#include <string>

class IncorrectShipSizeException : public std::exception
{
public:
    IncorrectShipSizeException(int size) : size(size) {}

    std::string what()
    {
        message += std::to_string(size) + "!";
        return message;
    }
private:
    int size;
    std::string message = "Wrong size for ship: ";
};

#endif