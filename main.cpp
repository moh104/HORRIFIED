#include <iostream>
#include "game.hpp"

int main(){

    Game game;

    try
    {
        game.run();
    }
    catch(...)
    {
        std::cerr << "Error!!!" << '\n';
    }
    
    

    return 0;
}
