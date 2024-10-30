#ifndef SCANER_ARGS_H
#define SCANER_ARGS_H

#include "IArgs.h"
#include "Field.h"
#include "IVisitor.h"
#include "IAbility.h"

struct ScanerArgs : public IArgs
{
//methods
    ScanerArgs(std::pair <int, int> coordinates, Field * pField) : 
        coordinates(coordinates), pField(pField) {}
    void acceptVisitor(IVisitor & visitor) {visitor.Visit(*this);}
//members
    std::pair <int, int> coordinates;
    Field * pField;
};

#endif