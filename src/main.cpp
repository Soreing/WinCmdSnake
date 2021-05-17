#include <iostream>
#include "graphics.h"
#include "game.h"

int main() 
{
    Game gm;

    gm.loadLevel("level.bin");
    gm.start();

    while(gm.isRunning())
    {
        gm.update();
    }
}