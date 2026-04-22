#pragma once
#include <raylib.h>
#include "../headers/entt.hpp"

struct TextureComponent
{
    Vector2 position = {};
    Texture2D texture = {};
};

struct MoveComponent
{
    Vector2 position = {};
    Vector2 velocity = {};
    float speedMultiplier = 1.0f;
};

struct InputComponent
{
    float yInput = {};
    float xInput = {};
};

void UpdateInputComponents(entt::registry& registry);
void UpdateMoveComponents(entt::registry& registry);
