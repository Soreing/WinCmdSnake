#include <string.h>
#include "board.h"


Board::Board(int x, int y) : xSize(x), ySize(y), board(new char[x*y])
{   memset(board, 0, x*y);
}


char Board::get(int x, int y)
{   return board[x + y*xSize];
}


void Board::set(int x, int y, char val)
{   board[x + y*xSize] = val;
}


Board::~Board()
{   delete[] board;
}