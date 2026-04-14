#pragma once
#include "../../headers/entity.h"

struct Player
{
    TextureComponent textureComponent = {};
    MoveComponent moveComponent = {};
    InputComponent inputComponent = {};

    Vector2 position = {};
    float speed;
};

void MoveEntity(Player* player); //this is EXTREMELY temporary