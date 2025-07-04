#include <unordered_map>
#include "dracula.hpp"
#include "map.hpp"

using namespace std;

Dracula::Dracula(Location i_location) : Monster(MonsterName::DRACULA , i_location , ItemType::YELLOW , 6 , unordered_map<Location , bool>{{ Location::CAVE , false } , { Location::CRYPT , false } , { Location::DUNGEON , false } , { Location::GRAVEYARD , false }}) {}

void Dracula::receiveAdvance(Location heroLocation, const std::vector<Item>& items)
{
    int totalStrength = 0;
    for (auto const& item : items)
    {
        if (item.getItemType() != ItemType::RED)
        {
            throw std::invalid_argument("Only red items can be used to destroy the coffin");
        }
        totalStrength += item.getStrength();
    }
    if (totalStrength < REQUIRED_RED_STRENGTH)
    {
        throw std::logic_error("The power of red items is not enough to decorate the coffin (need at least 6)");
    }
    doOperationOnMat(heroLocation);
}

void Dracula::power(const std::array<Villager , 7>& , Hero* currentHero)
{
    currentHero->setLocation(getLocation());
}