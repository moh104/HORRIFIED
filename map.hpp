#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <array>
#include <memory>
#include <string>


class Monster;
class Villager;
class Hero;
class Item;

enum class Location {
    DOCKS,
    CAMP,
    INN,
    MANSION,
    ABBEY,
    MUSEUM,
    THEATRE,
    GRAVEYARD,
    BARN,
    SHOP,
    PRECINCT,
    INSTITUTE,
    LABORATORY,
    TOWER,
    CAVE,
    DUNGEON,
    CRYPT,
    CHURCH,
    HOSPITAL,
};

class Map
{
    private:
        static constexpr std::array<std::array<int , 19> , 19> distances = {
                            //DOCKS CAMP INN MANSION ABBEY MUSEUM THEATRE GRAVEYARD BARN SHOP PRECINCT INSTITUTE LABORATORY TOWER CAVE DUNGEON CRYPT CHURCH HOSPITAL
        std::array<int , 19>{ 0     ,3   ,3   ,3      ,4    ,4     ,2      ,5        ,3   ,3   ,3       ,5        ,4         ,1    ,4   ,2      ,5    ,4     ,5     }, //DOCKS
        std::array<int , 19>{ 3     ,0   ,1   ,1      ,2    ,2     ,1      ,3        ,2   ,2   ,1       ,4        ,3         ,2    ,1   ,3      ,3    ,2     ,3     }, //CAMP
        std::array<int , 19>{ 3     ,1   ,0   ,1      ,2    ,2     ,1      ,3        ,2   ,2   ,1       ,4        ,3         ,2    ,2   ,3      ,3    ,2     ,3     }, //INN
        std::array<int , 19>{ 3     ,1   ,1   ,0      ,1    ,1     ,1      ,2        ,2   ,1   ,1       ,3        ,2         ,2    ,2   ,3      ,2    ,1     ,2     }, //MANSION
        std::array<int , 19>{ 4     ,2   ,2   ,1      ,0    ,2     ,2      ,3        ,3   ,2   ,2       ,4        ,3         ,3    ,3   ,4      ,1    ,2     ,3     }, //ABBEY
        std::array<int , 19>{ 4     ,2   ,2   ,1      ,2    ,0     ,2      ,2        ,3   ,1   ,2       ,3        ,2         ,3    ,3   ,4      ,3    ,1     ,2     }, //MUSEUM
        std::array<int , 19>{ 2     ,1   ,1   ,1      ,2    ,2     ,0      ,3        ,1   ,1   ,1       ,3        ,2         ,1    ,2   ,2      ,3    ,2     ,3     }, //THEATRE
        std::array<int , 19>{ 5     ,3   ,3   ,2      ,3    ,2     ,3      ,0        ,4   ,2   ,3       ,4        ,3         ,4    ,4   ,5      ,4    ,1     ,2     }, //GRAVEYARD
        std::array<int , 19>{ 3     ,2   ,2   ,2      ,3    ,3     ,1      ,4        ,0   ,2   ,2       ,4        ,3         ,2    ,3   ,3      ,4    ,3     ,4     }, //BARN
        std::array<int , 19>{ 3     ,2   ,2   ,1      ,2    ,1     ,1      ,2        ,2   ,0   ,2       ,2        ,1         ,2    ,3   ,3      ,3    ,1     ,2     }, //SHOP
        std::array<int , 19>{ 3     ,1   ,1   ,1      ,2    ,2     ,1      ,3        ,2   ,2   ,0       ,4        ,3         ,2    ,2   ,3      ,3    ,2     ,3     }, //PRECINCT
        std::array<int , 19>{ 5     ,4   ,4   ,3      ,4    ,3     ,3      ,4        ,4   ,2   ,4       ,0        ,1         ,4    ,5   ,5      ,5    ,3     ,4     }, //INSTITUTE
        std::array<int , 19>{ 4     ,3   ,3   ,2      ,3    ,2     ,2      ,3        ,3   ,1   ,3       ,1        ,0         ,3    ,4   ,4      ,4    ,2     ,3     }, //LABORATORY
        std::array<int , 19>{ 1     ,2   ,2   ,2      ,3    ,3     ,1      ,4        ,2   ,2   ,2       ,4        ,3         ,0    ,3   ,1      ,4    ,3     ,4     }, //TOWER
        std::array<int , 19>{ 4     ,1   ,2   ,2      ,3    ,3     ,2      ,4        ,3   ,3   ,2       ,5        ,4         ,3    ,0   ,4      ,4    ,3     ,4     }, //CAVE
        std::array<int , 19>{ 2     ,3   ,3   ,3      ,4    ,4     ,2      ,5        ,3   ,3   ,3       ,5        ,4         ,1    ,4   ,0      ,5    ,4     ,5     }, //DUNGEON
        std::array<int , 19>{ 5     ,3   ,3   ,2      ,1    ,3     ,3      ,4        ,4   ,3   ,3       ,5        ,4         ,4    ,4   ,5      ,0    ,3     ,4     }, //CRYPT
        std::array<int , 19>{ 4     ,2   ,2   ,1      ,2    ,1     ,2      ,1        ,3   ,1   ,2       ,3        ,2         ,3    ,3   ,4      ,3    ,0     ,1     }, //CHURCH
        std::array<int , 19>{ 5     ,3   ,3   ,2      ,3    ,2     ,3      ,2        ,4   ,2   ,3       ,4        ,3         ,4    ,4   ,5      ,4    ,1     ,0     }, //HOSPITAL
        };

        static int levelOfHorror;

        static std::array<std::vector<std::string> , 4> getLocationBelongings(const std::array<Item , 35>& items, const std::array<std::unique_ptr<Monster> , 2>& monsters , const std::array<Villager , 7>& villagers , const std::array<std::unique_ptr<Hero> , 2>& heros , Location location) noexcept;
        static void printLocationBelongings(const std::array<Item , 35>& items, const std::array<std::unique_ptr<Monster> , 2>& monsters , const std::array<Villager , 7>& villagers , const std::array<std::unique_ptr<Hero> , 2>& heros , Location location) noexcept;
};

#endif