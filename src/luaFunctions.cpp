#include "../headers/luaFunctions.h"
#include "luaFunctions.h"

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
    lua_pushcfunction(L, lua_AddGameSystemComponent);
    lua_setglobal(L, "AddGameSystemComponent");
    lua_pushcfunction(L, lua_AddButtonComponent);
    lua_setglobal(L, "AddButtonComponent");
    lua_pushcfunction(L, lua_AddCustomComponent);
    lua_setglobal(L, "AddCustomComponent");

    lua_pushcfunction(L, lua_GetDeltaTime);
    lua_setglobal(L, "GetDeltaTime");

    lua_pushcfunction(L, lua_GetComponentValues);
    lua_setglobal(L, "GetComponentValues");
    lua_pushcfunction(L, lua_SetComponentValues);
    lua_setglobal(L, "SetComponentValues");

    lua_pushcfunction(L, lua_DeleteEntity);
    lua_setglobal(L, "DeleteEntity");
    lua_pushcfunction(L, lua_DeleteAllEntities);
    lua_setglobal(L, "DeleteAllEntities");

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

int lua_AddButtonComponent(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));

    AddButtonComponent(registry, entity);

    return 0;
}

int lua_GetDeltaTime(lua_State *L)
{
    lua_pushnumber(L, GetFrameTime());
    return 1;
}

int lua_GetComponentValues(lua_State* L)
{
    void* component = nullptr;
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    std::string componentName = static_cast<std::string>(lua_tostring(L, 2));

    if(componentName == "MoveComponent")
    {
        component = registry.try_get<MoveComponent>(entity);
        if(component)
        {
            MoveComponent* movePtr = static_cast<MoveComponent*>(component);
            lua_pushnumber(L, movePtr->position.x);
            lua_pushnumber(L, movePtr->position.y);

            lua_pushnumber(L, movePtr->velocity.x);
            lua_pushnumber(L, movePtr->velocity.y);
            //speedMultiplier doesn't matter anymore

            return 4;
        }
    }

    else if(componentName == "InputComponent")
    {
        component = registry.try_get<InputComponent>(entity);
        if(component)
        {
            InputComponent* inputPtr = static_cast<InputComponent*>(component);
            lua_pushboolean(L, inputPtr->arrowUp);
            lua_pushboolean(L, inputPtr->shootButton);
            lua_pushboolean(L, inputPtr->shift);

            lua_pushnumber(L, inputPtr->xInput);
            lua_pushnumber(L, inputPtr->yInput);
        }

        return 5;
    }

    else if(componentName == "ButtonComponent")
    {
        component = registry.try_get<ButtonComponent>(entity);
        if(component)
        {
            ButtonComponent* buttonPtr = static_cast<ButtonComponent*>(component);
            lua_pushboolean(L, buttonPtr->wasPressed);

            return 1;
        }
    }

    return 0;
    //Add more if needed
}

int lua_SetComponentValues(lua_State *L)
{
    void* component = nullptr;
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    std::string componentName = static_cast<std::string>(lua_tostring(L, 2));

    if(componentName == "MoveComponent")
    {
        component = registry.try_get<MoveComponent>(entity);
        if(component)
        {
            MoveComponent* movePtr = static_cast<MoveComponent*>(component);
            float posX = static_cast<float>(lua_tonumber(L, 3));
            float posY = static_cast<float>(lua_tonumber(L, 4));
            float velX = static_cast<float>(lua_tonumber(L, 5));
            float velY = static_cast<float>(lua_tonumber(L, 6));

            movePtr->position.x = posX;
            movePtr->position.y = posY;
            movePtr->velocity.x = velX;
            movePtr->velocity.y = velY;

            return 0;
        }
    }

    else if(componentName == "InputComponent")
    {
        component = registry.try_get<InputComponent>(entity);
        if(component)
        {
            InputComponent* inputPtr = static_cast<InputComponent*>(component);
            float xInput = static_cast<float>(lua_tonumber(L, 3));
            float yInput = static_cast<float>(lua_tonumber(L, 4));
            bool shootButton = static_cast<bool>(lua_toboolean(L, 5));
            bool arrowUp = static_cast<bool>(lua_toboolean(L, 6));
            bool shift = static_cast<bool>(lua_toboolean(L, 6));

            inputPtr->xInput = xInput;
            inputPtr->yInput = yInput;
            inputPtr->shootButton = shootButton;
            inputPtr->xInput = arrowUp;
            inputPtr->shift = shift;

            return 0;
        }
    }

    //Add more if needed

    return 0;
}
int lua_DeleteEntity(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    registry.destroy(entity);

    return 0;
}

int lua_DeleteAllEntities(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    for(auto entity: registry.view<entt::entity>()) 
    {
        registry.destroy(entity);
    }

    return 0;
}

int lua_LoadScene(lua_State *L)
{
    return 0;
}
