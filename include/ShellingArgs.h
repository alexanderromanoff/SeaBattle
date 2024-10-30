#ifndef SHELLING_ARGS_H
#define SHELLING_ARGS_H

#include "IArgs.h"
#include "Field.h"
#include "ShipManager.h"
#include "IVisitor.h"

struct ShellingArgs : public IArgs
{
//methods
    ShellingArgs(Field* pField, ShipManager* pShipManager) : pField(pField), pShipManager(pShipManager) {}
    void acceptVisitor(IVisitor & visitor) {visitor.Visit(*this);}
//members
    ShipManager * pShipManager;
    Field * pField;
};

#endif