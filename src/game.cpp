#include <chrono>
#include <iostream>
#include <conio.h>
#include <time.h>
#include "graphics.h"
#include "game.h"

typedef std::chrono::steady_clock::time_point timeStamp;
#define TIME_NOW std::chrono::high_resolution_clock().now()
#define ELAPSED_NANOS(x, y) std::chrono::duration_cast<std::chrono::nanoseconds>(x - y).count();

int APPLE_IMAGE = 0x0000FE20; //  ■
int FULL_BAR    = 0x0000DBDB; // ██
int EMPTY_BAR   = 0x0000B0B0; // ░░

Game::Game() : board(NULL), snake(NULL), dir(LEFT)
{   init();
    srand((unsigned int)time(NULL));
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


void Game::loadLevel(const char* filename)
{
    if(board != NULL)
        delete board;

    if(snake != NULL)
        delete snake;

    board = new Board(filename);
    snake = new Snake(board->getXSize()/2, board->getYSize()/2, 5);
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

    score      = 0;
    level      = 1;
    oldTarget  = 0;
    curTarget  = 300;
    speedScale = 20;

    inputThread = CreateThread(NULL, NULL, inThread, (LPVOID)this, NULL, NULL);

    std::list<Block> segments = snake->getBody();
    for(auto it = segments.begin(); it != segments.end(); it++)
        board->set(it->x, it->y, -1);

    board->drawBoard();
    generateApple();
    displayScore();
    displayProgress();
}


void Game::update()
{
    timeStamp now = TIME_NOW;
    totalTime += ELAPSED_NANOS(now, lastUpdate);
    lastUpdate = now;

    Block head, remove = {-1, -1, 0};

    if(totalTime > nextTick)
    {   
        nextTick += gameSpeed;
        remove.x  = -1;
        remove.y  = -1;
        head = snake->getHead();

        switch(dir)
        {   case UP:    head.y -= 1; break;
            case DOWN:  head.y += 1; break;
            case LEFT:  head.x -= 1; break;
            case RIGHT: head.x += 1; break;
        }

        if(board->get(head.x, head.y) != 0)
        {   running = false;
            return;
        }


        snake->move(head.x, head.y, remove);
        board->set(head.x, head.y, -1);
        if(remove.x != -1)
            board->set(remove.x, remove.y, 0);

        if(head.x == apple.x && head.y == apple.y)
        {   snake->eat();
            generateApple();
            score += 100;

            if(curTarget <= score)
            {   oldTarget  = curTarget;
                curTarget += curTarget;
                level++;
                increaseSpeed();
            }

            displayScore();
            displayProgress();
        }
    }

}


void Game::generateApple()
{
    int x, y;

    do
    {   x = rand() % board->getXSize();
        y = rand() % board->getYSize();
    } while ( board->get(x, y) != 0);
    
    apple = Apple{x, y};
    draw(x, y, &APPLE_IMAGE, RED);
}


void Game::increaseSpeed()
{    gameSpeed -= gameSpeed*speedScale/100;
}


void Game::displayScore()
{
    gotoPosition(1, board->getYSize());
    setColor(WHITE);
    std::cout<< "Score: "<< score;
}


void Game::displayProgress()
{
    setColor(WHITE);
    gotoPosition(11, board->getYSize());
    std::cout<< "Progress: ";

    int i=0;
    int rate = (score-oldTarget)*10/(curTarget-oldTarget);

    for(; i<rate; i++)
        draw(16+i, board->getYSize(), &FULL_BAR, GREEN);
    for(; i<10; i++)
        draw(16+i, board->getYSize(), &EMPTY_BAR);

    setColor(WHITE);
    std::cout<< "  Level ["<<level<<"]";
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


DWORD WINAPI inThread(LPVOID lparam)
{
    Game* gameInstance = (Game*)lparam;
    int input;

    while(true)
    {
        input = _getch();
        if(input== 0 || input== 224)
        {
            input = _getch();
            switch(input)
            {   case 72: gameInstance->dir = UP; break;
                case 80: gameInstance->dir = DOWN; break;
                case 75: gameInstance->dir = LEFT; break;
                case 77: gameInstance->dir = RIGHT; break;
            }
        }
    }
}