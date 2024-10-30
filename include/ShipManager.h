#ifndef SHIP_MANAGER_H
#define SHIP_MANAGER_H

#include <iostream>
#include <map>
#include <vector>
#include "Battleship.h"

class ShipManager
{
private:
    std::vector<Battleship *> mAvailableShips;
public:
    ShipManager(const std::map<int, int> & ships_info);
    ~ShipManager();

    Battleship & getShipAtIndex(int index);

    void createShip(int ship_size);
    void addShips(const std::map<int, int> & ships_info);
    void addShip(Battleship* ship_object);
    std::vector<int> getAliveShipsIndicies();
    void print();
};

#endif