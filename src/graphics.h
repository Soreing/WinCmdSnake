#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <windows.h>

#define WHITE  15
#define GREEN  2
#define RED    4
#define PURPLE 5
#define YELLOW 6
#define BLUE   9

static HANDLE outputHandle;

// Sets the value of the global OutputHandle
// And hides the console cursor to create a black canvas
void init();

// Draws a 1-2 character string on the console at coordinates x and y
// Takes a color for the drawn text, by default white on black background
void draw(int x, int y, int* arr, int color = WHITE);

// Erases 2 characters at coordinates x and y on the console
void erase(short x, short y);

// Puts the cursor in the console to a specific square coordinate
void gotoPosition(int x, int y);

// Sets the color of the text
void setColor(int color);

#endif