#ifndef SNAKE_H
#define SNAKE_H

#include "graphics.h"
#include <list>

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

// Describes one section of the snake in coordinates and visual type
struct Block
{   int type;
    int x, y;
};

class Snake
{
private:
    std::list<Block> body;

public:

    // Creates a snake at x, y coordinates with some number of segments
    // Draws the newly created segments on the screen
    Snake(int x, int y, int seg);

    // Adds a new section to the snake in the direction it's moving in and
    // Removes one section from the tail. If the last section is fat from
    // eating, it remains there to increase the length of the snake
    void move(int direction);

    // Converts the snake's head to an APPLE_BODY type to signal it has eaten an apple
    // Re-draws the graphic of the head on the console
    void eat();

    // Deletes all segments of the snake on the console
    ~Snake();
};

#endif