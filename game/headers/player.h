#pragma once
#include "../../headers/entity.h"

struct Player
{
    TextureComponent textureComponent = {};
    MoveComponent moveComponent = {};
    InputComponent inputComponent = {};

    Vector2 position = {};
};