#include "../include/ShipManager.h"

    ShipManager::ShipManager(const std::map<int, int> & shipsInfo)
    {
        addShips(shipsInfo);
    }

    ShipManager::~ShipManager()
    {
        for(auto & item : mAvailableShips)
        {
            delete item;
        }
    }

    Battleship & ShipManager::getShipAtIndex(int index)
    {
        if (index >= mAvailableShips.size())
        {
            throw std::invalid_argument("invalid index, can't access the ship");
        }
        return *mAvailableShips[index];
    }

    void ShipManager::addShips(const std::map<int, int> & shipsInfo) // map element: <ship length, number of such ships>
    {
        for(auto& item : shipsInfo)
        {
            for(int i = 0; i < item.second; i++)
            {
                try
                {
                    createShip(item.first);
                }
                catch(const std::exception& ex)
                {
                    std::cerr << ex.what() << "\n";
                } 
            }
        }
    }

    void ShipManager::createShip(int shipSize)
    {
        if(shipSize >= MAX_SHIP_LENGTH || shipSize < MIN_SHIP_LENGTH)
        {
            throw std::invalid_argument("incorrect size of ship");
        }
        Battleship * shipObject = new Battleship(shipSize);
        addShip(shipObject);      
    }

    void ShipManager::addShip(Battleship* shipObject)
    {
        mAvailableShips.push_back(shipObject);
    }

    std::vector<int> ShipManager::getAliveShipsIndicies()
    {
        std::vector<int> aliveShipsIndices;
        for(int i = 0; i < mAvailableShips.size(); i++)
        {
            if(mAvailableShips[i]->isPlaced() && mAvailableShips[i]->isAlive())
            {
                aliveShipsIndices.push_back(i);
            }
        }
        return aliveShipsIndices;
    }

    void ShipManager::print()
    {
        std::string res = "";
        for(int i = 0; i < mAvailableShips.size(); i++)
        {
            res +=  std::to_string(i) + " || " + (mAvailableShips[i] -> represent()) + '\n';
        }
        std::cout << res;
    }

