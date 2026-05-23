#include "../headers/luaFunctions.h"

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
    lua_pushcfunction(L, lua_GetDeltaTime);
    lua_setglobal(L, "GetDeltaTime");
    lua_pushcfunction(L, lua_SetMoveComponentVelocity);
    lua_setglobal(L, "SetMoveComponentVelocity");
    lua_pushcfunction(L, lua_AddGameSystemComponent);
    lua_setglobal(L, "AddGameSystemComponent");
    lua_pushcfunction(L, lua_AddCustomComponent);
    lua_setglobal(L, "AddCustomComponent");

    return L;
}

int lua_ReferenceAndPushBehaviour(lua_State *L)
{
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    std::string scriptPath = static_cast<std::string>(lua_tostring(L, 2));

    ReferenceAndPushBehaviour(L, static_cast<int>(entity), scriptPath);

    return 0;
}

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

int lua_AddGameSystemComponent(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    std::string scriptPath = static_cast<std::string>(lua_tostring(L, 2));
    int tableRef = ReferenceAndPushBehaviour(L, static_cast<int>(entity), scriptPath);

    AddGameSystemComponent(registry, entity, scriptPath, tableRef);

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

int lua_GetDeltaTime(lua_State *L)
{
    lua_pushnumber(L, GetFrameTime());
    return 1;
}

int lua_SetMoveComponentVelocity(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    float velX = static_cast<float>(lua_tonumber(L, 2));
    float velY = static_cast<float>(lua_tonumber(L, 3));

    auto* moveComponent = registry.try_get<MoveComponent>(entity);
    if(moveComponent)
    {
        moveComponent->velocity = Vector2{velX, velY};
    }
    
    //speed scaler will only be in lua from now on

    return 0;
}