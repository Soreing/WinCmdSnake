#ifndef BOARD_H
#define BOARD_H

class Board
{
private:
    int xSize;
    int ySize;
    char* board;

public:

    // Creates a Board of x width and y height and allocates the array on the heap
    Board(int x, int y);

    // Creates a Board from a file and allocates the array on the heap
    //Board(const char* filename)

    // Gets the element on the board at coordinates x and y
    char get(int x, int y);

    // Sets the element on the board at coordinates x and y
    void set(int x, int y, char val);

    // Deallocates memory for the board
    ~Board();

};

#endif