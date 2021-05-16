#include "graphics.h"
#include "directions.h"
#include "snake.h"

int APPLE_BODY = 0x0000B2B2; // ▓▓
int SNAKE_BODY = 0x0000B0B0; // ░░


Snake::Snake(int x, int y, int seg)
{
    Block segment;

    for(int i=0; i<seg; i++)
    {   
        segment = Block{ SNAKE_BODY, x+i, y };

        body.push_back(segment);
        draw(segment.x, segment.y, &segment.type);
    }
}


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


void Snake::eat()
{
    body.front().type = APPLE_BODY;
    draw(body.front().x, body.front().y, &body.front().type);
}

 std::list<Block> Snake::getBody()
 {   return body;
 }

Block Snake::getHead()
{    return body.front();
}

Snake::~Snake()
{
    for(auto it = body.begin(); it!= body.end(); it++)
        erase(it->x, it->y);
}
