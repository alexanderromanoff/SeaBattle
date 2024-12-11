#ifndef NO_ABILITIES_EXCEP
#define NO_ABILITIES_EXCEP

#include <string>

class NoAbilitiesException : public std::exception
{
public:
    std::string what()
    {
        return message;
    }
private:
    const std::string message = "No abilities available!";
};

#endif