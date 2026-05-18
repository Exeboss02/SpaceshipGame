#include "../headers/entities.h"
#include "entities.h"

void DrawTextureComponents(entt::registry& registry)
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
    //may do AB and BA collision checks, but I'm not sure if I have time to optimize
    auto view = registry.view<BoxColliderComponent>();
    for (auto [aEntity, aCollider] : view.each())
    {
        for (auto [bEntity, bCollider] : view.each())
        {
            if(aEntity != bEntity)
            {
                if(CheckCollisionRecs(aCollider.rectangle, bCollider.rectangle))
                {
                    aCollider.inCollision = true;
                    aCollider.hitEntity = bEntity;

                    bCollider.inCollision = true;
                    bCollider.hitEntity = aEntity;
                }

                else
                {
                    aCollider.inCollision = false;
                    bCollider.inCollision = false;
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

void ResetTimerComponent(entt::registry &registry, entt::entity timerHoldingEntity)
{
    auto* timer = registry.try_get<TimerComponent>(timerHoldingEntity);
    if(timer) timer->currentTime = timer->startTime;
}
