#ifndef COLLISION_EXCEP_H
#define COLLISION_EXCEP_H

#include <string>

class CollisionException : public std::exception
{
public:
    std::string what()
    {
        return message;
    }
private:
    const std::string message = "Ships collide or placed too close!";
};

#endif