#pragma once
#include <type_traits>
#include <iostream>
#include <raylib.h>
#include <lua.hpp>

#include "../headers/resourceStorage.h"

enum GameTag
{
    NONE,
    PLAYER,
    ENEMY,
    BULLET
};

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
    bool shift = false;
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

struct ButtonComponent
{
    bool wasPressed = false;
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
void AddButtonComponent(entt::registry& registry, entt::entity& entity);

int ReferenceAndPushBehaviour(lua_State* L, int entity, std::string scriptPath);
void UpdateGameSystems(entt::registry& registry, lua_State* L);
void UpdateInputComponents(entt::registry& registry);
void UpdateColliderComponents(entt::registry& registry, lua_State* L);
void UpdateMoveComponents(entt::registry& registry);
void UpdateTimerComponents(entt::registry& registry);
void UpdateButtonComponents(entt::registry& registry);
void ResetTimerComponent(entt::registry &registry, entt::entity timerHoldingEntity);

entt::registry& GetRegistry();
void OnCollisions(entt::registry& registry, lua_State* L);

void GetGameTag(lua_State *L, std::string tag);
int lua_GetGameTag(lua_State* L); //has to be here because of collisions
