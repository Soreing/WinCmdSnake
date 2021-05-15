#include <iostream>
#include "game.h"

int main() 
{
    init();
    
    Game mainGame(45, 20);

    while(mainGame.running)
    {   mainGame.update();
    }

    std::cin.get();
}