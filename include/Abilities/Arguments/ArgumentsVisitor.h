#ifndef VISITOR_H
#define VISITOR_h

#include "IArgumentsVisitor.h"
#include "../Factory.h"


class ArgumentsVisitor : public IArgumentsVisitor
{
private:
    Factory* mFactory = nullptr;
public:
    ArgumentsVisitor(Factory* pFactory);
    void Visit(class MassiveAttackArgs& arguments);    
    void Visit(class ScanerArgs& arguments);  
    void Visit(class ShellingArgs& arguments); 
    void Visit(class TrollArgs& arguments); 
};

#endif