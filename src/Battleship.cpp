#include "../include/Battleship.h"

    Battleship::Battleship(int size) : mNumberOfSegments (size)
    {
        mShipSegments.resize(mNumberOfSegments);
        std::fill(mShipSegments.begin(), mShipSegments.begin() + mNumberOfSegments, Segment_States::OK);
    }


    void Battleship::takeDamage(int segmentPosition, int damage)
    {
        // if(segmentPosition < 0 || segmentPosition >= mNumberOfSegments) // not sure where they will be handled
        // {
        //     throw std::invalid_argument("inavaliable segment"); 
        // }
        if(damage > 1)
        {
            mShipSegments[segmentPosition] = Segment_States::destroyed;
            return;
        }

        switch (mShipSegments[segmentPosition])
        {
        case Segment_States::OK:
            mShipSegments[segmentPosition] = Segment_States::damaged;
            break;
        case Segment_States::damaged:
            mShipSegments[segmentPosition] = Segment_States::destroyed;
        default:
            break;
        }
  
    }
    
    bool Battleship::isAlive()
    {
        for(int i = 0; i < mNumberOfSegments; i++)
        {
            if(mShipSegments[i] != Segment_States::destroyed)
            {
                return false;
            }
        }
        return true;
    }

    bool Battleship::isPlaced()
    {
        return mPlaced;
    }

    void Battleship::setPlaced(bool state)
    {
        mPlaced = state;
    }

    int Battleship::getSegmentHealth(int index)
    {
        // if(index < 0 || index >= mNumberOfSegments) // not sure where they will be handled
        // {
        //     throw std::invalid_argument("inavaliable segment");
        // }
        return mShipSegments[index];
    }
    int Battleship::getNumberOfSegments()
    {
        return mNumberOfSegments;
    }

    void Battleship::setOrientation(Orientation mShipOrientation)
    {
        this->mShipOrientation = mShipOrientation;
    } 

    std::string Battleship::represent()
    {
        std::string res = std::to_string(mNumberOfSegments) + ": ";
        for(int i = 0; i < mNumberOfSegments; i++)
        {
            res += std::to_string(mShipSegments[i]) + " ";
        }
        res += "\n";
        return res;
    }


