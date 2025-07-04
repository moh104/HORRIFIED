#include "perk.hpp"

Perk::Perk(Name n, int num) : name(n), number_of_perk(num)
{
}

Name Perk::getName()const{
    return name;
}

bool Perk::IsActive() const{
    return Active;
}

void Perk::Activation(){
    Active = true;
}

std::string Perk::NameToString(Name n) const{
    switch(n)
    {
        case Name::Break_of_Dawn:      
            return "Break of Down";

        case Name::Hurry:       
            return "Hurry";

        case Name::Late_into_the_Night:        
            return "Late into the Night";

        case Name::Overstock:    
            return "Overstock";

        case Name::Repel:     
            return "Repel";

        case Name::Visit_from_the_Detective:    
            return "Visit from Detective";
        default:
            return " ";
    }
}