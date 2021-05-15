#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <windows.h>

static HANDLE outputHandle;

// Sets the value of the global OutputHandle
// And hides the console cursor to create a black canvas
void init();

// Draws a 1-2 character string on the console at coordinates x and y
void draw(int x, int y, int* arr);

// Erases 2 characters at coordinates x and y on the console
void erase(short x, short y);

#endif