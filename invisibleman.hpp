#ifndef INVISIBLEMAN_HPP
#define INVISIBLEMAN_HPP

#include <unordered_map>
#include "monster.hpp"

class InvisibleMan : public Monster
{
    private:
        Villager* markedVillager = nullptr;

    public:
        InvisibleMan(Location i_location);

        virtual void receiveAdvance(Location heroLocation , const std::vector<Item>& items) override;
        virtual void power(const std::array<Villager , 7>& villagers , Hero* currentHero) override;
        virtual void clearMarkedVillager() noexcept override;
};

#endif