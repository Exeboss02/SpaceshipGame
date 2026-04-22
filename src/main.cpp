#include <raylib.h>
#include <string>
#include <iostream>
#include <lua.hpp>

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
    lua_State* L = luaL_newstate();

    // Load standard Lua libraries
    luaL_openlibs(L);

    // Run a simple Lua script
    const char* luaScript = "print('Lua is working!')";
    int result = luaL_dostring(L, luaScript);

    // Check for errors
    if (result != LUA_OK) {
        std::cerr << "Error running Lua script: " << lua_tostring(L, -1) << std::endl;
        lua_close(L);
        return 1;
    }

    // Clean up
    lua_close(L);

    entt::registry registry;

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
            //DrawRectangle(200, 100, 400, 250, customColor);

            UpdateInputComponents(registry);

            PlayerUpdate(registry);

            UpdateMoveComponents(registry);
            DrawTextureComponents(registry);

        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    return 0;
}