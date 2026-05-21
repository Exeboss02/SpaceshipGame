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

std::string GetExecutablePath();


//Rendering and textures
void DrawTextureComponents(entt::registry& registry);
TextureContainer* GetTexture(std::string path);

int lua_CreateEntity(lua_State* L);
int lua_AddMoveComponent(lua_State* L);
int lua_AddTextureComponent(lua_State* L);
int lua_AddInputComponent(lua_State* L);
int lua_AddTimerComponent(lua_State* L);
int lua_AddBoxColliderComponent(lua_State* L);
int lua_GetInputValues(lua_State* L);
int lua_GetDeltaTime(lua_State* L);

int lua_GetMoveComponent(lua_State* L);
int lua_GetTextureComponent(lua_State* L);
int lua_GetInputComponent(lua_State* L);
int lua_GetTimerComponent(lua_State* L);
int lua_GetBoxColliderComponent(lua_State* L);

int lua_SetMoveComponentVelocity(lua_State* L);
int lua_SetTextureComponent(lua_State* L);
int lua_SetInputComponent(lua_State* L);
int lua_SetTimerComponent(lua_State* L);
int lua_SetBoxColliderComponent(lua_State* L);

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
void DrawBackground(entt::registry& registry);

entt::registry& GetRegistry();
lua_State *LuaSetup();
