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

void Monster::movement (int moveCount , Location target) noexcept
{
    int distance = Map::getDistance(location , target);

    if(moveCount >= distance)
    {
        location = target;
        return;
    }

    for (int i = 0 ; i < 19 ; ++i)
    {
        Location otherLocation = static_cast<Location>(i);
        distance = Map::getDistance(location , otherLocation);
        int remainingDistance = Map::getDistance(otherLocation , target);
        if (distance == moveCount && remainingDistance == (Map::getDistance(location , target) - moveCount))
        {
            location = otherLocation;
        }
    }
}

bool Monster::attack(Hero* hero , Villager* villager) const noexcept
{
    if(hero && hero->receiveAttack())
    {
        Map::increaseHorror();
        return true;
    }
    else if (villager)
    {
        Map::increaseHorror();
        villager->receiveAttack();
        return true;
    }
    return false;
}

bool Monster::isActive() const noexcept
{
    return active;
}

void Monster::kill() noexcept
{
    active = false;
}

const unordered_map<Location , bool>& Monster::getMatStatus() const noexcept
{
    return matStatus;
}

void Monster::receiveDefeat(Location heroLocation , const std::vector<Item>& items)
{
    if (!isActive())
    {
        throw std::logic_error("Dracula has already been killed");
    }
    for (auto const& part : matStatus)
    {
        if (!part.second)
        {
            throw std::logic_error("The monster's mat mission is not complete");
        }
    }
    if (heroLocation != location)
    {
        throw std::invalid_argument("To kill monster, the hero must be in that monster's position");
    }
    int totalStrength = 0;
    for (auto const& item : items)
    {
        if (item.getItemType() != requiredItemType)
        {
            throw std::invalid_argument("Invalid item type used to kill the monster");
        }
        totalStrength += item.getStrength();
    }
    if (totalStrength < requiredItemStrength)
    {
        throw std::logic_error("The total power of the items is not enough to kill monster");
    }

    kill();
}

void Monster::setRequiredItemStrength(int strength)
{
    if (strength < 0 || strength > 218)
    {
        throw invalid_argument("The total power of the items is invalid");
    }
    requiredItemStrength = strength;
}

unsigned int Monster::numOfPartsSolved() const noexcept
{
    unsigned int partsSolved = 0;
    for (auto const& part : matStatus)
    {
        if (part.second)
        {
            ++partsSolved;
        }
    }

    return partsSolved;
}


void Monster::doOperationOnMat(Location location)
{
    auto it = matStatus.find(location);
    if (it == matStatus.end())
    {
        throw std::invalid_argument("Invalid location for monster's mat");
    }
    if (it->second)
    {
        throw std::logic_error("The operation of this location on the monster's mat has already been done");
    }
    it->second = true;
}