#include <raylib.h>
#include "../headers/entt.hpp"

int main(void)
{
    // Initialize window
    const int screenWidth = 900;
    const int screenHeight = 550;
    InitWindow(screenWidth, screenHeight, "Spaceship Game");

    // Set target FPS
    SetTargetFPS(144);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        // TODO: Add your game logic here

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello, Raylib!", 190, 200, 20, BLACK);
        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    return 0;
}