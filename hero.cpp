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

void Hero::defeatMonster(Monster* monster) {
    if (monster->getName() == MonsterName::DRACULA)
    {
        try
        {
            std::vector <Item> sendItem;
            int a = 1;
            for (size_t i = 0; i < items.size(); i++)
            {
                std::cout << a << ". " << items[i].getItemName() << std::endl;
                a++;
            }
            for (size_t i = 0; i < items.size(); i++)
            {
                std::cout << "Enter the Item you want to use (100 for end):" ;
                int entekhab;
                std::cin >> entekhab;
                if (entekhab == 100)
                {
                    break;
                }
                sendItem.push_back(items[entekhab - 1]);
            }
            
            monster->receiveDefeat(location , sendItem);
            actionsLeft--;
            for (size_t i = 0; i < sendItem.size(); i++)
            {
                for (size_t j = 0; j < items.size(); j++)
                {
                    if (items[j].getItemName() == sendItem[i].getItemName())
                    {
                        items.erase(items.begin() + j);
                    }
                }  
            }
            
        }
        catch(std::invalid_argument &e)
        {
            std::cerr << e.what() << '\n';
        }
        catch(std::logic_error &e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    else{
        try
        {
            std::vector <Item> sendItem;
            int a = 1;
            for (size_t i = 0; i < items.size(); i++)
            {
                std::cout << a << ". " << items[i].getItemName() << std::endl;
                a++;
            }
            for (size_t i = 0; i < items.size(); i++)
            {
                std::cout << "Enter the Item you want to use (100 for end):" ;
                int entekhab;
                std::cin >> entekhab;
                if (entekhab == 100)
                {
                    break;
                }
                sendItem.push_back(items[entekhab - 1]);
            }
            
            monster->receiveDefeat(location , sendItem);
            actionsLeft--;
            for (size_t i = 0; i < sendItem.size(); i++)
            {
                for (size_t j = 0; j < items.size(); j++)
                {
                    if (items[j].getItemName() == sendItem[i].getItemName())
                    {
                        items.erase(items.begin() + j);
                    }
                }  
            }
            
        }
        catch(std::invalid_argument &e)
        {
            std::cerr << e.what() << '\n';
        }
        catch(std::logic_error &e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
}

void Hero::pickUpItem(const std::array<Item* , 35>& AllItems)
{ 
    if (name == HeroName::ARCHAEOLOGIST)
    {
        std::vector<Location> near = Map::getNeighboringPlaces(location);
        std::vector<Item*> Wanted;
        near.push_back(location);
        std::cout << "there is the items you can pick :" << std::endl;
        int a = 1;
        for (size_t i = 0; i < AllItems.size(); i++)
        {
            for (size_t j = 0; j < near.size(); j++)
            {
                
                if (AllItems[i]->getItemStatus()==ItemStatus::ON_BOARD && AllItems[i]->getLocation() == near[j])
                {
                    std::cout << a << ". " << AllItems[i]->getItemName() << std::endl;
                    Wanted.push_back(AllItems[i]);
                    a++;
                }
            }
        }
        int itemWant;
        while (true)
        {
            std::cout << "Enter what Items you want to pick (100 for end):";
            std::cin >> itemWant;
            if (itemWant == 100)
            {
                break;
            }
            if (Wanted[itemWant - 1]->getItemStatus() == ItemStatus::IN_INVENTORY)
            {
                continue;
            }
            else{
                Wanted[itemWant - 1]->setItemStatus(ItemStatus::IN_INVENTORY);
                items.push_back(*Wanted[itemWant - 1]);
                
            }
            
        }
        
    }
    
    if (name == HeroName::MAYOR)
    {
        std::vector<Item*> Wanted;

        int a = 1;
        for (size_t i = 0; i < AllItems.size(); i++)
        {
            
            if (AllItems[i]->getItemStatus()==ItemStatus::ON_BOARD && AllItems[i]->getLocation() == location)
            {
                std::cout << a << ". " << AllItems[i]->getItemName() << std::endl;
                Wanted.push_back(AllItems[i]);
                a++;
            }
        }
        int itemWant;
        while (true)
        {
            std::cout << "Enter what Items you want to pick (100 for end):";
            std::cin >> itemWant;
            if (itemWant == 100)
            {
                break;
            }
            if (Wanted[itemWant - 1]->getItemStatus() == ItemStatus::IN_INVENTORY)
            {
                continue;
            }
            else{
                Wanted[itemWant - 1]->setItemStatus(ItemStatus::IN_INVENTORY);
                items.push_back(*Wanted[itemWant - 1]);
                
            }
            
        }
    }
    
    actionsLeft--;
}