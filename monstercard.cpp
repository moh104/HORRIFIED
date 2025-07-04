#include "monstercard.hpp"

using namespace std;

MonsterCard::MonsterCard(MonsterCardName i_name , int i_quantity , int i_newItems , int i_strikeMove , int i_strikeDice , std::vector<MonsterName> i_strikeOrder) : name(i_name)
{
    setQuantity(i_quantity);
    setNewItems(i_newItems);
    setStrikeMove(i_strikeMove);
    setStrikeDice(i_strikeDice);
    setStrikeOrder(i_strikeOrder);
}

void MonsterCard::setQuantity(int i_quantity)
{
    if (i_quantity <= 0 || i_quantity > 5)
    {
        throw std::invalid_argument("Invalid quantity entered");
    }
    quantity = i_quantity;
}
void MonsterCard::setNewItems(int i_newItems)
{
    if (i_newItems < 0 || i_newItems > 3)
    {
        throw std::invalid_argument("Invalid number of new items entered");
    }
    newItems = i_newItems;
}
void MonsterCard::setStrikeMove(int i_strikeMove)
{
    if (i_strikeMove <= 0 || i_strikeMove > 3)
    {
        throw std::invalid_argument("Invalid move count entered");
    }
    strikeMove = i_strikeMove;
}
void MonsterCard::setStrikeDice(int i_strikeDice)
{
    if (i_strikeDice <= 0 || i_strikeDice > 3)
    {
        throw std::invalid_argument("Invalid number of dice entered");
    }
    strikeDice = i_strikeDice;
}
void MonsterCard::setStrikeOrder(std::vector<MonsterName> order)
{
    if (order.empty())
    {
        throw std::invalid_argument("At least 1 monster must be on strike");
    }
    strikeOrder = order;
}

MonsterCardName MonsterCard::getName() const noexcept
{
    return name;
}
int MonsterCard::getQuantity() const noexcept
{
    return quantity;
}
int MonsterCard::getNewItems() const noexcept
{
    return newItems;
}
int MonsterCard::getStrikeMove()  const noexcept
{
    return strikeMove;
}
int MonsterCard::getStrikeDice()  const noexcept
{
    return strikeDice;
}
const std::vector<MonsterName>& MonsterCard::getStrikeOrder() const noexcept
{
    return strikeOrder;
}

string monsterCardToString(MonsterCardName card) noexcept
{
    switch(card)
    {
        case MonsterCardName::FORMOFTHEBAT:      
            return "FORMOFTHEBAT";

        case MonsterCardName::SUNRISE:       
            return "SUNRISE";

        case MonsterCardName::THIEF:
            return "THIEF";

        case MonsterCardName::THEDELIVERY:    
            return "THEDELIVERY";

        case MonsterCardName::FORTUNETELLER:      
            return "FORTUNETELLER";

        case MonsterCardName::FORMEREMPLOYER:     
            return "FORMEREMPLOYER";

        case MonsterCardName::HURRIEDASSISTANT:    
            return "HURRIEDASSISTANT";

        case MonsterCardName::THEINNOCENT:  
            return "THEINNOCENT";

        case MonsterCardName::EGYPTIANEXPERT:       
            return "EGYPTIANEXPERT";

        case MonsterCardName::THEICHTHYOLOGIST:    
            return "THEICHTHYOLOGIST";

        case MonsterCardName::HYPNOTICGAZE:
            return "HYPNOTICGAZE";

        case MonsterCardName::ONTHEMOVE:
            return "ONTHEMOVE";

        default:
            return "UNKNOWN";
    }
}