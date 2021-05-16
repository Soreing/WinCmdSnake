#include <chrono>
#include <iostream>
#include "graphics.h"
#include "game.h"

typedef std::chrono::steady_clock::time_point timeStamp;
#define TIME_NOW std::chrono::high_resolution_clock().now()
#define ELAPSED_NANOS(x, y) std::chrono::duration_cast<std::chrono::nanoseconds>(x - y).count();


Game::Game() : board(NULL), snake(NULL), dir(LEFT)
{   init();
} 

void Game::loadLevel(int xSize, int ySize)
{
    if(board != NULL)
        delete board;

    if(snake != NULL)
        delete snake;

    board = new Board(xSize, ySize);
    snake = new Snake(xSize/2, ySize/2, 5);

    for(int i=0; i<xSize; i++)
    {   board->set(i, 0, 1);
        board->set(i, ySize-1, 1);
    }

    for(int i=0; i<ySize; i++)
    {   board->set(0, i, 2);
        board->set(xSize-1, i, 2);
    }

    board->set(0,       0,       5);
    board->set(xSize-1, 0,       3);
    board->set(0,       ySize-1, 6);
    board->set(xSize-1, ySize-1, 4);
}

void Game::start()
{   
    if(board == NULL || snake == NULL)
        return;

    running = true;
    lastUpdate = TIME_NOW;
    totalTime = 0;
    gameSpeed = 200000000;
    nextTick  = 200000000;

    std::list<Block> segments = snake->getBody();
    for(auto it = segments.begin(); it != segments.end(); it++)
        board->set(it->x, it->y, -1);

    board->drawBoard();
}

void Game::update()
{
    timeStamp now = TIME_NOW;
    totalTime += ELAPSED_NANOS(now, lastUpdate);
    lastUpdate = now;

    if(totalTime > nextTick)
    {   snake->move(dir);
        nextTick += gameSpeed;
    }

}

bool Game::isRunning()
{   return running;
}

Game::~Game()
{   
    if(board != NULL)
        delete board;

    if(snake != NULL)
        delete snake;
} 