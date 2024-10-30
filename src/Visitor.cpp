#include "../include/Visitor.h"

    
AbilityVisitor::AbilityVisitor(Factory* pFactory) : mFactory(pFactory){}

void AbilityVisitor::Visit(class MassiveAttackArgs& arguments)
{
    mFactory->buildMassiveAttack(arguments);
}
void AbilityVisitor::Visit(class ScanerArgs& arguments)
{
    mFactory->buildScaner(arguments);
}
void AbilityVisitor::Visit(class ShellingArgs& arguments)
{
    mFactory->buildShelling(arguments);
}
