#ifndef REPLACING_SHIP_EXCEP
#define REPLACING_SHIP_EXCEP

#include <string>

class ShipAlreadyPlacedException : public std::exception
{
public:
    std::string what()
    {
        return message;
    }
private:
    const std::string message = "Ship has already been placed!";
};

#endif