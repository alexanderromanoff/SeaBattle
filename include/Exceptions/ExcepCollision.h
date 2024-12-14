#ifndef COLLISION_EXCEP_H
#define COLLISION_EXCEP_H

#include <string>

class CollisionException : public std::exception
{
public:
    CollisionException(int x, int y) : x(x), y(y) {}
    std::string what()
    {
        return message + std::to_string(x) + " " + std::to_string(y);
    }
private:
    int x, y;
    const std::string message = "Ships collide or placed too close!";
};

#endif