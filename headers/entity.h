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
    int velocity = {};
};

struct InputComponent
{
    float yInput = {};
    float xInput = {};
};
