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

struct GunComponent
{
    float shootCoolDown = 0.5f;
    float spreadFactor = 0.0f;
};

struct HealthComponent
{
    float hp = 10.0f;
};

struct DamageComponent
{
    float damage = 1.0f;
};

void DrawBackground(entt::registry& registry);

template<typename T, typename... Args>
void AddCustomComponent(entt::registry& registry, entt::entity entity, Args&&... args);