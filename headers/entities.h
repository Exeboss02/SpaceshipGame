#pragma once
#include <type_traits>
#include <iostream>
#include <raylib.h>
#include <lua.hpp>

#include "../headers/resourceStorage.h"

struct BackgroundComponent //is a game entity but has to be here because of template jank
{
    float scrollSpeed = 1.0f;
};

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
    float speedMultiplier = -10.0f;
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

struct GameSystemComponent
{
    std::string scriptPath = {};
    int luaTableReference;
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
void AddGameSystemComponent(entt::registry& registry, entt::entity& entity, std::string scriptPath, int luaReference);

int ReferenceAndPushBehaviour(lua_State* L, int entity, std::string scriptPath);
void UpdateGameSystems(entt::registry& registry, lua_State* L);
void UpdateInputComponents(entt::registry& registry);
void UpdateColliderComponents(entt::registry& registry);
void UpdateMoveComponents(entt::registry& registry);
void UpdateTimerComponents(entt::registry& registry);
void ResetTimerComponent(entt::registry &registry, entt::entity timerHoldingEntity);

entt::registry& GetRegistry();
