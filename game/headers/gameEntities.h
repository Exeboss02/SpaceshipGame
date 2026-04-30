#pragma once
#include "../../headers/entities.h"

enum GameTag
{
    NONE,
    PLAYER,
    ENEMY,
    GUN,
    BULLET
};

enum EnemyTag
{
    DRONE
};

enum BulletType
{
    STANDARD
};

enum BulletPattern
{
    STRAIGHT
};

struct GunComponent
{
    float shootCoolDown = 0.5f;
    float spreadFactor = 0.0f;
};

struct BulletEntity
{
    float damage = 1.0f;
};

template<typename T, typename... Args>
void AddCustomComponent(entt::registry& registry, entt::entity entity, Args&&... args);

entt::entity CreateEnemyEntity(entt::registry& registry, EnemyTag tag);
entt::entity CreateBulletEntity(entt::registry& registry, BulletType bulletType, Vector2 position);

void PlayerUpdate(entt::registry& registry);
void EnemyUpdate(entt::registry& registry);
void BulletUpdate(entt::registry& registry);
void CreateGameEntities(entt::registry& registry);