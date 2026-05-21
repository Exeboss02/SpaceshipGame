#include "../headers/entities.h"
#include "entities.h"

//fix this for cross-platform later. windows.h sucks by the way
std::string GetExecutablePath()
{
    //return std::filesystem::canonical("/proc/self/exe").parent_path();
    // char* path = {};
    // GetModuleFileNameA(NULL, path, 256);
    // std::string outPath = path;

    // return outPath;
    return std::string{};
}

void DrawTextureComponents(entt::registry &registry)
{
    auto view = registry.view<TextureComponent>();
    for (auto [entity, textureComponent] : view.each())
    {
        //this is so that source texture can have different sizes depending on which entity
        textureComponent.textureContainer->texture.width = textureComponent.size.x;
        textureComponent.textureContainer->texture.height = textureComponent.size.y;

        DrawTextureV(textureComponent.textureContainer->texture, {textureComponent.position}, WHITE);
    }
}

TextureContainer* GetTexture(std::string path)
{
    static TextureStorage storage;

    for (int i = 0; i < storage.textures.size(); i++)
    {
        if(storage.textures[i]->path == path)
        {
            return storage.textures[i];
        }
    }

    //not what I wanted, but has to work in the meantime. REMEMBER to delete
    TextureContainer* texture = new TextureContainer();
    texture->path = path;
    texture->texture = LoadTexture(path.c_str());
    storage.textures.push_back(texture);

    return texture;
}

//----------------------STATIC-LUA-FUNCTIONS---------------------------------------------------------

int lua_CreateEntity(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = registry.create();

    lua_pushinteger(L, static_cast<int>(entity));

    return 1;
}

int lua_AddMoveComponent(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    float posX = static_cast<float>(lua_tonumber(L, 2));
    float posY = static_cast<float>(lua_tonumber(L, 3));
    float velX = static_cast<float>(lua_tonumber(L, 4));
    float velY = static_cast<float>(lua_tonumber(L, 5));
    float speed = static_cast<float>(lua_tonumber(L, 6));

    AddMoveComponent(registry, entity, Vector2{posX, posY}, Vector2{velX, velY}, speed);

    return 0;
}

int lua_AddTextureComponent(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    std::string texturePath = static_cast<std::string>(lua_tostring(L, 2));
    float posX = static_cast<float>(lua_tonumber(L, 3));
    float posY = static_cast<float>(lua_tonumber(L, 4));
    float sizeX = static_cast<float>(lua_tonumber(L, 5));
    float sizeY = static_cast<float>(lua_tonumber(L, 6));

    AddTextureComponent(registry, entity, texturePath, Vector2{sizeX, sizeY}, Vector2{posX, posY});
    return 0;
}

int lua_AddInputComponent(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));

    AddInputComponent(registry, entity);
    return 0;
}

int lua_AddTimerComponent(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    float startTime = static_cast<float>(lua_tonumber(L, 2));

    AddTimerComponent(registry, entity, startTime);
    return 0;
}

int lua_AddBoxColliderComponent(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    float posX = static_cast<float>(lua_tonumber(L, 2));
    float posY = static_cast<float>(lua_tonumber(L, 3));
    float sizeX = static_cast<float>(lua_tonumber(L, 4));
    float sizeY = static_cast<float>(lua_tonumber(L, 5));

    AddBoxColliderComponent(registry, entity, Vector2{posX, posY}, Vector2{sizeX, sizeY});
    return 0;
}

int lua_GetInputValues(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    auto* input = registry.try_get<InputComponent>(entity);

    if(input)
    {
        lua_pushboolean(L, input->arrowUp);
        lua_pushboolean(L, input->shootButton);
        lua_pushnumber(L, input->xInput);
        lua_pushnumber(L, input->yInput);
    }
    else
    {
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
    }

    return 4;
}
//-------------------------------------C++-Add-Components---------------------------------------------------------------

void AddInputComponent(entt::registry& registry, entt::entity& entity)
{
    registry.emplace<InputComponent>(entity);
}

void AddTimerComponent(entt::registry &registry, entt::entity &entity, float startTime)
{
    registry.emplace<TimerComponent>(entity, startTime);
}

void AddBoxColliderComponent(entt::registry &registry, entt::entity &entity, Vector2 position, Vector2 scale)
{
    Rectangle rectangle = {position.x, position.y, scale.x, scale.y};
    registry.emplace<BoxColliderComponent>(entity, rectangle, false);
}

void AddMoveComponent(entt::registry &registry, entt::entity &entity, Vector2 position, Vector2 velocity, float speedMultiplier)
{
    registry.emplace<MoveComponent>(entity, position, velocity, speedMultiplier);
}

