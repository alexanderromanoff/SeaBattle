#ifndef OUT_OF_FIELD_EXCEP
#define OUT_OF_FIELD_EXCEP

#include <string>

class OutOfFieldException : public std::exception
{
public:
    OutOfFieldException(int x, int y) : x(x), y(y) {}
    std::string what()
    {
        message += "(" + std::to_string(x) + " ," + std::to_string(y) + ")";
        return message;
    }
private:
    int x;
    int y;
    std::string message = "Coordinates are out of field!";
};

#endif