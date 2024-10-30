#ifndef IARGS_H
#define IARGS_H

#include "IVisitor.h"

struct IArgs
{
    virtual void acceptVisitor(IVisitor & visitor) = 0;
};

#endif