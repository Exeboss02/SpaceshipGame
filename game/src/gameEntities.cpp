#include "../game/headers/gameEntities.h"

template<typename T, typename... Args>
void AddCustomComponent(entt::registry& registry, entt::entity entity, Args&&... args)
{
    registry.emplace<T>(entity, std::forward<Args>(args)...);
}

int lua_AddCustomComponent(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    std::string type = lua_tostring(L, 2);

    //do I really need to return values > 0 here?

    if(type == ("GameTag"))
    {
        std::string tag = lua_tostring(L, 3);

        if(tag == "ENEMY" || tag == "Enemy")
        {
            AddCustomComponent<GameTag>(registry, entity, GameTag::ENEMY);
        }
        else if(tag == "PLAYER" || tag == "Player")
        {
            AddCustomComponent<GameTag>(registry, entity, GameTag::PLAYER);
        }
        else if(tag == "GUN" || tag == "Gun")
        {
            AddCustomComponent<GameTag>(registry, entity, GameTag::GUN);
        }
        else if(tag == "BULLET" || tag == "Bullet")
        {
            AddCustomComponent<GameTag>(registry, entity, GameTag::BULLET);
        }

        return 3;
    }

    else if(type == ("EnemyTag"))
    {
        std::string tag = lua_tostring(L, 3);

        if(tag == "DRONE" || tag == "Drone")
        {
            AddCustomComponent<EnemyTag>(registry, entity, EnemyTag::DRONE);
        }
        return 3;
    }

    else if(type == ("BulletType"))
    {
        std::string tag = lua_tostring(L, 3);

        if(tag == "STANDARD" || tag == "Standard")
        {
            AddCustomComponent<BulletType>(registry, entity, BulletType::STANDARD);
        }
        return 3;
    }

    else if(type == ("BulletPattern"))
    {
        std::string tag = lua_tostring(L, 3);

        if(tag == "STRAIGHT" || tag == "Straight")
        {
            AddCustomComponent<BulletPattern>(registry, entity, BulletPattern::STRAIGHT);
        }
        return 3;
    }

    else if(type == ("GunComponent"))
    {
        float shootCoolDown = static_cast<float>(lua_tonumber(L, 3));
        float spreadFactor = static_cast<float>(lua_tonumber(L, 4));

        AddCustomComponent<GunComponent>(registry, entity, shootCoolDown, spreadFactor);
        return 4;
    }

    else if(type == ("HealthComponent"))
    {
        float hp = static_cast<float>(lua_tonumber(L, 3));

        AddCustomComponent<HealthComponent>(registry, entity, hp);
        return 3;
    }

    else if(type == ("DamageComponent"))
    {
        float damage = static_cast<float>(lua_tonumber(L, 3));

        AddCustomComponent<DamageComponent>(registry, entity, damage);
        return 3;
    }

    else if(type == ("BackgroundComponent"))
    {
        float scrollSpeed = static_cast<float>(lua_tonumber(L, 3));

        AddCustomComponent<BackgroundComponent>(registry, entity, scrollSpeed);
        return 3;
    }

    return 2;
}

void GameLuaSetup(lua_State *L)
{
    lua_pushcfunction(L, lua_AddCustomComponent);
    lua_setglobal(L, "AddCustomComponent");
}

entt::entity CreateEnemyEntity(entt::registry &registry, EnemyTag tag)
{
    entt::entity enemy = registry.create();

    switch (tag)
    {
        case (EnemyTag::DRONE):
        {
            AddMoveComponent(registry, enemy, Vector2{0, 0}, Vector2{0, 1}, -120.0f * GetFrameTime());
            auto* moveComponent = registry.try_get<MoveComponent>(enemy);
            if(moveComponent) moveComponent->speedMultiplier = 80.0f;

            AddBoxColliderComponent(registry, enemy, Vector2(0, 0), Vector2{80.0f, 50.0f});
            AddTextureComponent(registry, enemy, "game/assets/textures/nitwBridge.png", Vector2{80.0f, 50.0f}, Vector2{80.0f, 0.0f});
            AddCustomComponent<GameTag>(registry, enemy, GameTag::ENEMY);
            AddCustomComponent<GunComponent>(registry, enemy);
            AddCustomComponent<HealthComponent>(registry, enemy, 10.0f);
            break;
        }
        
        default:
        {
            break;
        }
    }

    return enemy;
}

