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

void Hero::move(Location newLocation ) noexcept {
    location = newLocation;
    std::cout << owner << " moved" << std::endl;
    actionsLeft--;
}

void Hero::movement (int moveCount , Location target) noexcept
{
    int distance = Map::getDistance(location , target);

    if(moveCount >= distance)
    {
        location = target;
        return;
    }

    for (int i = 0 ; i < 19 ; ++i)
    {
        Location otherLocation = static_cast<Location>(i);
        distance = Map::getDistance(location , otherLocation);
        int remainingDistance = Map::getDistance(otherLocation , target);
        if (distance == moveCount && remainingDistance == (Map::getDistance(location , target) - moveCount))
        {
            location = otherLocation;
        }
    }
}

void Hero::guide(const std::vector<Villager*>& villagers)
{
    std::vector <Location> nearlocations = Map::getNeighboringPlaces(location) ;

    std::vector <Villager*> nearVillager;
    std::vector <Villager*> inVillagers;

    
    for(size_t i = 0 ; i < nearlocations.size() ; i++){
        for (size_t j = 0 ; j < villagers.size() ; j++) {
            if ( villagers[j]->getLocation() == nearlocations[i] ) {
                nearVillager.push_back(villagers[j]);
            }
        }
    }

    for(size_t i=0 ; i < villagers.size() ; i++){
        if(location == villagers[i]->getLocation()){
            inVillagers.push_back(villagers[i]);
        }
    }

    std::cout << "You can guide this villagers :" << std::endl;
    int a = 1;
    for( size_t i = 0 ; i < nearVillager.size() ; i++){
        std::cout << a << ". " << villagerNameToString(nearVillager[i]->getName()) << std::endl;
        a++;
    }
    for (size_t i = 0; i < inVillagers.size(); i++)
    {
        std::cout << a << ". " << villagerNameToString(inVillagers[i]->getName()) << std::endl;
        a++;
    }
    

    int choice;
    std::cout << "What Villager you want to guide?";
    std::cin >> choice;
    if (choice > static_cast<int>(nearVillager.size() + inVillagers.size()))
    {
        std::cout << "Enter a correct choice!!";
        std::cin >> choice;
    }
    
    if (choice <= static_cast<int>(nearVillager.size() ) )
    {
        nearVillager[choice - 1]->setLocation(location);
    }
    else{
        int a = 1;
        std::cout << "There is the locations villager can go :" << std::endl;
        for (size_t i = 0 ; i < nearlocations.size() ; i ++){
            std::cout << a << ". " << Map::locationToString(nearlocations[i]) << std::endl; 
            a++;
        }
        std::cout << "Enter location that villager should go :" ;
        int choose;
        std::cin >> choose;
        if (choose > static_cast<int>(nearlocations.size()))
        {
            std::cout << "Enter a correct choice!!";
            std::cin >> choose;
        }
        inVillagers[choice - 1 - nearVillager.size()]->setLocation(nearlocations[choose - 1]);
        
    }

    actionsLeft--;
}

void Hero::advanceTask(Monster* monster) {
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
            
            monster->receiveAdvance(location , sendItem);
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
            std::vector <Item> entekhabi;
            int a = 1;
            for (size_t i = 0; i < items.size(); i++)
            {
                std::cout << a << ". " << items[i].getItemName() << std::endl;
                a++;
            }
            std::cout << "Enter the Item you want to place :" ;
            int entekhab;
            std::cin >> entekhab;
            entekhabi.push_back(items[entekhab - 1]);
            monster->receiveAdvance(location , entekhabi);
            actionsLeft--;
            items.erase(items.begin() + entekhab - 1);
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

bool Hero::receiveAttack() noexcept{

    std::cout << "Do you want to use perk ?[Y/N]";
    std::string answer;
    std::cin >> answer;
    if (answer == "Y")
    {
        if (perks.empty())
        {
            setLocation(Location::HOSPITAL);
            return true;
        }
        
        std::cout << "There is your Perk cards :" << std::endl;
        int a = 1;
        for (Perk& perk : perks)
        {
            std::cout << a << ". " << perk.NameToString(perk.getName()) << std::endl;
            a++;
        }
        std::cout << "Choose the perk you want to use :";
        int perk;
        std::cin >> perk;
        perks.erase( perks.begin()+ perk - 1);
        return false;
    }
    
    else{
        setLocation(Location::HOSPITAL);
        return true;
    }
}

std::string Hero::heroNameToString(HeroName name) const noexcept
{
    switch (name)
    {
        case HeroName::ARCHAEOLOGIST:
            return "Archaeologist";
        case HeroName::MAYOR:
            return "Mayor";
        default:
            return "";
            break;
    }
}



void Hero::HavePerkCard( Perk perk )
{
    perks.push_back(perk);
    perk.Activation();
}