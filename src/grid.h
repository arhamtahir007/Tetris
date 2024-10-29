#pragma once
#include <iostream>
#include <vector>
#include <raylib.h>
#include "colors.h"
using namespace std;

class Grid
{
    int rows;
    int cols;
    int cellSize;
    vector<Color> colors;
    bool isRowFull(int row);
    void clearRow(int row);
    void moveRowDown(int row, int numOfRows);
public:
    int grid[20][10];
    Grid();
    void initializeGrid();
    void printGrid();
    void drawGrid();
    bool isCellOutside(int row, int col);
    bool isCellEmpty(int row, int col);
    int clearFullRow();
};