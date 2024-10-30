#include "../include/Field.h"
#include "Cell.cpp"

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


    void Field::attackCell(int x, int y, int attackPower = 1)
    {
        if(!checkCellInField(x, y))
        {
            throw std::invalid_argument("invalid coordinates");
        }
        mFieldMap[y][x].attack(attackPower);

    }

    void Field::placeShip(Battleship& shipObject, int x, int y, Battleship::Orientation orientation)
    {
        if(shipObject.isPlaced())
        {
            throw std::logic_error("ship has already been placed");
        }

        try
        {
            checkShipPlacement(shipObject, x, y, orientation);
        }
        catch(const std::invalid_argument& ex)
        {
            std::cerr << ex.what() << "\n";
            return;
        }
        catch(std::logic_error &ex)
        {
            std::cerr << ex.what() << "\n";
            return;
        }
        int shipLength = shipObject.getNumberOfSegments();
        if(orientation == Battleship::Orientation::HORIZONTAL)
        {
            for(int i = 0; i < shipLength; i++)
            {
                mFieldMap[y][x + i].addShipSegment(&shipObject, i);
            }
        }
        else if(orientation == Battleship::Orientation::VERTICAL)
        {
            for(int i = 0; i < shipLength; i++)
            {
                mFieldMap[y + i][x].addShipSegment(&shipObject, i);
            }
        }

        shipObject.setOrientation(orientation);
        shipObject.setPlaced(true);
    }

    bool Field::checkShipPlacement(Battleship & shipObject, int x_start, int y_start, Battleship::Orientation orientation)
    {
        bool suitable = true;
        int shipLength = shipObject.getNumberOfSegments();

        // default orientation is horizontal...
        int x_end = x_start  + shipLength - 1;
        int y_end = y_start;

        if(orientation == Battleship::Orientation::VERTICAL)
        {
            x_end = x_start;
            y_end = y_start  + shipLength - 1;
        }
        suitable = checkCellInField(x_start, y_start) && checkCellInField(x_end, y_end);

        if(!suitable)
        {
            throw std::invalid_argument("invalid coordinates");
        }

        else
        {
            for(int i = x_start - 1; i <= x_end + 1; i++)
            {
                for(int j = y_start - 1; j <= y_end + 1; j++)
                {
                    if (!checkCellInField(i, j))
                    {
                        continue;
                    }

                    if(isCellOccupied(i, j))
                    {
                        suitable = false;
                        throw std::logic_error("ships interfere");
                        break;
                    }
                }
            }
        }
        return suitable;
    }

    bool Field::isCellOccupied(int x, int y)
    {
        if(!checkCellInField(x, y))
        {
            return false;
        }
        
        return (mFieldMap[y][x].isShipHere());
    }

    bool Field::checkCellInField(int x, int y)
    {
        return ((x >= 0) && (x < mHorizontalSize)) && ((y >= 0) && (y < mVerticalSize));
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
