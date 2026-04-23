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
    entt::entity player = registry.create();
    AddMoveComponent(registry, player, Vector2{100.0f, 80.0f}, Vector2{0, 0}, 125.0f);
    AddTextureComponent(registry, player, "game/assets/textures/HumanoidTpose.png", Vector2{160.0f, 80.0f}, Vector2{150.0f, 80.0f});
    AddInputComponent(registry, player);
    registry.emplace<GameTag>(player, PLAYER);
}