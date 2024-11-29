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

    Field::Field(const Field & source) : mHorizontalSize(source.mHorizontalSize), mVerticalSize(source.mVerticalSize), 
                                        mFieldMap(source.mFieldMap)
    {}

    Field & Field::operator = (const Field & source) 
    {
        if(&source != this)
        {
            mHorizontalSize = source.mHorizontalSize;
            mVerticalSize = source.mVerticalSize;
            mFieldMap = source.mFieldMap;
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

    std::string Field::getFieldMap()
    {
        std::string res;
        res += std::to_string(mVerticalSize) + "\n" + std::to_string(mHorizontalSize) + "\n";
        for(int i = 0; i < mVerticalSize; i++)
        {
            for(int j = 0; j < mHorizontalSize; j++)
            {
                res += mFieldMap[i][j].getState();
            }
        }
        res += "\n";
        return res;
    }

    void Field::setFieldMap(std::string info)
    {
        for(int i = 0; i < mVerticalSize; i++)
        {
            for(int j = 0; j < mHorizontalSize; j++)
            {
                int strInd = i * mVerticalSize + j;
                mFieldMap[i][j].setState(info[strInd]);
            }
        }
    }

    std::string Field::getShips()
    {
        std::string res;
        for(int i = 0; i< mVerticalSize; i++)
        {
            for(int j = 0; j < mHorizontalSize; j++)
            {
                if(mFieldMap[i][j].isShipHere() && mFieldMap[i][j].getNumberOFshipSegment() == 0)
                {
                    res += std::to_string(i) + "\n" + std::to_string(j) + "\n";
                    Battleship& shipObject = mFieldMap[i][j].getShip();
                    int shipSize = shipObject.getNumberOfSegments();
                    int orientation = shipObject.getOrientation();
                    res += std::to_string(shipSize) + std::to_string(orientation);
                    for(int k = 0; k < shipSize; k++)
                    {
                        res += std::to_string(shipObject.getSegmentHealth(k));
                    }
                    res += "\n";
                }
            }
        }
        res += "end\n";
        return res;
    }
    
