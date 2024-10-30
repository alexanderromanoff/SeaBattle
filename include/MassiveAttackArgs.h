#ifndef MASSIVE_ATTACK_ARGS_H
#define MASSIVE_ATTACK_ARGS_H

#include "IArgs.h"
#include "IVisitor.h"
#include "Field.h"


struct MassiveAttackArgs : public IArgs
{
//methods
    void acceptVisitor(IVisitor & visitor) {visitor.Visit(*this);}
    MassiveAttackArgs(Field* pField) : pField(pField) {}
//members
    Field * pField;
};

#endif