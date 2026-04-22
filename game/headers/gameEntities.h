#pragma once
#include "../../headers/rendering.h"

enum GameTag
{
    NONE,
    PLAYER
};

enum BulletPattern
{
    STRAIGHT
};

struct BulletComponent
{
    MoveComponent moveComponent;
    TextureComponent textureComponent;
};

struct GunComponent
{
    BulletPattern pattern = BulletPattern::STRAIGHT;
    float fireRate = 1; // shots/sec
};

void PlayerUpdate(entt::registry& registry);
void CreateGameEntities(entt::registry& registry);