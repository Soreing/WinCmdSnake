#ifndef SNAKE_H
#define SNAKE_H

#include <list>

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

    // Adds a new section to the snake in the coordinates x and y
    // Removes one section from the tail. If the last section is fat from
    // eating, it remains there to increase the length of the snake
    void move(int x, int y, Block &removed);

    // Converts the snake's head to an APPLE_BODY type to signal it has eaten an apple
    // Re-draws the graphic of the head on the console
    void eat();

    // Returns all the body segments of the snake
    std::list<Block> getBody();

    // Returns the head segment of the snake
    Block Snake::getHead();

    // Deletes all segments of the snake on the console
    ~Snake();
};

#endif