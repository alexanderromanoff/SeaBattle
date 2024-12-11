#include "../include/Field.h"
//#include "Cell.cpp"

    Field::Field(int height, int width) : mHorizontalSize(width), mVerticalSize(height)
    {
        mFieldMap.resize(mVerticalSize);
        for(int i = 0; i < mVerticalSize; i++)
        {
            mFieldMap[i].resize(mHorizontalSize);
            for(int j = 0; j < mHorizontalSize; j++)
            {
                mFieldMap[i][j] = Cell();
            }
        }
    }

    Field::Field(const Field & source) : mHorizontalSize(source.mHorizontalSize), mVerticalSize(source.mVerticalSize)
    {
        std::vector<std::vector<Cell::CELL_STATES>> sourceCellStates = source.getCellStates();
        mFieldMap.resize(mVerticalSize);
        for(int i = 0; i < mVerticalSize; i++)
        {
            mFieldMap[i].resize(mHorizontalSize);
            for(int j = 0; j < mHorizontalSize; j++)
            {
                mFieldMap[i][j] = Cell();
                mFieldMap[i][j].setState(sourceCellStates[i][j]);
            }
        }
    }

    Field & Field::operator = (const Field & source) 
    {
        if(&source != this)
        {
            mHorizontalSize = source.mHorizontalSize;
            mVerticalSize = source.mVerticalSize;
            std::vector<std::vector<Cell::CELL_STATES>> sourceCellStates = source.getCellStates();
            mFieldMap.resize(mVerticalSize);
            for(int i = 0; i < mVerticalSize; i++)
            {
                mFieldMap[i].resize(mHorizontalSize);
                for(int j = 0; j < mHorizontalSize; j++)
                {
                    mFieldMap[i][j] = Cell();
                    mFieldMap[i][j].setState(sourceCellStates[i][j]);
                }
            }
        }
        return *this;
    }

    Field::Field(Field && source) : mHorizontalSize(source.mHorizontalSize), mVerticalSize(source.mVerticalSize), 
                                     mFieldMap(std::move(source.mFieldMap))
    {}

    Field & Field::operator = (Field && source)
    {
        if(&source != this)
        {
            mHorizontalSize = source.mHorizontalSize;
            mVerticalSize = source.mVerticalSize;
            mFieldMap = std::move(source.mFieldMap);
        }
        return *this;
    }


    Field::Attack_Result Field::attackCell(int x, int y, int attackPower = 1)
    {
        if(!checkCellInField(x, y))
        {
            throw OutOfFieldException(x,y);
        }
        return mFieldMap[y][x].attack(attackPower);

    }

    void Field::placeShip(Battleship& shipObject, int x, int y, Battleship::Orientation orientation)
    {
        if(shipObject.isPlaced())
        {
            throw ShipAlreadyPlacedException();
        }

        // try
        // {
        //     checkShipPlacement(shipObject, x, y, orientation);
        // }
        // catch(OutOfFieldException &ex)
        // {
        //     std::cerr << ex.what() << "\n";
        //     return;
        // }
        // catch(CollisionException &ex)
        // {
        //     std::cerr << ex.what() << "\n";
        //     return;
        // }

        checkShipPlacement(shipObject, x, y, orientation);
        
        int shipLength = shipObject.getNumberOfSegments();
        if(orientation == Battleship::Orientation::HORIZONTAL)
        {
            for(int i = 0; i < shipLength; i++)
            {
                mFieldMap[y][x + i].addShipSegment(shipObject, i);
            }
        }
        else if(orientation == Battleship::Orientation::VERTICAL)
        {
            for(int i = 0; i < shipLength; i++)
            {
                mFieldMap[y + i][x].addShipSegment(shipObject, i);
            }
        }


        shipObject.setOrientation(orientation);
        shipObject.setPlaced(true);
    }

    bool Field::checkShipPlacement(Battleship & shipObject, int xStart, int yStart, Battleship::Orientation orientation)
    {
        bool suitable = true;
        int shipLength = shipObject.getNumberOfSegments();

        // default orientation is horizontal...
        int xEnd = xStart  + shipLength - 1;
        int yEnd = yStart;

        if(orientation == Battleship::Orientation::VERTICAL)
        {
            xEnd = xStart;
            yEnd = yStart  + shipLength - 1;
        }
 
        if(!checkCellInField(xStart, yStart))
        {
            throw OutOfFieldException(xStart,yStart);
        }

        if(!checkCellInField(xEnd, yEnd))
        {
            throw OutOfFieldException(xEnd,yEnd);
        }

        for(int i = xStart - 1; i <= xEnd + 1; i++)
        {
            for(int j = yStart - 1; j <= yEnd + 1; j++)
            {
                if (!checkCellInField(i, j))
                {
                    continue;
                }

                if(isCellOccupied(i, j))
                {
                    suitable = false;
                    throw CollisionException();
                    break;
                }
            }
        }

        return suitable;
    }

    bool Field::isCellOccupied(int x, int y)
    {
        if(!checkCellInField(x, y))
        {
            throw OutOfFieldException(x, y);

        }
        return (mFieldMap[y][x].isShipHere());
    }

    bool Field::checkCellInField(int x, int y)
    {
        return ((x >= 0) && (x < mHorizontalSize)) && ((y >= 0) && (y < mVerticalSize));
    }

    int Field::getHeight()
    {
        return mVerticalSize;
    }

    int Field::getWidth()
    {
        return mHorizontalSize;
    }

    void Field::print()
    {
        for(int y = 0; y < mVerticalSize; y++)
        {
            for(int x = 0; x < mHorizontalSize; x++)
            {
                std::cout << mFieldMap[y][x].represent() << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    std::vector<std::vector<Field::Cell::CELL_STATES>> Field::getCellStates() const
    {
        std::vector<std::vector<Field::Cell::CELL_STATES>> cellStates;
        cellStates.resize(mVerticalSize);

        for(int i = 0; i < mVerticalSize; i++)
        {
            cellStates[i].resize(mHorizontalSize);
            for(int j = 0; j < mHorizontalSize; j++)
            {
                cellStates[i][j] = mFieldMap[i][j].getState();
            }
        }
        return cellStates;
    }

    void Field::setCellStates(std::vector<std::vector<Cell::CELL_STATES>> cellStates)
    {
        for(int i = 0; i < mVerticalSize; i++)
        {
            for(int j = 0; j < mHorizontalSize; j++)
            {
                mFieldMap[i][j].setState(cellStates[i][j]);
            }
        }
    }

    // std::string Field::getInfoStr() const
    // {
    //     std::string stateString;

    //     for(int i = 0; i < mVerticalSize; i++)
    //     {
    //         for(int j = 0; j < mHorizontalSize; j++)
    //         {
    //             Field::Cell::CELL_STATES state = mFieldMap[i][j].getState();
    //             switch (state)
    //             {
    //             case Field::Cell::CELL_STATES::UNKNOWN:
    //                 stateString += "0";
    //                 break;
    //             case Field::Cell::CELL_STATES::EMPTY:
    //                 stateString += "1";
    //                 break;
    //             case Field::Cell::CELL_STATES::SHIP_EXISTS:
    //                 stateString += "2";
    //                 break;
    //             default:
    //                 break;
    //             }
                
    //         }
    //     }
    //     return stateString;
    // }

    // void Field::setInfoFromStr(std::string info)
    // {
    //      for(int i = 0; i < mVerticalSize; i++)
    //     {
    //         for(int j = 0; j < mHorizontalSize; j++)
    //         {
    //             char state = info[i*j + j];
    //             switch (state)
    //             {
    //             case '0':
    //                 mFieldMap[i][j].setState(Field::Cell::CELL_STATES::UNKNOWN);
    //                 break;
    //             case '1':
    //                 mFieldMap[i][j].setState(Field::Cell::CELL_STATES::EMPTY);
    //                 break;
    //             case '2':
    //                 mFieldMap[i][j].setState(Field::Cell::CELL_STATES::SHIP_EXISTS);
    //                 break;
                
    //             default:
    //                 break;
    //             }
    //         }
    //     }
    // }


    std::map<std::pair<int, int>, Battleship*> Field::getShips()
    {
        std::map<std::pair<int, int>, Battleship*> res;
        for(int i = 0; i< mVerticalSize; i++)
        {
            for(int j = 0; j < mHorizontalSize; j++)
            {
                if(mFieldMap[i][j].isShipHere() && mFieldMap[i][j].getNumberOFshipSegment() == 0)
                {
                    
                    std::pair<int, int> coords (i, j);
                    Battleship& shipObject = mFieldMap[i][j].getShip();
                    res.insert({coords, &shipObject});
                }
            }
        }
        return res;
    }
    
