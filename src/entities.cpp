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
        auto* isBackground = registry.try_get<BackgroundComponent>(entity);
        if(isBackground) continue;

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

void AddGameSystemComponent(entt::registry &registry, entt::entity &entity, std::string scriptPath, int luaReference)
{
    registry.emplace<GameSystemComponent>(entity, scriptPath, luaReference);
}

void AddButtonComponent(entt::registry &registry, entt::entity &entity)
{
    registry.emplace<ButtonComponent>(entity);
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

void UpdateGameSystems(entt::registry &registry, lua_State* L)
{
    auto view = registry.view<GameSystemComponent>();

    view.each([&](GameSystemComponent& script)
    {
        lua_rawgeti(L, LUA_REGISTRYINDEX, script.luaTableReference);
        lua_getfield(L, -1, "Update");
        lua_pushvalue(L, -2);
        if (lua_pcall(L, 1, 0, 0) != LUA_OK)
        {
            std::cout << "UpdateGameSystems failed!" << std::endl;
        }
        lua_pop(L, 1);
    });
}

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
        if(IsKeyDown(KEY_LEFT_SHIFT)) input.shift = true;
        else input.shift = false;
    }
}

void UpdateColliderComponents(entt::registry &registry, lua_State* L)
{
    //max nr of colliders is 256, this is not very clean but I have to put colliders in
    //a contigous array somehow, and I don't have a class to store the array in because of ecs.
    static BoxColliderComponent* colliders[512] = {};
    static entt::entity entities[512] = {};

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

                GameSystemComponent* system1 = registry.try_get<GameSystemComponent>(entities[i]);
                GameSystemComponent* system2 = registry.try_get<GameSystemComponent>(entities[j]);
                std::string* tag1 = registry.try_get<std::string>(entities[i]);
                std::string* tag2 = registry.try_get<std::string>(entities[j]);

                if(system1 && tag2)
                {
                    lua_rawgeti(L, LUA_REGISTRYINDEX, system1->luaTableReference);
                    lua_getfield(L, -1, "OnCollision");
                    lua_pushvalue(L, -2);
                    lua_pushstring(L, tag2->c_str());
                    if (lua_pcall(L, 2, 0, 0) != LUA_OK)
                    {
                        std::cout << "OnCollision 1 failed!" << std::endl;
                    }
                    lua_pop(L, 1);
                }

                if(system2 && tag1)
                {
                    lua_rawgeti(L, LUA_REGISTRYINDEX, system2->luaTableReference);
                    lua_getfield(L, -1, "OnCollision");
                    lua_pushvalue(L, -2);
                    lua_pushstring(L, tag1->c_str());
                    if (lua_pcall(L, 2, 0, 0) != LUA_OK)
                    {
                        std::cout << "OnCollision 2 failed!" << std::endl;
                    }
                    lua_pop(L, 1);
                }
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

void UpdateButtonComponents(entt::registry &registry)
{
    auto view = registry.view<ButtonComponent, TextureComponent>();
    for (auto [entity, buttonComponent, textureComponent] : view.each())
    {
        Vector2 mousePosition = GetMousePosition();
        Vector2 rightSidePosition;
        rightSidePosition.x = textureComponent.position.x + textureComponent.size.x;
        rightSidePosition.y = textureComponent.position.y + textureComponent.size.y;

        if(mousePosition.x > textureComponent.position.x && mousePosition.x < rightSidePosition.x
            && mousePosition.y > textureComponent.position.y && mousePosition.y < rightSidePosition.y
            && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
        )
        {
            buttonComponent.wasPressed = true;
        }

        else
        {
            buttonComponent.wasPressed = false;
        }
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

// void OnCollisions(entt::registry &registry, lua_State *L)
// {
//     auto view = registry.view<GameSystemComponent>();

//     view.each([&](GameSystemComponent& script)
//     {
//         lua_rawgeti(L, LUA_REGISTRYINDEX, script.luaTableReference);
//         lua_getfield(L, -1, "Update");
//         lua_pushvalue(L, -2);
//         if (lua_pcall(L, 1, 0, 0) != LUA_OK)
//         {
//             std::cout << "UpdateGameSystems failed!" << std::endl;
//         }
//         lua_pop(L, 1);
//     });
// }

void GetGameTag(lua_State *L, std::string tag)
{
    lua_pushstring(L, tag.c_str());
}

int lua_GetGameTag(lua_State *L)
{
    return 0;
}

int ReferenceAndPushBehaviour(lua_State* L, int entity, std::string scriptPath)
{
    luaL_dofile(L, scriptPath.c_str());

    lua_pushvalue(L, -1);
    int luaTableRef = luaL_ref(L, LUA_REGISTRYINDEX);

    lua_pushinteger(L, entity);
    lua_setfield(L, -2, "ID");

    lua_pushstring(L, scriptPath.c_str());
    lua_setfield(L, -2, "path");

    lua_getfield(L, -1, "Start");
    lua_pushvalue(L, -2);
    lua_pcall(L, 1, 0, 0);

    //lua_pop(L, 1);
    return luaTableRef;
}
