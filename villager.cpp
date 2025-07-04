#include "villager.hpp"
#include "hero.hpp"

Villager::Villager(VillagerName n , Location currentlocation, Location safeLocation )
    : location(currentlocation), safe_location(safeLocation) {
        name = n;
    }

void Villager::Move(int moveCount  , const Location& target ) noexcept {
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

void Villager::receiveAttack()noexcept{
    isAlive = false;
    Active = false;
}

VillagerName Villager::getName()const {
    return name;
}

Location Villager::getLocation()const{
    return location;
}

void Villager::setLocation(Location n){
    location = n;
}

Location Villager::getSafeLocation()const{
    return safe_location;
}

bool Villager::isActive() const{
    if (Active == true)
    {
        return true;
    }
    return false;
    
}

void Villager::activate(){
    Active = true;
}

std::string villagerNameToString(VillagerName n){
    switch (n)
    {
    case VillagerName::DRCRANLY:
        return "DRCRANLY";
    case VillagerName::DRREAD:
        return "DRREAD";
    case VillagerName::FRITZ:
        return "FRITZ";
    case VillagerName::MALEVA:
        return "MALEVA";
    case VillagerName::MARIA:
        return "MARIA";
    case VillagerName::PROFPEARSON:
        return "PROFPEARSON";
    case VillagerName::WILBURANDCHICK:
        return "WILBURANDCHICK";
    
    default:
        return " ";
        break;
    }
}

void Villager::movement (int moveCount , Location target) noexcept
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

void Villager::DisActive(){
    Active = false;
}