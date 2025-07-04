#include "map.hpp"
#include "hero.hpp"
#include "item.hpp"
#include "monster.hpp"
#include "villager.hpp"
#include <cstdio>
#include <string>
#include <iomanip>
#include <vector>
#include <iostream>

using namespace std;

int Map::levelOfHorror = 0;

pair<Hero* , Villager*> Map::findNearestTarget (Location currentLocation , const std::array<Villager , 7>& villagers , const std::array<unique_ptr<Hero> , 2>& heroes) noexcept
{
    Hero* nearestHero     = nullptr;
    Villager* nearestVillager = nullptr;
    int minDistance = 1000;

    if (heroes[0] != nullptr)
    {
        for (auto const& hero : heroes)
        {
            int distance = getDistance(currentLocation , hero->getLocation());
            if(distance < minDistance)
            {
                minDistance = distance;
                nearestHero = hero.get();
            }
        }
    }

    for (auto const& villager : villagers)
    {
        if(villager.isActive())
        {
            int distance = getDistance(currentLocation , villager.getLocation());
            if (distance < minDistance)
            {
                minDistance = distance;
                nearestVillager = const_cast<Villager*>(&villager);
                nearestHero = nullptr;
            }
        }
    }

    return {nearestHero , nearestVillager};
}

vector<Location> Map::getNeighboringPlaces(Location i_location) noexcept
{
    vector<Location> places;
    for (int i = 0 ; i < 19 ; ++i)
    {
        Location location = static_cast<Location>(i);
        if (getDistance(i_location , location) == 1)
        {
            places.push_back(location);
        }
    }
    
    return places;
}

void Map::increaseHorror()
{
    ++levelOfHorror;
    if (levelOfHorror > 5)
    {
        throw std::runtime_error("Horror level cannot be greater than 5");
    }
}

int Map::getHorroLevel() noexcept
{
    return levelOfHorror;
}

string Map::locationToString(Location i_location) noexcept
{
    switch(i_location)
    {
        case Location::DOCKS:      
            return "DOCKS";

        case Location::CAMP:       
            return "CAMP";

        case Location::INN:        
            return "INN";

        case Location::MANSION:    
            return "MANSION";

        case Location::ABBEY:      
            return "ABBEY";

        case Location::MUSEUM:     
            return "MUSEUM";

        case Location::THEATRE:    
            return "THEATRE";

        case Location::GRAVEYARD:  
            return "GRAVEYARD";

        case Location::BARN:       
            return "BARN";

        case Location::SHOP:       
            return "SHOP";

        case Location::PRECINCT:   
            return "PRECINCT";

        case Location::INSTITUTE:  
            return "INSTITUTE";

        case Location::LABORATORY: 
            return "LABORATORY";

        case Location::TOWER:      
            return "TOWER";

        case Location::CAVE:       
            return "CAVE";

        case Location::DUNGEON:    
            return "DUNGEON";

        case Location::CRYPT:      
            return "CRYPT";

        case Location::CHURCH:     
            return "CHURCH";

        case Location::HOSPITAL:   
            return "HOSPITAL";

        default:
            return "UNKNOWN";
    }
}

array<vector<string> , 4> Map::getLocationBelongings(const array<Item , 35>& items, const array<unique_ptr<Monster> , 2>& monsters , const array<Villager , 7>& villagers , const array<unique_ptr<Hero> , 2>& heros , Location location) noexcept
{
    array<vector<string> , 4> belongings;
    for (auto const& item : items)
    {
        if (item.getLocation() == location && item.getItemStatus() == ItemStatus::ON_BOARD)
        {
            belongings[0].push_back(item.getItemName());
        }
    }
    for (auto const& monster : monsters)
    {
        if (monster->isActive() && monster->getLocation() == location)
        {
            belongings[1].push_back(monsterNameToString(monster->getName()));
        }
    }
    for (auto const& villager : villagers)
    {
        if (villager.isActive() && villager.getLocation() == location)
        {
            belongings[2].push_back(villagerNameToString(villager.getName()));
        }
    }
    for (auto const& hero : heros)
    {
        if (hero->getLocation() == location)
        {
            belongings[3].push_back(hero->heroNameToString(hero->getName()));
        }
    }

    return belongings;
}

void Map::printLocationBelongings(const array<Item , 35>& items, const array<unique_ptr<Monster> , 2>& monsters , const array<Villager , 7>& villagers , const array<unique_ptr<Hero> , 2>& heros , Location location) noexcept
{
    auto belongings = getLocationBelongings(items , monsters , villagers , heros , location);
    for (size_t i = 0 ; i < belongings[0].size() || i < belongings[1].size() || i < belongings[2].size() || i < belongings[3].size() ; ++i)
    {
        if (i != 0)
        {
            cout << left << setw(15) << "|";
        }
        else
        {
            cout << "|   " << left << setw(11) << locationToString(location);
        }
        if (i < belongings[0].size())
        {
            cout << left << setw(23) << belongings[0][i];
        }
        else
        {
            cout << left << setw(23) << "_";
        }
        if (i < belongings[1].size())
        {
            cout << left << setw(14) << belongings[1][i];
        }
        else
        {
            cout << left << setw(14) << "_";
        }
        if (i < belongings[2].size())
        {
            cout << left << setw(15) << belongings[2][i];
        }
        else
        {
            cout << left << setw(15) << "_";
        }
        if (i < belongings[3].size())
        {
            cout << left << setw(14) << belongings[3][i];
        }
        else
        {
            cout << left << setw(14) << "_";
        }
        cout << "|\n";

    }
}

Location Map::findLocationWithMostItems(const std::array<Item,35>& items) noexcept
{
    std::array<int , 19> counts{};
    for (auto const& item : items)
    {
        if (item.getItemStatus() == ItemStatus::ON_BOARD)
        {
            ++counts[static_cast<int>(item.getLocation())];
        }
    }

    int maxCount = counts[0];
    int maxIndex = 0;
    for (int i = 1; i < 19; ++i)
    {
        if (counts[i] > maxCount)
        {
            maxCount = counts[i];
            maxIndex = i;
        }
    }

    return static_cast<Location>(maxIndex);
}

int Map::getDistance(Location origin, Location destination) noexcept
{
    return distances[static_cast<size_t>(origin)][static_cast<size_t>(destination)];
}