#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <iostream>
#include <array>
#include <memory>
#include <unordered_map>
#include "map.hpp"
#include "hero.hpp"
#include "villager.hpp"
#include "item.hpp"

enum class MonsterName {
    DRACULA,
    INVISIBLEMAN,
    FRENZY
};

std::string monsterNameToString(MonsterName name) noexcept;

class Monster
{
    public:
        Monster(MonsterName i_name , Location i_location , ItemType color , int i_requiredItemStrength , std::unordered_map<Location , bool> i_matStatus);

        MonsterName getName() const noexcept;
        Location getLocation() const noexcept;
        void setLocation(Location location) noexcept;
        void movement(int moveCount , Location target) noexcept;
        bool attack(Hero* hero , Villager* villager) const noexcept;
        virtual void power(const std::array<Villager , 7>& villagers , Hero* currentHero) = 0;
        virtual void receiveAdvance(Location heroLocation , const std::vector<Item>& items) = 0;
        virtual void receiveDefeat(Location heroLocation , const std::vector<Item>& items);
        bool isActive() const noexcept;
        void kill() noexcept;
        const std::unordered_map<Location , bool>& getMatStatus() const noexcept;
        void setRequiredItemStrength(int);
        unsigned int numOfPartsSolved() const noexcept;
        void doOperationOnMat(Location location);
        virtual void clearMarkedVillager() noexcept{}

        virtual ~Monster() = default;
    private:
        MonsterName name;
        Location location;
        ItemType requiredItemType;
        int requiredItemStrength;
        bool active = true;
        std::unordered_map<Location,bool> matStatus;
};

#endif