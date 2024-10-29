#include <raylib.h>
#include "game.h"
#include <iostream>

double lastUpdateTime = 0;
bool eventTriggered(double interval);

int main()
{
    Font font = LoadFontEx("ARCADE_N.TTF", 64, 0, 0);
    // Color darkBlue = {44, 44, 127, 255};
    InitWindow(500, 620, "Tetris");
    SetTargetFPS(60);
    Game game;
    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        game.handleInput();
        if (eventTriggered(0.5))
        {
            game.moveDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {350, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 28, 2, WHITE);
        }
        char score[10];
        sprintf(score, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, score, 38, 2);
        DrawRectangle(320, 55, 170, 60, lightBlue);
        DrawTextEx(font, score, {320 + (150 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangle(320, 215, 170, 180, lightBlue);
        game.gameDraw();

        EndDrawing();
    }

    CloseWindow();
}

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}