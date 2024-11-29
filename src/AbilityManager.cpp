#include "../include/AbilityManager.h"


AbilityManager::AbilityManager()
{
    std::vector<AbilitiesCodes> startValues {AbilitiesCodes::MASSIVE_ATTACK, AbilitiesCodes::SCANER, AbilitiesCodes::SHELLING};
    //std::random_shuffle(startValues.begin(), startValues.end());
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

IAbility& AbilityManager::buildAbility(IAbilityArguments & arguments)
{
    Factory & abilityFactory = *(new Factory());
    IArgumentsVisitor & visitor = *(new ArgumentsVisitor(&abilityFactory));
    arguments.acceptVisitor(visitor);
    IAbility & ability = abilityFactory.getAbility();
    delete &abilityFactory;
    delete &visitor;
    return ability;
}

IAbilityResult& AbilityManager::useAbility(IAbilityArguments &arguments)
{
    if(mAvaliableAbilitiesInfo.size() == 0)
    {
        throw NoAbilitiesException();
    }
    IAbility &ability = buildAbility(arguments);
    IAbilityResult& abilityResult = ability.applyAbility();
    mAvaliableAbilitiesInfo.pop();
    delete &ability;
    return abilityResult;
}

AbilityManager::AbilitiesCodes AbilityManager::viewAvaliableAbilities()
{
    if(mAvaliableAbilitiesInfo.size() == 0)
    {
        throw NoAbilitiesException();
    }
    return mAvaliableAbilitiesInfo.front();
}

std::string AbilityManager::getInfo()
{
    std::string res;
    std::queue<AbilitiesCodes> tempQueue(mAvaliableAbilitiesInfo);

    while(tempQueue.size() > 0)
    {
        res += std::to_string(tempQueue.front());
        tempQueue.pop();
    }
    res += "\n";
    return res;
}

void AbilityManager::setInfo(std::string info)
{
    while(mAvaliableAbilitiesInfo.size() > 0) // emty the queue
    {
        mAvaliableAbilitiesInfo.pop();
    }

    for(int i = 0; i < info.size(); i++) // refill the queue
    {
        switch (info[i])
        {
        case '0':
            mAvaliableAbilitiesInfo.push(AbilitiesCodes::MASSIVE_ATTACK);
            break;
        
        case '1':
            mAvaliableAbilitiesInfo.push(AbilitiesCodes::SCANER);
            break;
        case '2':
            mAvaliableAbilitiesInfo.push(AbilitiesCodes::SHELLING);
            break;

        default:
            break;
        }
    }
}