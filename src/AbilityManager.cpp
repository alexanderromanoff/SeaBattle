#include "../include/AbilityManager.h"


AbilityManager::AbilityManager()
{
    std::vector<AbilitiesCodes> startValues {AbilitiesCodes::MASSIVE_ATTACK, AbilitiesCodes::SCANER, AbilitiesCodes::SHELLING};
    //shuffle(startValues.begin(), startValues.end(), rand());
    for(int i = 0; i < 3; i++)
    {
        mAvaliableAbilitiesInfo.push(startValues[i]);
    }
}

void AbilityManager::recieveAbility()
{   

    int randomCode = rand() % 3;
    AbilitiesCodes code;
    switch (randomCode)
    {
    
    case 0:
        code = AbilitiesCodes::MASSIVE_ATTACK;
        break;
    case 1:
        code = AbilitiesCodes::SHELLING;
        break;
    case 2:
        code = AbilitiesCodes::SCANER;
        break;
    default:
        break;
    }
    mAvaliableAbilitiesInfo.push(code);

}

IAbility& AbilityManager::buildAbility(IArgs & arguments)
{
    Factory & abilityFactory = *(new Factory());
    IVisitor & visitor = *(new AbilityVisitor(&abilityFactory));
    arguments.acceptVisitor(visitor);
    IAbility & ability = abilityFactory.getAbility();
    delete &abilityFactory;
    delete &visitor;
    return ability;
}

void AbilityManager::useAbility(IArgs &arguments)
{
    if(mAvaliableAbilitiesInfo.size() == 0)
    {
        throw std::length_error("0 abilities avliable");
    }
    IAbility &ability = buildAbility(arguments);
    ability.applyAbility();
    mAvaliableAbilitiesInfo.pop();
    delete &ability;
}

AbilityManager::AbilitiesCodes AbilityManager::viewAvaliableAbilities()
{
    if(mAvaliableAbilitiesInfo.size() == 0)
    {
        throw std::length_error("0 abilities avliable");
    }
    return mAvaliableAbilitiesInfo.front();
}
