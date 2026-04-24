#pragma once
#include <type_traits>
#include <iostream>
#include <raylib.h>

#include "../headers/entities.h"
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

//Rendering and textures
void DrawTextureComponents(entt::registry& registry);
bool SetTexture(Texture2D* texture, std::string path);

void AddMoveComponent(entt::registry& registry, entt::entity& entity, Vector2 position, Vector2 velocity, float speedMultiplier);
bool AddTextureComponent(entt::registry& registry, entt::entity& entity, std::string texturePath, Vector2 size, Vector2 position);
void AddInputComponent(entt::registry& registry, entt::entity& entity);

void UpdateInputComponents(entt::registry& registry);
void UpdateMoveComponents(entt::registry& registry);
