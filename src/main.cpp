#include <iostream>
#include "graphics.h"
#include "game.h"

int main() 
{
    Game gm;

    gm.loadLevel(45, 20);
    gm.start();

    while(gm.isRunning())
    {
        gm.update();
    }
}