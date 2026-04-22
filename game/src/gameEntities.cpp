#include "../game/headers/gameEntities.h"

void PlayerUpdate(entt::registry& registry)
{
    auto view = registry.view<MoveComponent, InputComponent, GameTag>();
    for (auto [entity, moveComponent, input, gameTag] : view.each())
    {
        if(gameTag == GameTag::PLAYER)
        {
            float deltaTime = GetFrameTime();
            moveComponent.velocity.x = input.xInput * moveComponent.speedMultiplier * deltaTime;
            moveComponent.velocity.y = input.yInput * moveComponent.speedMultiplier * deltaTime;
        }
    }
}

void CreateGameEntities(entt::registry& registry)
{
    Texture2D playerTexture;
    playerTexture.width = 150;
    playerTexture.height = 80;
    SetTexture(&playerTexture, "game/assets/textures/HumanoidTpose.png");

    entt::entity player = registry.create();
    registry.emplace<GameTag>(player, PLAYER);
    registry.emplace<TextureComponent>(player, Vector2{100, 80}, playerTexture);
    registry.emplace<MoveComponent>(player, Vector2{100, 80}, Vector2{0, 0}, 125.0f);
    registry.emplace<InputComponent>(player);
}