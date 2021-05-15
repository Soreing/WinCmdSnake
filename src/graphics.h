#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <windows.h>

static HANDLE outputHandle;

void init();
void draw (short x, short y, const int* arr);
void erase(short x, short y);

#endif