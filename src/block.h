#pragma once
#include <map>
#include "position.h"
#include <vector>
#include "colors.h"
using namespace std;
class Block
{
    int cellSize;
    int rotationState;

public:
    int id;
    map<int, vector<Position>> cells;
    vector<Color> colors;
    int rowOffset;
    int colOffset;
    Block();
    void drawBlock(int offsetX, int offsetY);
    void blockMove(int row, int col);
    void blockRotate();
    void blockUnRotate();
    vector<Position> getCellPosition();
};