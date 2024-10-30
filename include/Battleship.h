#pragma once
#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
#include <string>
#include <vector>

const int MIN_SHIP_LENGTH = 1;
const int MAX_SHIP_LENGTH = 5;

class Battleship {

public:
    enum Orientation {HORIZONTAL = 1, VERTICAL = 2};
private:
    const int mNumberOfSegments;
    enum Segment_States { OK = 2, damaged = 1, destroyed = 0 };
    std::vector <Segment_States> mShipSegments;
    bool mPlaced = false;
    Orientation mShipOrientation;
public:

    Battleship(int size);
    ~Battleship() = default;

    void takeDamage(int segment_position, int damage);

    bool isPlaced(); 
    bool isAlive();

    int getSegmentHealth(int index);
    int getNumberOfSegments();

    void setPlaced(bool state);
    void setOrientation(Orientation mShipOrientation);
    
    std::string represent();
};


#endif 