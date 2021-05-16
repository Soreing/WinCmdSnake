#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <chrono>
#include "snake.h"
#include "board.h"
#include "directions.h"

typedef std::chrono::steady_clock::time_point timeStamp;

class Game
{
private:
    Snake* snake;           // Snake object in the game
    Board* board;           // Board object with obstacles in the game
    bool running;           // Running state of the game

    timeStamp lastUpdate;   // Last time stamp of when Update() was called
    long long totalTime;    // Total amount of nanoseconds that elapsed in the game

    Direction dir;          // Direction of the snake
    long long nextTick;     // Timestamp of the next logic tick
    long long gameSpeed;    // Time required before the next game tick

    HANDLE inputThread;     // Thread for user input

public:

    // Initializes the graphics in case it isn't
    Game();

    // Creates a Snake and a Board with width and height
    // If either objects already exist, they will be deleted
    void loadLevel(int xSize, int ySize);

    // Sets the game running, initializes the timer
    void start();

    // Handles game logic and updating the timer
    void update();

    bool isRunning();

    // Deallocated dynamically allocated Board and Snake
    ~Game();

    friend DWORD WINAPI inThread(LPVOID lparam);
};

#endif