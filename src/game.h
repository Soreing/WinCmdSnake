#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <chrono>
#include "snake.h"
#include "board.h"
#include "directions.h"

typedef std::chrono::steady_clock::time_point timeStamp;

struct Apple
{   int x, y;
};

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

    Apple apple;            // Current apple on the board
    int   score;            // Current Score
    int   level;            // Current Speed difficulty level
    int   curTarget;        // Current Target Score for difficulty increase
    int   oldTarget;        // Old Target Score for difficulty increase
    int   speedScale;       // Scale of how faster the game gets

    HANDLE inputThread;     // Thread for user input

public:

    // Initializes the graphics in case it isn't
    Game();

    // Creates a Snake and a Board with width and height
    // If either objects already exist, they will be deleted
    void loadLevel(int xSize, int ySize);

    // Creates a Snake and a Board by reading level data from a file
    // If either objects already exist, they will be deleted
    void loadLevel(const char* filename);

    // Sets the game running, initializes the timer and draws initial graphics
    void start();

    // Handles game logic and updating the timer
    void update();

    // Generates a randomply placed apple and draws it on the board
    void generateApple();

    // Increases the speed of the snake
    void increaseSpeed();

    // Displays the score at the bottom of the board
    void displayScore();

    // Displays the progress to the next level at the bottom of the board
    void displayProgress();

    bool isRunning();

    // Deallocated dynamically allocated Board and Snake
    ~Game();

    friend DWORD WINAPI inThread(LPVOID lparam);
};

#endif