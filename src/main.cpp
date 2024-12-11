
#include "../include/Game/GameController.h"
#include "../include/Game/Game.h"

#include "../include/Game/Input/IOMediator.h"
#include "../include/Game/Input/DummyInput.h"
#include "../include/Game/Input/ConsoleInput.h"
#include "../include/Game/Input/InputHandler.h"

#include "../include/Game/SaveLoad/Saver.h"

#include "../include/Game/Display/GameObserver.h"
#include "../include/Game/Display/ConsoleDisplay.h"

int main() 
{
    srand(time(NULL));
    Game* game = new Game;
    GameController* gContr = new GameController(*game);

    GameDisplayerWrapper<ConsoleDisplayer>* output = new GameDisplayerWrapper<ConsoleDisplayer>("/dev/pts/1");
    GameObserver* gObserver = new ConcreteGameObserver(*output);
    game->addObserver(gObserver);
    // UserObserver* uObserver = new UserObserver(*output);
    // DummyObserver* dObserver = new DummyObserver(*output);

    ConsoleInput* userInput = new ConsoleInput("/dev/pts/0");
    DummyInput* dummyInput = new DummyInput;
    InputHandler* handler = new InputHandler(*gContr);
    IOMediator* mediator = new ConcreteMediator(*userInput, *dummyInput, *handler);


    gContr->initController(mediator);
    gContr->setChoice();
    while(!gContr->interruptSignal)
    {
        gContr->controlGame();
    }
    std::cout  << "quit bro";
    delete mediator;
    delete handler;
    delete dummyInput;
    delete userInput;

    delete output;
    delete gContr;
    delete game;
    
}
