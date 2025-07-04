#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "map.hpp"

enum class ItemType {RED , YELLOW , BLUE};
enum class ItemStatus {ON_BOARD , OUT_GAME , DISCARDED , IN_INVENTORY};

class Item
{
    private:
        std::string name;
        ItemType type;
        int strength;
        Location location;
        ItemStatus status = ItemStatus::OUT_GAME;
        
    public:
        Item(const std::string& name , ItemType type , int power , Location location);
        std::string getItemName() const noexcept;
        ItemType getItemType() const;
        int getStrength() const;
        Location getLocation() const;
        void setLocation(Location newLocation);
        void activate();
        void removeItem();
        ItemStatus getItemStatus() const noexcept;
        void setItemStatus(ItemStatus) noexcept;

};

#endif