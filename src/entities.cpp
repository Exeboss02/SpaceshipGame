#include "../headers/entities.h"

void DrawTextureComponents(entt::registry& registry)
{
    auto view = registry.view<TextureComponent>();
    for (auto [entity, textureComponent] : view.each())
    {
        DrawTextureV(textureComponent.texture, {textureComponent.position}, WHITE);
    }
}

bool SetTexture(Texture2D* texture, std::string path)
{
    if(!texture)
    {
        std::cout << "texture was nullptr" << std::endl;
        return false;
    }

    int width = texture->width;
    int height = texture->height;
    *texture = LoadTexture(path.c_str());
    texture->width = width;
    texture->height = height;

    return true;
}

void AddInputComponent(entt::registry& registry, entt::entity& entity)
{
    registry.emplace<InputComponent>(entity);
}

void AddMoveComponent(entt::registry &registry, entt::entity &entity, Vector2 position, Vector2 velocity, float speedMultiplier)
{
    registry.emplace<MoveComponent>(entity, position, velocity, speedMultiplier);
}

bool AddTextureComponent(entt::registry &registry, entt::entity &entity, std::string texturePath, Vector2 size, Vector2 position)
{
    Texture2D texture;
    texture.width = size.x;
    texture.height = size.y;
    bool success = SetTexture(&texture, texturePath);
    
    if(success)
    {
        registry.emplace<TextureComponent>(entity, position, texture);
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
    }
}