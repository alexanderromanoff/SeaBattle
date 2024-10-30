#ifndef VISITOR_H
#define VISITOR_h

#include "IVisitor.h"
#include "Factory.h"


class AbilityVisitor : public IVisitor
{
private:
    Factory* mFactory = nullptr;
public:
    AbilityVisitor(Factory* pFactory);
    void Visit(class MassiveAttackArgs& arguments);    
    void Visit(class ScanerArgs& arguments);  
    void Visit(class ShellingArgs& arguments);  
};

#endif