#include <iostream>
#include "mayor.hpp"
#include "perk.hpp"

Mayor::Mayor()
    : Hero( HeroName::MAYOR , Location::THEATRE)
{
    setActionsLeft(5);
}