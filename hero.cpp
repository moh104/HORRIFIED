#include <iostream>
#include <algorithm>
#include <climits>
#include <cmath>
#include "hero.hpp"
#include "map.hpp"
#include "game.hpp"


Hero::Hero( HeroName name , Location startLocation) noexcept
    : name(name), location(startLocation), actionsLeft(0) {}

void Hero::setOwner(const std::string& n)
{
    if (n.empty())
    {
        throw std::invalid_argument("Hero name cannot be empty");
    }
    else
    {
        owner = n;
    }
}

void Hero::setLocation(Location loc)
{
    location = loc;
}

void Hero::setActionsLeft(int n)
{
    actionsLeft = n;
}

Location Hero::getLocation() const noexcept{
    return location;
}

int Hero::getActionsLeft() const noexcept {
    return actionsLeft;
}

std::string Hero::getOwner() const noexcept
{
    return owner;
}

HeroName Hero::getName()const noexcept{
    return name;
}

std::vector<std::string> Hero::getItems() const{
    std::vector < std::string > ItemNames;
    for (size_t i = 0; i < items.size(); i++)
    {
        ItemNames.push_back(items[i].getItemName());
    }
    return ItemNames;

}

std::vector<std::string> Hero::getPerks() const{
    std::vector < std::string > PerkNames;
    for (size_t i = 0; i < perks.size(); i++)
    {
        PerkNames.push_back(perks[i].NameToString(perks[i].getName()));
    }
    return PerkNames;
}

int Hero::getActions()const noexcept{
    if (getName() == HeroName::ARCHAEOLOGIST)
    {
        return 4;
    }
    if (getName() == HeroName::MAYOR)
    {
        return 5;
    }
    else{
        return 0;
    }
}

std::vector<Perk> Hero::GetPerk()
{
    return perks;
}