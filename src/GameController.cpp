#include "../include/Game/GameController.h"
#include "../include/Game/Input/IOInterface.h"
#include "../include/Game/Input/ConsoleInput.h"

GameController::GameController(Game& game) : mGame(game), mInput(*(new ConsoleInput)) {}

void GameController::initGame()
{
    std::pair<int, int> fieldSize = mInput.readFieldSize();
    std::map<int, int> ships = mInput.readShipsMap();

    UserPlayer *userPlayer = new UserPlayer(*(new InputHandler(this)));
    userPlayer->initUser(fieldSize, ships);

    DummyPlayer *dummyPlayer = new DummyPlayer(*(new InputHandler(this)));
    dummyPlayer->initDummy(fieldSize, ships);

    GameState* state = new GameState(userPlayer, dummyPlayer);

    fieldSizesData = fieldSize;
    shipsData = ships;

    mGame.setState(*state);

    mGame.setAttacker(*userPlayer);
    mGame.setTarget(*dummyPlayer);

    mGame.placeShips(*userPlayer);
    mGame.placeShips(*dummyPlayer);

    runGame();
}


void GameController::saveProgress()
{
    GameState* state = mGame.getState();
    std::ofstream writeFile(destFile);
    if(writeFile.is_open())
    {
        writeFile << *state;
        writeFile.close();
    }
}

void GameController::loadProgress()
{
    GameState* state = mGame.getState();
    if(state == nullptr)
    {

        UserPlayer *userPlayer = new UserPlayer(*(new InputHandler(this)));
        DummyPlayer *dummyPlayer = new DummyPlayer(*(new InputHandler(this)));
        state = new GameState(userPlayer, dummyPlayer);
    }
    std::ifstream readFile(destFile);
    if(readFile.is_open())
    {
        readFile >> *state;
        mGame.setState(*state);
        readFile.close();
        // mainLoop();
    }
}

void GameController::selectCommand(CommandArgs& args)
{
    Command* command = nullptr;
    if(args.commandName == "ATK")
    {
        command = new AttackCommand(args.x, args.y, mGame.getAttacker());
    }
    else if(args.commandName == "ABL")
    {
        AbilityManager::AbilitiesCodes code = mGame.getAttacker().getAbManager().viewAvaliableAbilities();
        switch (code)
        {
        case AbilityManager::AbilitiesCodes::SCANER:
        {
            IOInterface& inp = mGame.getAttacker().getIO(); // get the hecking coordinates DIRECTLY from INVOKER'S input device
            std::pair<int, int> coordinatos = inp.readCoordinates();
            command = new ScanerCommand(mGame.getTarget(), coordinatos);
            break;
        }
        case AbilityManager::AbilitiesCodes::SHELLING:
        {
            command = new ShellingCommand(mGame.getTarget());
            break;
        }
        case AbilityManager::AbilitiesCodes::MASSIVE_ATTACK:
        {
            command = new MassiveAttackCommand(mGame.getAttacker());
            break;
        }
        default:
        {
            break;
        }
        }
    }
    if(command != nullptr)
    {
        mGame.executeCommand(*command);
        delete command;
    }
    if(args.commandName == "INFO")
    {
        AbilityManager::AbilitiesCodes code = mGame.getAttacker().getAbManager().viewAvaliableAbilities();
        IOInterface& inp = mGame.getAttacker().getIO(); 
        inp.viewInfo(code);
        
    }
    if(args.commandName == "SAVE")
    {
        std::cout << "start Save\n";
        saveProgress();
        std::cout << "save OK\n";
    }
    else if(args.commandName == "LOAD")
    {
        std::cout << "start load\n";
        loadProgress();
        std::cout << "load OK\n";
    }
    runGame();
}


void GameController::runGame()
{

    if(!mGame.getAttacker().isAlive())
    {   
        Player* deadPlayer = &mGame.getAttacker();
        Player* user = &mGame.getState()->getUser();
        if(deadPlayer == user)
        {
            std::cout << "lose\n";
            initGame(); // restart
        }
        else
        {
            std::cout << "win\n";
            newWave(); // continue: renew the dummy, doesn't change user
        }
    }

    mGame.playRound();
}

void GameController::newWave()
{
    UserPlayer* currentUser = &mGame.getState()->getUser();

    DummyPlayer* newDummy = new DummyPlayer(*(new InputHandler(this)));
    newDummy->initDummy(fieldSizesData, shipsData);

    mGame.placeShips(*newDummy);
    mGame.setAttacker(*newDummy);

    GameState* newState = new GameState(currentUser, newDummy);
    mGame.setState(*newState);
    std::cout << "new wave!\n";

    runGame();
}