bool AddTextureComponent(entt::registry &registry, entt::entity &entity, std::string texturePath, Vector2 size, Vector2 position)
{
    TextureContainer* texture = GetTexture(texturePath);
    
    if(texture)
    {
        registry.emplace<TextureComponent>(entity, position, size, texture);
        return true;
    }

    return false;
}

//----------------------UPDATES----------------------------------------------------------------------------------------------------

void UpdateInputComponents(entt::registry &registry)
{
    auto view = registry.view<InputComponent>();
    for (auto [entity, input] : view.each())
    {
        input.xInput = 0;
        input.yInput = 0;

        if(IsKeyDown(KEY_A)) input.xInput--;
        if(IsKeyDown(KEY_D)) input.xInput++;
        if(IsKeyDown(KEY_W)) input.yInput--;
        if(IsKeyDown(KEY_S)) input.yInput++;
        if(IsKeyDown(KEY_RIGHT)) input.shootButton = true;
        else input.shootButton = false;
        if(IsKeyDown(KEY_UP)) input.arrowUp = true;
        else input.arrowUp = false;
    }
}

void UpdateColliderComponents(entt::registry &registry)
{
    //max nr of colliders is 256, this is not very clean but I have to put colliders in
    //a contigous array somehow, and I don't have a class to store the array in because of ecs.
    static BoxColliderComponent* colliders[256] = {};
    static entt::entity entities[256] = {};

    auto view = registry.view<BoxColliderComponent>();
    int index = 0;
    for (auto [entity, collider] : view.each())
    {
        entities[index] = entity;
        colliders[index] = &collider;
        colliders[index]->inCollision = false;
        index++;
    }

    for (int i = 0; i < view.size(); i++)
    {
        for(int j = i + 1; j < view.size(); j++)
        {
            if(CheckCollisionRecs(colliders[i]->rectangle, colliders[j]->rectangle))
            {
                colliders[i]->inCollision = true;
                colliders[i]->hitEntity = entities[j];

                colliders[j]->inCollision = true;
                colliders[j]->hitEntity = entities[i];
            }
        }
    }
    
}

void UpdateMoveComponents(entt::registry &registry)
{
    auto view = registry.view<MoveComponent>();
    for (auto [entity, moveComponent] : view.each())
    {
        moveComponent.position.x = moveComponent.position.x + moveComponent.velocity.x;
        moveComponent.position.y = moveComponent.position.y + moveComponent.velocity.y;

        if (auto* textureComponent = registry.try_get<TextureComponent>(entity))
        {
            textureComponent->position = moveComponent.position;
        }

        if (auto* collider = registry.try_get<BoxColliderComponent>(entity))
        {
            collider->rectangle.x = moveComponent.position.x;
            collider->rectangle.y = moveComponent.position.y;
        }
    }
}

void UpdateTimerComponents(entt::registry &registry)
{
    auto view = registry.view<TimerComponent>();
    for (auto [entity, timer] : view.each())
    {
        if(!timer.paused && timer.currentTime > 0) timer.currentTime -= GetFrameTime();
    }
}

void ResetTimerComponent(entt::registry &registry, entt::entity timerHoldingEntity)
{
    auto* timer = registry.try_get<TimerComponent>(timerHoldingEntity);
    if(timer) timer->currentTime = timer->startTime;
}

entt::registry &GetRegistry()
{
    static entt::registry registry;
    return registry;
}

lua_State *LuaSetup()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, lua_CreateEntity);
    lua_setglobal(L, "CreateEntity");
    lua_pushcfunction(L, lua_AddMoveComponent);
    lua_setglobal(L, "AddMoveComponent");
    lua_pushcfunction(L, lua_AddTextureComponent);
    lua_setglobal(L, "AddTextureComponent");
    lua_pushcfunction(L, lua_AddInputComponent);
    lua_setglobal(L, "AddInputComponent");
    lua_pushcfunction(L, lua_AddTimerComponent);
    lua_setglobal(L, "AddTimerComponent");
    lua_pushcfunction(L, lua_AddBoxColliderComponent);
    lua_setglobal(L, "AddBoxColliderComponent");

    lua_pushcfunction(L, lua_GetInputValues);
    lua_setglobal(L, "GetInputValues");

    // std::string luaPath = "game/lua/test.lua";
    // int result = luaL_dofile(L, luaPath.c_str());
    // // Check for errors
    // if (result != LUA_OK) {
    //     std::cerr << "Error running Lua script: " << lua_tostring(L, -1) << std::endl;
    //     return L;
    // }

    // std::cout << "LUA RESULTAT: " << lua_gettop(L) << std::endl;
    // lua_pop(L, 0);

    return L;
}
