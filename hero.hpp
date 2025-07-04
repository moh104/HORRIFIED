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
        
        void setOwner(const std::string& owner);
        std::string getOwner() const noexcept;
        HeroName getName() const noexcept;
        std::string heroNameToString(HeroName name) const noexcept;
        int getActions() const noexcept;
        int getActionsLeft() const noexcept;
        bool receiveAttack() noexcept;
        Location getLocation() const noexcept;
        void move(Location newLocation) noexcept;
        void guide(const std::vector<Villager*>&);
        void pickUpItem(const std::array<Item* , 35>&);
        void advanceTask(Monster*);
        void defeatMonster(Monster*);
        std::vector<std::string> getItems() const;
        std::vector<std::string> getPerks() const;
        void movement(int moveCount , Location target) noexcept;
        void setLocation(Location);
        void setActionsLeft(int n);
        void HavePerkCard( Perk perk );
        std::vector<Perk> GetPerk();

        virtual ~Hero() = default;
};

#endif