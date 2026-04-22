#pragma once
#include <raylib.h>

struct TextureComponent
{
    Vector2 position = {};
    Vector2 velocity = {};
    Texture2D texture = {};
};

struct MoveComponent
{
    Vector2 velocity = {};
};

struct InputComponent
{
    float yInput = {};
    float xInput = {};
};

void UpdateInputComponent(InputComponent* input);
