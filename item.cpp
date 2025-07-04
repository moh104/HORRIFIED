#include <string>
#include "item.hpp"

Item::Item(const std::string& name, ItemType type, int strength, Location location)
    : name(name), type(type), strength(strength), location(location) {}

std::string Item::getItemName() const noexcept{ 
    int p = strength;
    std::string strength = std::to_string(p);
    std::string Return = name + "(" + strength + ")";
    return Return;     
}
ItemType Item::getItemType() const { return type; }
int Item::getStrength() const { return strength; }
Location Item::getLocation() const { return location; }
void Item::setLocation(Location newLocation) { location = newLocation; }

void Item::activate()
{
    status = ItemStatus::ON_BOARD;
}

void Item::removeItem(){
    status = ItemStatus::DISCARDED;
}

ItemStatus Item::getItemStatus() const noexcept
{
    return status;
}

void Item::setItemStatus(ItemStatus i_status) noexcept
{
    status = i_status;
}