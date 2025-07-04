#include <iostream>
#include "archaeologist.hpp"
#include "perk.hpp"

Archaeologist::Archaeologist()
    : Hero( HeroName::ARCHAEOLOGIST , Location::DOCKS)
{
    setActionsLeft(4); 
}