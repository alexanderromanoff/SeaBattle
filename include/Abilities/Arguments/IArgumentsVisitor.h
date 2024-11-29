#ifndef IVISTOR_H
#define IVISTOR_H



class IArgumentsVisitor
{
public:

    virtual void Visit(class MassiveAttackArgs& arguments) = 0;    
    virtual void Visit(class ScanerArgs& arguments) = 0;  
    virtual void Visit(class ShellingArgs& arguments) = 0;  
};

#endif