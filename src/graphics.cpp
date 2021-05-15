#include "graphics.h"
#include <iostream>

// Sets the value of the global OutputHandle
// And hides the console cursor to create a black canvas
void init()
{   outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO params{1, FALSE};
    SetConsoleCursorInfo(outputHandle, &params);
}

// Draws a 1-2 character string on the console at coordinates x and y
void draw(int x, int y, int* arr)
{   SetConsoleCursorPosition(outputHandle, COORD{(short)(x*2), (short)y});
    std::cout<< (char*)arr;
}

// Erases 2 characters at coordinates x and y on the console
void erase(short x, short y)
{   SetConsoleCursorPosition(outputHandle, COORD{(short)(x*2), (short)y});
    std::cout<< "  ";
}