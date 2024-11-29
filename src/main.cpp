
#include "../include/Game/GameController.h"
#include "../include/Game/Game.h"

int main() 
{
    
    std::cout << "balls";
    Game* game = new Game;
    GameController* gContr = new GameController(*game);
    gContr->initGame();
}
