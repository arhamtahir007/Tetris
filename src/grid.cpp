#include "grid.h"

bool Grid::isRowFull(int row)
{
    for (int i = 0; i < cols; i++)
    {
        if (grid[row][i] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::clearRow(int row)
{
    for (int i = 0; i < cols; i++)
    {
        grid[row][i] = 0;
    }
}

void Grid::moveRowDown(int row, int numOfRows)
{
    for (int i = 0; i < cols; i++)
    {
        grid[row + numOfRows][i] = grid[row][i];
        grid[row][i] = 0;
    }
}

Grid::Grid()
{
    rows = 20;
    cols = 10;
    cellSize = 30;
    initializeGrid();
    colors = getCellColors();
}

void Grid::initializeGrid()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void Grid::printGrid()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void Grid::drawGrid()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int colorIndex = grid[i][j];
            DrawRectangle(j * cellSize + 11, i * cellSize + 11, cellSize - 1, cellSize - 1, colors[colorIndex]);
        }
    }
}

bool Grid::isCellOutside(int row, int col)
{
    if (row >= 0 && row < rows && col >= 0 && col < cols)

    {
        return false;
    }

    return true;
}

bool Grid::isCellEmpty(int row, int col)
{
    if (grid[row][col] == 0)
    {
        return true;
    }
    return false;
}

int Grid::clearFullRow()
{
    int completed = 0;
    for (int i = rows; i >= 0; i--)
    {
        if (isRowFull(i))
        {
            clearRow(i);
            completed++;
        }
        else if (completed > 0)
        {
            moveRowDown(i, completed);
        }
    }
    return completed;
}
