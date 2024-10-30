
#include "../include/Battleship.h"
#include "../include/Field.h"
#include "../include/ShipManager.h"
#include "../include/AbilityManager.h"
#include "../include/IArgs.h"
#include "../include/Scaner.h"
#include <map>

Field foo(Field obj)
{
    obj.print();
    
    Field ff = Field(6, 4);
    return obj;
}

int main() 
{
    srand(time(NULL));
    Battleship ship_one(1);
    std::cout << ship_one.represent() << "\n";
    
    int size = 6;
    try
    {
        Battleship ship_two(size);
    }    
    catch(std::invalid_argument &ex)
    {
        std::cerr << ex.what() << ": " << size << "\n";
    }

    

    std::map<int, int> ships;
 
    ships.insert({2, 3});
    ships.insert({7, 1});
    ships.insert({1, 4});
    ships.insert({4, 1});

    ShipManager manager_one(ships);
    AbilityManager man_ab;
   // man_ab.recieveAbility(rand()%3);

    man_ab.viewAvaliableAbilities();
    

    manager_one.print();

    Field field_one(10, 14);
    field_one.placeShip(manager_one.getShipAtIndex(0), 0, 0, Battleship::Orientation::HORIZONTAL);
    std::pair<int, int> coords {10, 10};
   // AbilityResult res{false};
    IArgs *arrr = new ScanerArgs(coords, &field_one);
    man_ab.useAbility(*arrr);
    std::cout << "hh\n";


}