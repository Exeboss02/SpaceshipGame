#pragma once
#include "../../headers/entities.h"

struct Player
{
    TextureComponent textureComponent = {};
    MoveComponent moveComponent = {};
    InputComponent inputComponent = {};

    Vector2 position = {};
    float speed;
};

struct PlayerEntity
{
    //ha noll-komponent i början för att kunna göra if-check ifall den har en kompnonent eller inte
    int id;
    int textureIndex;
    int moveIndex;
    int inputIndex;
};

void MoveEntity(Player* player); //this is EXTREMELY temporary