#ifndef HERO_HPP
#define HERO_HPP


#include "perk.hpp"
#include <string>
#include <vector>
#include "item.hpp"
#include "map.hpp"


enum class HeroName{
    ARCHAEOLOGIST,
    MAYOR
};


class Hero
{
    private:
        std::string owner;
        HeroName name;
        Location location;
        int actionsLeft;
        std::vector<Item> items;
        std::vector<Perk> perks;

    public:
        Hero( HeroName name , Location startLocation) noexcept;

        virtual ~Hero() = default;
};

#endif