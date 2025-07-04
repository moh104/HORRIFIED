#ifndef DRACULA_HPP
#define DRACULA_HPP

#include <unordered_map>
#include "monster.hpp"

class Dracula : public Monster
{
        static constexpr int REQUIRED_RED_STRENGTH = 6;
    public:
        explicit Dracula (Location initialLocation);
        
        virtual void receiveAdvance(Location heroLocation , const std::vector<Item>& items) override;
        virtual void power(const std::array<Villager , 7>& villagers , Hero* currentHero) override;
};

#endif