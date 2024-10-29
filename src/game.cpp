#include "game.h"
#include <random>
Game::Game()
{
    grid = Grid();
    blocks = getBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/MainSong.mp3");
    PlayMusicStream(music);
    rotationSound = LoadSound("Sounds/rotationTrim.mp3");
    clearSound = LoadSound("Sounds/rowClear.mp3");
}

Game::~Game()
{
    // Clean up audio device
    UnloadSound(rotationSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::getRandomBlock()
{
    if (blocks.empty())
    {
        blocks = getBlocks();
    }

    int randomNum = rand() % blocks.size();
    Block block = blocks[randomNum];
    blocks.erase(blocks.begin() + randomNum);
    return block;
}

vector<Block> Game::getBlocks()
{
    return {IBlock(), LBlock(), JBlock(), OBlock(), SBlock(), ZBlock(), TBlock()};
}

void Game::gameDraw()
{
    grid.drawGrid();
    currentBlock.drawBlock(11, 11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.drawBlock(255, 290);
        break;
    case 4:
        nextBlock.drawBlock(255, 280);
        break;

    default:
        nextBlock.drawBlock(270, 270);
        break;
    }
}

void Game::handleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed == KEY_ENTER)
    {
        gameOver = false;
        resetGame();
    }

    switch (keyPressed)
    {
    case KEY_LEFT:
    {
        moveLeft();
        break;
    }
    case KEY_RIGHT:
    {
        moveRight();
        break;
    }
    case KEY_UP:
    {
        rotateBlock();
        break;
    }
    case KEY_DOWN:
    {
        moveDown();
        updateScore(0, 1);
        break;
    }

    default:
        break;
    }
}

void Game::moveLeft()
{
    if (!gameOver)
    {
        currentBlock.blockMove(0, -1);
        if (isBlockOutside() || !blockFits())
        {
            currentBlock.blockMove(0, 1);
        }
    }
}

void Game::moveRight()
{
    if (!gameOver)
    {
        currentBlock.blockMove(0, 1);
        if (isBlockOutside() || !blockFits())
        {
            currentBlock.blockMove(0, -1);
        }
    }
}

void Game::moveDown()
{
    if (!gameOver)
    {
        currentBlock.blockMove(1, 0);
        if (isBlockOutside() || !blockFits())
        {
            currentBlock.blockMove(-1, 0);
            lockBlock();
        }
    }
}

bool Game::isBlockOutside()
{
    vector<Position> tiles = currentBlock.getCellPosition();
    for (Position item : tiles)
    {
        if (grid.isCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::rotateBlock()
{
    if (!gameOver)
    {
        currentBlock.blockRotate();
        if (isBlockOutside() || !blockFits())
        {
            currentBlock.blockUnRotate();
        }
        else
        {
            PlaySound(rotationSound);
        }
    }
}

void Game::lockBlock()
{
    vector<Position> tiles = currentBlock.getCellPosition();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (!blockFits())
    {
        gameOver = true;
    }

    nextBlock = getRandomBlock();
    int rowsCleared = grid.clearFullRow();
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        updateScore(rowsCleared, 0);
    }
}

bool Game::blockFits()
{
    vector<Position> tiles = currentBlock.getCellPosition();
    for (Position item : tiles)
    {
        if (!grid.isCellEmpty(item.row, item.column))
        {
            return false;
        }
    }
    return true;
}

void Game::updateScore(int linesCleared, int movedDown)
{
    if (gameOver)
    {
        return;
    }

    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }
    score += movedDown * 10;
}

void Game::resetGame()
{
    grid.initializeGrid();
    blocks = getBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    score = 0;
}
