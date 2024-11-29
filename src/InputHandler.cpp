#include "../include/Game/InputHandler.h"
#include "../include/Game/GameController.h"

void InputHandler::processInput(std::string inputStr)
{
        CommandArgs& args = *(new CommandArgs);
        std::regex maskRegex(R"((\w+)?(?:\s+([\d]+))?(?:\s+([\d]+))?)");
        std::smatch matches;
        if(std::regex_match(inputStr, matches, maskRegex))
        {
            args.commandName = matches[1];
            //std::cout << args.commandName;
            if(matches[2] != "")
            {
                args.x = std::stoi(matches[2]);
            }
            if(matches[3] != "")
            {
                args.y = std::stoi(matches[3]);
            }
        }
        else
        {
            throw std::invalid_argument("wrong format");
        }
    mController.selectCommand(args);
    delete &args;
       
}

InputHandler::InputHandler(GameController* contr) : mController(*contr) {}
