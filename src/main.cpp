#include <raylib.h>
#include <string>
#include <iostream>

#include "../headers/entt.hpp"
#include "../headers/rendering.h"
#include "../game/headers/player.h"

int main(void)
{
    // Initialize window
    const int screenWidth = 900;
    const int screenHeight = 550;
    InitWindow(screenWidth, screenHeight, "Spaceship Game");

    // Set target FPS
    SetTargetFPS(144);
    Color customColor = {255, 80, 30, 255};

    Player player;
    player.textureComponent.texture.width = 150;
    player.textureComponent.texture.height = 80;
    player.position = Vector2(100, 80);
    SetTexture(&player.textureComponent.texture, "game/assets/textures/HumanoidTpose.png");

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        // TODO: Add your game logic here

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello, Raylib!", 190, 200, 20, BLACK);
            //DrawRectangle(200, 100, 400, 250, customColor);

            Draw(player.textureComponent);

        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    return 0;
}