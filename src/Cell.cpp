#include "../include/Field.h"


void Field::Cell::addShipSegment(Battleship* shipObject, int shipSegmentIndex)
{
    mShipPointer = shipObject;
    mShipSegmentNumber = shipSegmentIndex;
    mCellState = CELL_STATES::SHIP_EXISTS;
}

bool Field::Cell::isShipHere()
{
    return !(mShipPointer == nullptr);
}

void Field::Cell::attack(int attackPower) // будет возвращать опр. значение если можно повторить ход
{
    switch (mCellState)
    {
    case CELL_STATES::UNKNOWN:
        mCellState = CELL_STATES::EMPTY;
        break;

    case CELL_STATES::EMPTY:
        std::cout << "клетка уже была атакована\n";
        break;

    case CELL_STATES::SHIP_EXISTS:
        mShipPointer->takeDamage(mShipSegmentNumber, attackPower);
        break;
    
    default:
        break;
    }
}

std::string Field::Cell::represent()
{
    std::string res;
    switch (mCellState)
    {
    case CELL_STATES::UNKNOWN:
        res = "[]";

        if(true)
        {
            if(mShipPointer != nullptr)
            {
                res = "[" + std::to_string(mShipPointer->getSegmentHealth(mShipSegmentNumber)) + "]";
            }

        }
        break;

    case CELL_STATES::SHIP_EXISTS:
        res = "[" + std::to_string(mShipPointer->getSegmentHealth(mShipSegmentNumber)) + "]";
        break;
    
    case CELL_STATES::EMPTY:
        res = "[⋅]";
        break;
    }

    return res;
}