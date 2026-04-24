#pragma once
#include "../../headers/entities.h"

enum GameTag
{
    NONE,
    PLAYER,
    ENEMY
};

enum EnemyTag
{
    DRONE
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

template<typename T, typename... Args>
void AddCustomComponent(entt::registry& registry, entt::entity entity, Args&&... args);

entt::entity CreateEnemyEntity(entt::registry& registry, EnemyTag tag);

void PlayerUpdate(entt::registry& registry);
void EnemyUpdate(entt::registry& registry);
void CreateGameEntities(entt::registry& registry);