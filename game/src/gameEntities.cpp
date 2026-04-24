#include "../game/headers/gameEntities.h"

template<typename T, typename... Args>
void AddCustomComponent(entt::registry& registry, entt::entity entity, Args&&... args)
{
    registry.emplace<T>(entity, std::forward<Args>(args)...);
}

entt::entity CreateEnemyEntity(entt::registry &registry, EnemyTag tag)
{
    entt::entity enemy = registry.create();

    switch (tag)
    {
        case EnemyTag::DRONE:

            AddMoveComponent(registry, enemy, Vector2{0, 0}, Vector2{0, 1}, -12.0f * GetFrameTime());
            AddTextureComponent(registry, enemy, "game/assets/textures/nitwBridge.png", Vector2{80.0f, 50.0f}, Vector2{80.0f, 0.0f});
            AddCustomComponent<GameTag>(registry, enemy, GameTag::ENEMY);
            break;
        
        default:
            break;
    }

    return enemy;
}

void PlayerUpdate(entt::registry &registry)
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

void EnemyUpdate(entt::registry& registry)
{
    auto view = registry.view<MoveComponent, GameTag>();
    for (auto [entity, moveComponent, gameTag] : view.each())
    {
        if(gameTag == GameTag::ENEMY)
        {
            float deltaTime = GetFrameTime();
            moveComponent.velocity.x = 0;
            moveComponent.velocity.y = moveComponent.speedMultiplier * deltaTime;
        }
    }
}

void CreateGameEntities(entt::registry& registry)
{
    entt::entity player = registry.create();
    AddMoveComponent(registry, player, Vector2{100.0f, 80.0f}, Vector2{0, 0}, 125.0f);
    AddTextureComponent(registry, player, "game/assets/textures/HumanoidTpose.png", Vector2{160.0f, 80.0f}, Vector2{150.0f, 80.0f});
    AddInputComponent(registry, player);
    AddCustomComponent<GameTag>(registry, player, GameTag::PLAYER);

    CreateEnemyEntity(registry, EnemyTag::DRONE);
}