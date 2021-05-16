#include <string.h>
#include "board.h"
#include "graphics.h"

int obstacles[] = {
    0x00002020,  // EMPTY       ID: 0
    0x0000CDCD,  // HOR_WALL ══ ID: 1
    0x0000BA20,  // VER_WALL ║  ID: 2

    0x0000BBCD,  // UR_COR ═╗ ID: 3
    0x0000BCCD,  // LR_COR ═╝ ID: 4
    0x0000C920,  // UL_COR  ╔ ID: 5
    0x0000C820,  // LL_COR  ╚ ID: 6

    0x0000CACD,  // UP_INT ═╩ ID: 7
    0x0000CBCD,  // DN_INT ═╦ ID: 8
    0x0000B9CD,  // LF_INT ═╣ ID: 9
    0x0000CC20,  // RT_INT  ╠ ID: 10

    0x0000CECD   // CROSS ═╬  ID: 11
};

Board::Board(int x, int y) : xSize(x), ySize(y), board(new char[x*y])
{   memset(board, 0, x*y);
}


void Board::drawBoard()
{
    init();
    SetConsoleCursorPosition(outputHandle, COORD{0, 0});

    int tile;
    for(int i=0;i<ySize; i++)
        for(int j=0;j<xSize; j++)
        {   
            tile = get(j,i);
            if(tile != 0)
                draw(j, i, &obstacles[tile]);

        }
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