#ifndef BOARD_H
#define BOARD_H

#include <string.h>

class Board
{
public:
    int xSize;
    int ySize;
    char* board;

public:

    Board(int x, int y) : xSize(x), ySize(y), board(new char[x*y])
    {   memzero(board, x*y);
    }

    char get(int x, int y)
    {   return board[x*xSize + y];
    }
    void set(int x, int y, char val)
    {   board[x*xSize + y] = val;
    }

    ~Board()
    {   delete[] board;
    }

};

#endif