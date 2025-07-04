#include <limits>
#include "monster.hpp"

using namespace std;

string monsterNameToString(MonsterName name) noexcept
{
    switch(name)
    {
        case MonsterName::DRACULA:      
            return "DRACULA";

        case MonsterName::INVISIBLEMAN:       
            return "INVISIBLEMAN";

        case MonsterName::FRENZY:
            return "FRENZY";

        default:       
            return "UNKNOWN";
    }
}

Monster::Monster(MonsterName i_name , Location i_location , ItemType i_requiredItemType , int strength , unordered_map<Location , bool> i_matStatus) : name(i_name) , location(i_location) , requiredItemType(i_requiredItemType) , matStatus(i_matStatus)
{
    setRequiredItemStrength(strength);
}

MonsterName Monster::getName() const noexcept
{
    return name;
}

Location Monster::getLocation() const noexcept
{
    return location;
}

void Monster::setLocation (Location i_location) noexcept
{
    location = i_location;
}

void Monster::setRequiredItemStrength(int strength)
{
    if (strength < 0 || strength > 218)
    {
        throw invalid_argument("The total power of the items is invalid");
    }
    requiredItemStrength = strength;
}