-- void PlayerUpdate(entt::registry &registry)
-- {
--     auto view = registry.view<MoveComponent, InputComponent, GameTag>();
--     for (auto [entity, moveComponent, input, gameTag] : view.each())
--     {
--         if(gameTag == GameTag::PLAYER)
--         {
--             float deltaTime = GetFrameTime();
--             moveComponent.velocity.x = input.xInput * moveComponent.speedMultiplier * deltaTime;
--             moveComponent.velocity.y = input.yInput * moveComponent.speedMultiplier * deltaTime;

--             if(input.shootButton)
--             {
--                 auto* timer = registry.try_get<TimerComponent>(entity);

--                 if(timer && timer->currentTime <= 0)
--                 {
--                     timer->currentTime = timer->startTime;
--                     CreateBulletEntity(registry, BulletType::STANDARD, moveComponent.position);
--                 }
--             }

--             if(input.arrowUp)
--             {
--                 auto* timer = registry.try_get<TimerComponent>(entity);

--                 if(timer && timer->currentTime <= 0)
--                 {
--                     timer->currentTime = timer->startTime;
--                     CreateEnemyEntity(registry, EnemyTag::DRONE);
--                 }
--             }
--         }
--     }
-- }

function PlayerUpdate()
    input = {}
    input = ReadInput(player) --player is a global entity

    
end

PlayerUpdate()
