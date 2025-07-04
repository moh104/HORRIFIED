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

void Map::draw(const array<Item , 35>& items, const array<unique_ptr<Monster> , 2>& monsters , const array<Villager , 7>& villagers , const array<unique_ptr<Hero> , 2>& heros) noexcept
{
    cout << "+-----------------------------------------------------------+-------------------------------------------------------+" << '\n'
         << "|                                                           |                                                       |" << '\n'
         << "|                   Terror Level: [" << levelOfHorror << "]                       |                  Heros Information                    |" << '\n'
         << "|                                                           |    -----------------------------------------------    |" << '\n'
         << "|                                                           | 1)Hero: " << left << setw(18) << heros[0]->heroNameToString(heros[0]->getName()) << "* 2)Hero: " << setw(18) << heros[1]->heroNameToString(heros[1]->getName()) << "|" << '\n'
         << "|  CAVE======CAMP    INN    PRECINCT     BARN      DUNGEON  |   Actions left: " << heros[0]->getActionsLeft() << '/' << heros[0]->getActions() << "       *  Actions left: " << heros[1]->getActionsLeft() << '/' << heros[1]->getActions() << "        |" << '\n'
         << "|              |      |        |          |           |     |   Items:                  *  Items:                   |" << '\n';

    array <string , 12> restMap = {
        "|              ========================THEATRE======TOWER   |    ",
        "|              |                          |           |     |    ",
        "|  ABBEY====MANSION======================SHOP       DOCKS   |    ",
        "|    |               |         |          |                 |    ",
        "|  CRYPT          MUSEUM       |    LABORATORY====INSTITUTE |    ",
        "|                              |                            |    ",
        "|              HOSPITAL=====CHURCH=====GRAVEYARD            |    ",
        "|                                                           |    ",
        "+-----------------------------------------------------------+-------------------------------------------------------+",
        "|                      ACTION MENU                          |                        VILLAGERS                      |",
        "|   [M]ove  |   [G]uide |   [P]ick Up   |   [A]dvance       |    ",
        "|   [D]efeat    |   [U]se Perk  |   [H]elp  |   [Q]uit      |    "
    };

    size_t i = 0;
    vector<string> items1 = heros[0]->getItems();
    vector<string> items2 = heros[1]->getItems();
    for (size_t j = 0 ; j < items1.size() || j < items2.size() ; ++j)
    {
        if (i > 7)
        {
            cout << restMap[7] << setw(23) << (j < items1.size() ? items1[j] : " ") << '*' << "   " << setw(24) << (j < items2.size() ? items2[j] : " ") << "|\n";
        }
        else
        {
            cout << restMap[i++] << setw(23) << (j < items1.size() ? items1[j] : " ")  << '*' << "   " << setw(24) << (j < items2.size() ? items2[j] : " ") << "|\n" ;
        }
    }

    vector<string> perks1 = heros[0]->getPerks();
    vector<string> perks2 = heros[1]->getPerks();
    if (i > 7)
    {
        cout << restMap[7].substr(0 , restMap[7].size() - 1) << setw(24) << "Perks:" << setw(28) << "*  Perks:" << "|\n";
    }
    else
    {
        cout << restMap[i++].substr(0 , restMap[7].size() - 1) << setw(24) << "Perks:" << setw(28) << "*  Perks:" << "|\n";
    }
    for (size_t j = 0 ; j < perks1.size() || j < perks2.size() ; ++j)
    {
        if (i > 7)
        {
            cout << restMap[7] << setw(23) << (j < perks1.size() ? perks1[j] : " ")  << '*' << "   " << setw(24) << (j < perks2.size() ? perks2[j] : " ")  << "|\n";
        }
        else
        {
            cout << restMap[i++] << setw(23) << (j < perks1.size() ? perks1[j] : " ")  << '*' << "   " << setw(24) << (j < perks2.size() ? perks2[j] : " ")  << "|\n";
        }
    }

    for (; i < 8 ; ++i)
    {
        cout << restMap[i] << "                                                   |\n";
    }

    cout << restMap[i++] << '\n';
    cout << restMap[i++] << '\n';
    cout << restMap[8] << '\n';

    for (auto const& villager : villagers)
    {
        if (i > 11)
        {
            cout << restMap[7] << left << setw(16) << (villagerNameToString(villager.getName()) + ": ") << setw(35) << locationToString(villager.getSafeLocation()) << "|\n";
        }
        else
        {
            cout << restMap[i++] << left << setw(16) << (villagerNameToString(villager.getName()) + ": ") << setw(35) << locationToString(villager.getSafeLocation()) << "|\n";
        }
    }

    for (; i < 12 ; ++i)
    {
        cout << restMap[i] << "                                                   |\n";
    }

    cout << restMap[8] << '\n';

    cout << " _______________________________ Location Overview ______________________________\n"
         << "|   Location   Items                  Monsters      Villagers      Heros         |\n"
         << "|________________________________________________________________________________|\n";
    printLocationBelongings(items , monsters , villagers , heros , Location::DOCKS);
    printLocationBelongings(items , monsters , villagers , heros , Location::CAMP);
    printLocationBelongings(items , monsters , villagers , heros , Location::INN);
    printLocationBelongings(items , monsters , villagers , heros , Location::MANSION);
    printLocationBelongings(items , monsters , villagers , heros , Location::ABBEY);
    printLocationBelongings(items , monsters , villagers , heros , Location::MUSEUM);
    printLocationBelongings(items , monsters , villagers , heros , Location::THEATRE);
    printLocationBelongings(items , monsters , villagers , heros , Location::GRAVEYARD);
    printLocationBelongings(items , monsters , villagers , heros , Location::BARN);
    printLocationBelongings(items , monsters , villagers , heros , Location::SHOP);
    printLocationBelongings(items , monsters , villagers , heros , Location::PRECINCT);
    printLocationBelongings(items , monsters , villagers , heros , Location::INSTITUTE);
    printLocationBelongings(items , monsters , villagers , heros , Location::LABORATORY);
    printLocationBelongings(items , monsters , villagers , heros , Location::TOWER);
    printLocationBelongings(items , monsters , villagers , heros , Location::CAVE);
    printLocationBelongings(items , monsters , villagers , heros , Location::DUNGEON);
    printLocationBelongings(items , monsters , villagers , heros , Location::CRYPT);
    printLocationBelongings(items , monsters , villagers , heros , Location::CHURCH);
    printLocationBelongings(items , monsters , villagers , heros , Location::HOSPITAL);
    cout << "|                                                                                |\n"
         << "|________________________________________________________________________________|\n"
         << "|   KEY LOCATIONS:                                                               |\n";
    
    for (auto const& monster : monsters)
    {
        if (monster->getName() == MonsterName::DRACULA)
        {
            cout << "|  ";
            string result = "[ ";
            auto draculaMat = monster->getMatStatus();
            for (auto const& part : draculaMat)
            {
                if (!part.second)
                {
                    result += locationToString(part.first);
                    result += " ";
                }
            }
            result += "]";
            cout << left << setw(41) << result << setw(20) << " Coffins smashed:" << " (" << monster->numOfPartsSolved() << setw(14) << "/4)" << "|\n";
        }
        else if (monster->getName() == MonsterName::INVISIBLEMAN)
        {
            cout << "|  ";
            string result = "[ ";
            auto invisibleManMat = monster->getMatStatus();
            for (auto const& part : invisibleManMat)
            {
                if (!part.second)
                {
                    result += locationToString(part.first);
                    result += " ";
                }
            }
            result += "]";
            cout << left << setw(41) << result << setw(20) << " Evidence collected:" << " (" << monster->numOfPartsSolved() << setw(14) << "/4)" << "|\n";
        }
    }

    cout << "|________________________________________________________________________________|" << endl;
    
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