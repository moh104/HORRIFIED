#ifndef VILLAGER_HPP
#define VILLAGER_HPP

#include <iostream>
#include "map.hpp"

enum class VillagerName{
    WILBURANDCHICK,
    MALEVA,
    DRCRANLY,
    FRITZ,
    MARIA,
    PROFPEARSON,
    DRREAD
};

std::string villagerNameToString(VillagerName);


class Villager
{
    private:
        VillagerName name;
        Location location;
        Location safe_location;
        bool isAlive = true ;
        bool Active = false ;

    public:
        Villager(VillagerName , Location , Location);
        void Move(int moveCount , const Location&) noexcept;
        VillagerName getName() const;
        Location getLocation() const;
        Location getSafeLocation()const;
        void setLocation(Location);
        void receiveAttack() noexcept;
        void activate();
        bool isActive() const;
        void DisActive();
        void movement(int moveCount , Location target) noexcept;
        ~Villager(){};
};

#endif