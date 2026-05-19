#pragma once
#include <type_traits>
#include <iostream>
#include <raylib.h>
#include <lua.hpp>

#include "../headers/resourceStorage.h"

struct TimerComponent
{
    float startTime = 1.0f;
    float currentTime = startTime;
    bool paused = false;
    std::string id = "";
};

struct TextureComponent
{
    Vector2 position = {};
    Vector2 size = {};
    TextureContainer* textureContainer = nullptr;
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
    bool shootButton = false;
    bool arrowUp = false;
};

struct BoxColliderComponent
{
    Rectangle rectangle = {};
    bool inCollision = false;
    entt::entity hitEntity = {};
};

std::string GetExecutablePath();


//Rendering and textures
void DrawTextureComponents(entt::registry& registry);
TextureContainer* GetTexture(std::string path);

void AddMoveComponent(entt::registry& registry, entt::entity& entity, Vector2 position, Vector2 velocity, float speedMultiplier);
bool AddTextureComponent(entt::registry& registry, entt::entity& entity, std::string texturePath, Vector2 size, Vector2 position);
void AddInputComponent(entt::registry& registry, entt::entity& entity);
void AddTimerComponent(entt::registry& registry, entt::entity& entity, float startTime);
void AddBoxColliderComponent(entt::registry& registry, entt::entity& entity, Vector2 position, Vector2 scale);

void UpdateInputComponents(entt::registry& registry);
void UpdateColliderComponents(entt::registry& registry);
void UpdateMoveComponents(entt::registry& registry);
void UpdateTimerComponents(entt::registry& registry);
void ResetTimerComponent(entt::registry &registry, entt::entity timerHoldingEntity);

lua_State* LuaSetup();
