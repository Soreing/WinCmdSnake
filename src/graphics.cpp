#include "graphics.h"
#include <iostream>

void init()
{   outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO params{1, FALSE};
    SetConsoleCursorInfo(outputHandle, &params);
}

void draw(int x, int y, int* arr, int color)
{   setColor(color);
    SetConsoleCursorPosition(outputHandle, COORD{(short)(x*2), (short)y});
    std::cout<< (char*)arr;
}

void erase(short x, short y)
{   setColor(WHITE);
    SetConsoleCursorPosition(outputHandle, COORD{(short)(x*2), (short)y});
    std::cout<< "  ";
}

void gotoPosition(int x, int y)
{   SetConsoleCursorPosition(outputHandle, COORD{(short)(x*2), (short)y});
}

void setColor(int color)
{   SetConsoleTextAttribute(outputHandle, color);
}