entt::entity CreateBulletEntity(entt::registry &registry, BulletType bulletType, Vector2 position)
{
    entt::entity bullet = registry.create();
    AddMoveComponent(registry, bullet, position, Vector2{0, 1}, -12.0f * GetFrameTime());
    AddCustomComponent<GameTag>(registry, bullet, GameTag::BULLET);
    AddCustomComponent<BulletType>(registry, bullet, bulletType);

    switch(bulletType)
    {
        case(BulletType::STANDARD):
        {
            AddTextureComponent(registry, bullet, "game/assets/textures/nitwBridge.png", Vector2{80.0f, 50.0f}, position);
            auto* moveComponent = registry.try_get<MoveComponent>(bullet);
            if(moveComponent) moveComponent->speedMultiplier = -800.0f;

            AddBoxColliderComponent(registry, bullet, position, Vector2{80.0f, 50.0f});
            AddCustomComponent<DamageComponent>(registry, bullet, 6.0f);
            break;
        }

        default:
        {
            AddTextureComponent(registry, bullet, "game/assets/textures/nitwBridge.png", Vector2{80.0f, 50.0f}, Vector2{80.0f, 0.0f});
            auto* moveComponent = registry.try_get<MoveComponent>(bullet);
            if(moveComponent) moveComponent->speedMultiplier = -800.0f;

            AddBoxColliderComponent(registry, bullet, Vector2{80.0f, 0.0f}, Vector2{80.0f, 50.0f});
            AddCustomComponent<DamageComponent>(registry, bullet, 2.0f);
            break;
        }
    }

    return bullet;
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

            if(input.shootButton)
            {
                auto* timer = registry.try_get<TimerComponent>(entity);

                if(timer && timer->currentTime <= 0)
                {
                    timer->currentTime = timer->startTime;
                    CreateBulletEntity(registry, BulletType::STANDARD, moveComponent.position);
                }
            }

            if(input.arrowUp)
            {
                auto* timer = registry.try_get<TimerComponent>(entity);

                if(timer && timer->currentTime <= 0)
                {
                    timer->currentTime = timer->startTime;
                    CreateEnemyEntity(registry, EnemyTag::DRONE);
                }
            }
        }
    }
}

void EnemyUpdate(entt::registry& registry)
{
    //Movement
    auto view = registry.view<MoveComponent, GameTag>();
    for (auto [enemy, moveComponent, gameTag] : view.each())
    {
        if(gameTag == GameTag::ENEMY)
        {
            float deltaTime = GetFrameTime();
            moveComponent.velocity.x = 0;
            moveComponent.velocity.y = moveComponent.speedMultiplier * deltaTime;

            //Collision
            auto* collider = registry.try_get<BoxColliderComponent>(enemy);
            auto* otherCollider = registry.try_get<BoxColliderComponent>(collider->hitEntity);
            
            if(collider->inCollision)
            {
                // std::cout << "ENEMY WAS HIT!!!!!!!!" << std::endl;
                // std::cout << "From EnemyUpdate: " << collider->inCollision << ", " << otherCollider->inCollision << std::endl;

                auto* hitEntityTag = registry.try_get<GameTag>(collider->hitEntity);
                auto* damageComponent = registry.try_get<DamageComponent>(collider->hitEntity);
                auto* healthComponent = registry.try_get<HealthComponent>(enemy);

                if(damageComponent && healthComponent && hitEntityTag)
                {
                    if(*hitEntityTag == GameTag::BULLET)
                    {
                        healthComponent->hp -= damageComponent->damage;
                        registry.destroy(collider->hitEntity);

                        if(healthComponent->hp <= 0)
                        {
                            registry.destroy(enemy);
                        }
                    }
                }
            }
        }
    }
}

void BulletUpdate(entt::registry &registry)
{
    auto view = registry.view<MoveComponent, GameTag>();
    for (auto [entity, moveComponent, gameTag] : view.each())
    {
        if(gameTag == GameTag::BULLET)
        {
            float deltaTime = GetFrameTime();
            moveComponent.velocity.x = 0;
            moveComponent.velocity.y = moveComponent.speedMultiplier * deltaTime;

            //Collision
            auto* collider = registry.try_get<BoxColliderComponent>(entity);
            if(collider)
            {
                auto* hitTag = registry.try_get<GameTag>(collider->hitEntity);

                auto* otherCollider = registry.try_get<BoxColliderComponent>(collider->hitEntity);

            }
        }
    }

    //also delete bullets after some time
}

void CreateGameEntities(entt::registry& registry)
{
    // entt::entity background = registry.create();
    // AddTextureComponent(registry, background, "game/assets/textures/space.png", Vector2{1920.0f, 1080.0f}, Vector2{0.0f, 0.0f});
    // AddCustomComponent<BackgroundComponent>(registry, background, 19.0f);
}
