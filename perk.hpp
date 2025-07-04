#ifndef PERK_HPP
#define PERK_HPP

#include <iostream>

enum class Name{
    Visit_from_the_Detective,
    Break_of_Dawn,
    Overstock,
    Late_into_the_Night,
    Repel,
    Hurry
};

class Perk
{
    private:
        Name name;
        int number_of_perk;
        bool Active = false;

    public:
        Perk(Name n , int num);
        
        std::string NameToString(Name n) const;
        Name getName() const;
        bool IsActive() const;
        void Activation();
};

#endif