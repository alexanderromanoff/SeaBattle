#include "../include/ShipManager.h"

    ShipManager::ShipManager(const std::map<int, int> & shipsInfo)
    {
        addShips(shipsInfo);
        aliveShips = mAvailableShips.size();
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

    int ShipManager::getNumberOfShips()
    {
        return mAvailableShips.size();
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
                catch(IncorrectShipSizeException& ex)
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
            throw IncorrectShipSizeException(shipSize);
        }
        Battleship * shipObject = new Battleship(shipSize);
        addShip(*shipObject);      
    }

    void ShipManager::addShip(Battleship& shipObject)
    {
        mAvailableShips.push_back(&shipObject);
    }

    std::vector<int> ShipManager::getAliveShipsIndicies()
    {
        std::vector<int> aliveShipsIndices;
        bool nothingAdded = true;
        for(int i = 0; i < mAvailableShips.size(); i++)
        {
            if(mAvailableShips[i]->isPlaced() && mAvailableShips[i]->isAlive())
            {
                aliveShipsIndices.push_back(i);
                nothingAdded = false;
            }
        }
        if(nothingAdded)
        {
            throw NoShipsException();
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

