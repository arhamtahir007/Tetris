#include "block.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    rowOffset = 0;
    colOffset = 0;
    colors = getCellColors();
}

void Block::drawBlock(int offsetX, int offsetY)
{
    vector<Position> tiles = getCellPosition();
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::blockMove(int row, int col)
{
    rowOffset += row;
    colOffset += col;
}

void Block::blockRotate()
{
    rotationState += 1;
    if (rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}

void Block::blockUnRotate()
{
    rotationState -= 1;
    if (rotationState == -1)
    {
        rotationState = 3;
    }
}

vector<Position> Block::getCellPosition()
{
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position newPosi = Position(item.row + rowOffset, item.column + colOffset);
        movedTiles.push_back(newPosi);
    }
    return movedTiles;
}