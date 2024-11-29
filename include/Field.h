#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <vector>
#include "Battleship.h"
#include "../include/Exceptions/ExcepOutOfField.h"
#include "../include/Exceptions/ExcepCollision.h"
#include "../include/Exceptions/ExcepShipAlreadyPlaced.h"



const int MAX_FIELD_SIZE = 25;
const int MIN_FIELD_SIZE = 2;

class Field
{
public:
    enum Attack_Result {Miss, Strike, Wreck, Invalid};
private:

    class Cell
    {
    private:
        Battleship* mShipPointer = nullptr;
        int mShipSegmentNumber;

        enum CELL_STATES {UNKNOWN = 0, EMPTY = 2, SHIP_EXISTS = 1};
        CELL_STATES mCellState = CELL_STATES::UNKNOWN;
    public:
        Cell() = default;
        ~Cell() = default;
        std::string getState();
        void setState(char value);
        void addShipSegment(Battleship& ship_object, int ship_segment_index);
        bool isShipHere();
        int getNumberOFshipSegment();
        Battleship& getShip();
        Attack_Result attack(int mAttackPower);
        std::string represent();
    };

private:
    int mHorizontalSize;
    int mVerticalSize;
    std::vector<std::vector<Cell>> mFieldMap;

    bool checkShipPlacement(Battleship & battleship_object, int x_start, int y_start, Battleship::Orientation orientation);
    void placeShipSegmentOnCell(int x, int y, Battleship & ship_object, int segment_index);

public:

    Field(int height, int width);
    ~Field() = default;

    Field(const Field & source);
    Field & operator = (const Field & source);
    Field(Field && source);
    Field & operator = (Field && source);

    std::string getFieldMap();
    std::string getShips();
    void setFieldMap(std::string);


    int getHeight();
    int getWidth();
    bool checkCellInField(int x, int y);
    bool isCellOccupied(int x, int y);
    Attack_Result attackCell(int x, int y, int attackPower);
    void placeShip(Battleship & battleship_object, int x, int y, Battleship::Orientation orientation);
    
    void print();
};


#endif