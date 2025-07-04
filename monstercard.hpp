#ifndef MONSTERCARD_HPP
#define MONSTERCARD_HPP

#include <vector>
#include "monster.hpp"

enum class MonsterCardName{
    FORMOFTHEBAT,
    SUNRISE,
    THIEF,
    THEDELIVERY,
    FORTUNETELLER,
    FORMEREMPLOYER,
    HURRIEDASSISTANT,
    THEINNOCENT,
    EGYPTIANEXPERT,
    THEICHTHYOLOGIST,
    HYPNOTICGAZE,
    ONTHEMOVE
};
std::string monsterCardToString(MonsterCardName card) noexcept;

class MonsterCard
{
    private:
        MonsterCardName name;
        int quantity;
        int newItems;
        int strikeMove;
        int strikeDice;
        std::vector<MonsterName> strikeOrder;

    public:
        MonsterCard(MonsterCardName i_name , int i_quantity , int i_newItems , int i_strikeMove , int i_strikeDice , std::vector<MonsterName> strikeOrder);
};

#endif