#include "../include/Field.h"


void Field::Cell::addShipSegment(Battleship& shipObject, int shipSegmentIndex)
{
    mShipPointer = &shipObject;
    mShipSegmentNumber = shipSegmentIndex;
    if(mShipPointer->getSegmentHealth(mShipSegmentNumber) == 0)
    {
        mCellState = CELL_STATES::SHIP_DESTROYED;
    }  
    else if(mShipPointer->getSegmentHealth(mShipSegmentNumber) == 1)
    {
        mCellState = CELL_STATES::SHIP_DAMAGED;
    }
    else
    {
        mCellState = CELL_STATES::SHIP_EXISTS;
    } 
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
        std::cout << mShipPointer->getSegmentHealth(mShipSegmentNumber);
        if(mShipPointer->getSegmentHealth(mShipSegmentNumber) == 0)
        {
            mCellState = CELL_STATES::SHIP_DESTROYED;
        }   
        else
        {
            mCellState = CELL_STATES::SHIP_DAMAGED;
        }
        if(!mShipPointer->isAlive())
        {
            return Attack_Result::Wreck;
        }
        return Attack_Result::Strike;

    case CELL_STATES::SHIP_DAMAGED:
        mShipPointer->takeDamage(mShipSegmentNumber, attackPower);   
        
        mCellState = CELL_STATES::SHIP_DESTROYED;
                 
        if(!mShipPointer->isAlive())
        {
            return Attack_Result::Wreck;
        }
        return Attack_Result::Strike;
    
    case CELL_STATES::SHIP_DESTROYED:
        return Attack_Result::Invalid;

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

Field::Cell::CELL_STATES Field::Cell::getState() const
{
    return mCellState;
}

void Field::Cell::setState(Field::Cell::CELL_STATES value)
{
    mCellState = value;
}

Battleship& Field::Cell::getShip()
{
    return *mShipPointer;
}

int Field::Cell::getNumberOFshipSegment()
{
    return mShipSegmentNumber;
}