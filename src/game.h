#pragma once
#include <vector>
#include "grid.h"
#include "blocks.cpp"
using namespace std;

class Game
{
    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    void resetGame();
    bool isBlockOutside();
    void rotateBlock();
    void lockBlock();
    bool blockFits();
    void updateScore(int linesCleared, int movedDown);
    Sound clearSound;
    Sound rotationSound;

public:
    Game();
    ~Game();
    Block getRandomBlock();
    vector<Block> getBlocks();
    void gameDraw();
    void handleInput();
    void moveLeft();
    void moveRight();
    void moveDown();
    bool gameOver;
    int score;
    Grid grid;
    Music music;
};
