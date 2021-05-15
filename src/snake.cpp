#include "graphics.h"
#include "snake.h"

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

int APPLE_BODY = 0x0000B2B2; // ▓▓
int SNAKE_BODY = 0x0000B0B0; // ░░

// Creates a snake at x, y coordinates with some number of segments
// Draws the newly created segments on the screen
Snake::Snake(int x, int y, int seg)
{
    Block segment;

    for(int i=0; i<seg; i++)
    {   
        segment = Block{ SNAKE_BODY, x-i, y };

        body.push_back(segment);
        draw(segment.x, segment.y, &segment.type);
    }
}

// Adds a new section to the snake in the direction it's moving in and
// Removes one section from the tail. If the last section is fat from
// eating, it remains there to increase the length of the snake
void Snake::move(int direction)
{
    Block newSection = body.front();

    switch(direction)
    {   case UP:    newSection.y -= 1; break;
        case DOWN:  newSection.y += 1; break;
        case LEFT:  newSection.x -= 1; break;
        case RIGHT: newSection.x += 1; break;
    }

    body.push_front(newSection);
    draw(newSection.x, newSection.y, &newSection.type);

    Block tail = body.back();

    if(tail.type == SNAKE_BODY)
    {   erase(tail.x, tail.y);
        body.pop_back();
    }
    else
    {   body.back().type = SNAKE_BODY;
        draw(body.back().x, body.back().y, &body.back().type);
    }
}

// Converts the snake's head to an APPLE_BODY type to signal it has eaten an apple
// Re-draws the graphic of the head on the console
void Snake::eat()
{
    body.front().type = APPLE_BODY;
    draw(body.front().x, body.front().y, &body.front().type);
}

// Deletes all segments of the snake on the console
Snake::~Snake()
{
    for(auto it = body.begin(); it!= body.end(); it++)
        erase(it->x, it->y);
}
