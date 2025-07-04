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