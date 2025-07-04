#include "invisibleman.hpp"
#include "map.hpp"

using namespace std;

InvisibleMan::InvisibleMan (Location i_location) : Monster(MonsterName::INVISIBLEMAN, i_location , ItemType::RED , 9 , unordered_map<Location , bool>{{Location::INN , false} , {Location::BARN , false} , {Location::INSTITUTE , false} , {Location::LABORATORY , false} , {Location::MANSION , false}}) {}

void InvisibleMan::receiveAdvance(Location heroLocation , const std::vector<Item>& items)
{
    if (heroLocation != Location::PRECINCT)
    {
        throw std::logic_error("Hero must return to Precinct");
    }
    if (items.size() != 1)
    {
        throw std::invalid_argument("Exactly one item required for advance");
    }
    doOperationOnMat(items[0].getLocation());
}

void InvisibleMan::power(const std::array<Villager , 7>& villagers , Hero*)
{
    auto [hero , villager] = Map::findNearestTarget(getLocation(), villagers);
    if (!villager)
    {
        return;
    }
    movement(2 , villager->getLocation());
    if (getLocation() == villager->getLocation())
    {
        if (markedVillager != villager)
        {
            markedVillager = villager;
        }
        else
        {
            attack(nullptr , villager);
            throw logic_error("Attack occured");
        }
    }
}

void InvisibleMan::clearMarkedVillager() noexcept
{
    markedVillager = nullptr;
}