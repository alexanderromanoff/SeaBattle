#include "../include/Game/Display/ConsoleDisplay.h"

ConsoleDisplayer::ConsoleDisplayer(const std::string& terminalPath)
{
    console.open(terminalPath);
    if (!console.is_open()) 
    {
        throw std::runtime_error("Failed to open terminal: " + terminalPath);
    }
    console << "console open\n";
    console.flush();
}

ConsoleDisplayer::~ConsoleDisplayer()
{
    console << "end of session\n\n";
    console.flush();

    console.close();
}


void ConsoleDisplayer::drawField(Field& userField, Field& botField)
{
    static int turn = 0;
    std::string whitespaceOffset;
    for(int i = 0; i < userField.getWidth() - 2; i++)
    {
        whitespaceOffset +=  "    " ;
    }
    console << turn << "\n";
    turn++;
    console << "USER" << whitespaceOffset << "BOT\n";

    for(int i = 0; i < userField.getHeight(); i++)
    {
        drawFieldLine(userField, i, false);
        drawFieldLine(botField, i, true);
        console << "\n";
    }
    console << "\n\n";
    console.flush();
}

void ConsoleDisplayer::drawFieldLine(Field& fieldToDraw, int numberOfLine, bool hide)
{
    std::vector<std::vector<Field::Cell::CELL_STATES>> fieldCellsStates = fieldToDraw.getCellStates();
    for(int j = 0; j < fieldToDraw.getWidth(); j++)
        {
            switch (fieldCellsStates[numberOfLine][j])
            {
            case Field::Cell::CELL_STATES::UNKNOWN :
                console << "[ ]";
                break;
            
            case Field::Cell::CELL_STATES::EMPTY :
                console << "[⋅]";
                break;

            case Field::Cell::CELL_STATES::SHIP_EXISTS :
                if(hide)
                {
                    console << "[ ]";
                }
                else
                {
                    console << "[2]";
                }
                break;
            case Field::Cell::CELL_STATES::SHIP_DAMAGED :
                console << "[1]";
                break;
            case Field::Cell::CELL_STATES::SHIP_DESTROYED :
                console << "[X]";
                break;
            default:
                break;
            }
        }
        console << "\t";

}


















void ConsoleDisplayer::writeName(std::string name)
{
    console << name << "\n";
}


void ConsoleDisplayer::drawAbilityManager(AbilityManager& abManToDraw)
{
    AbilityManager::AbilitiesCodes code = abManToDraw.viewAvaliableAbilities();
    {
    switch (code)
    {
    case 0:
        console << "Massive attack\n";
        break;


    case 1:
        console << "Shelling\n";
        break;

    case 2:
        console << "Scaner\n";
        break;
    
    case 3:
        console << "No ablities\n";
        break;

    default:
        break;
    }
    }
    console << "\n\n";
    console.flush();
}

void ConsoleDisplayer::drawShipManager(ShipManager& shaManToDraw)
{
    for(int i = 0; i < shaManToDraw.getNumberOfShips(); i++)
    {
        Battleship& ship = shaManToDraw.getShipAtIndex(i);
        int lenShip = ship.getNumberOfSegments();
        for(int j = 0; j < ship.getNumberOfSegments(); j++)
        {
            console << "[" << ship.getSegmentHealth(i) << "]";
        }
        console << "  PLACED: " << ship.isPlaced() << "  ALIVE: " << ship.isAlive() << "\n\n";
    }
    console.flush();
    
}