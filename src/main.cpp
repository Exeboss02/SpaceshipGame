#include <raylib.h>
#include <string>
#include <iostream>

#include "../game/headers/gameEntities.h"

int main(void)
{
    // Initialize window
    const int screenWidth = 900;
    const int screenHeight = 550;
    InitWindow(screenWidth, screenHeight, "Spaceship Game");

    // Set target FPS
    SetTargetFPS(144);
    Color customColor = {255, 80, 30, 255};

    // Create a Lua state
    lua_State* L = LuaSetup();
    GameLuaSetup(L);
    luaL_dofile(L, "game/lua/start.lua");

    entt::registry& registry = GetRegistry();
    CreateGameEntities(registry);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        // TODO: Add your game logic here

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello, Raylib!", 190, 200, 20, BLACK);

            UpdateGameSystems(registry, L);

            UpdateInputComponents(registry);
            UpdateTimerComponents(registry);
            UpdateColliderComponents(registry);

            UpdateMoveComponents(registry);
            DrawBackground(registry);
            DrawTextureComponents(registry);

        EndDrawing();
    }

    // Cleanup
    lua_close(L);
    CloseWindow();
    return 0;
}