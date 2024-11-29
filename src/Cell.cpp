#include "../include/Field.h"


void Field::Cell::addShipSegment(Battleship& shipObject, int shipSegmentIndex)
{
    mShipPointer = &shipObject;
    mShipSegmentNumber = shipSegmentIndex;
    mCellState = CELL_STATES::SHIP_EXISTS;
}

bool Field::Cell::isShipHere()
{
    return !(mShipPointer == nullptr);
}

Field::Attack_Result Field::Cell::attack(int attackPower) // будет возвращать опр. значение если можно повторить ход
{
    switch (mCellState)
    {
    case CELL_STATES::UNKNOWN:
        mCellState = CELL_STATES::EMPTY;
        return Attack_Result::Miss;

    case CELL_STATES::EMPTY:
        return Attack_Result::Invalid;

    case CELL_STATES::SHIP_EXISTS:
        mShipPointer->takeDamage(mShipSegmentNumber, attackPower);
                
        if(!mShipPointer->isAlive())
        {
            return Attack_Result::Wreck;
        }
        return Attack_Result::Strike;

    default:
        break;
    }
    return Attack_Result::Miss;
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

std::string Field::Cell::getState()
{
    return std::to_string(mCellState);
}

void Field::Cell::setState(char value)
{
    switch (value)
    {
    case '0':
        mCellState = CELL_STATES::UNKNOWN;
        break;
    case '1':
        mCellState = CELL_STATES::SHIP_EXISTS;
        break;
    case '2':
        mCellState = CELL_STATES::EMPTY;
        break;
    
    default:
        break;
    }
}

Battleship& Field::Cell::getShip()
{
    return *mShipPointer;
}

int Field::Cell::getNumberOFshipSegment()
{
    return mShipSegmentNumber;
}