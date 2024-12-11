#include "../include/Abilities/Arguments/ArgumentsVisitor.h"

    
ArgumentsVisitor::ArgumentsVisitor(Factory* pFactory) : mFactory(pFactory){}

void ArgumentsVisitor::Visit(class MassiveAttackArgs& arguments)
{
    mFactory->buildMassiveAttack(arguments);
}
void ArgumentsVisitor::Visit(class ScanerArgs& arguments)
{
    mFactory->buildScaner(arguments);
}
void ArgumentsVisitor::Visit(class ShellingArgs& arguments)
{
    mFactory->buildShelling(arguments);
}
void ArgumentsVisitor::Visit(class TrollArgs& arguments)
{
    mFactory->buildTroll();
}
